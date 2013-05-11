<?php
/**
 * @file
 * Administration page callbacks fof ys_makelaar.
 */

function ys_makelaar_settings_form() {
  $result = db_query('SELECT * FROM {ys_makelaars}');
  $rij = array();
  foreach ($result as $row) {
    $rij = (array) $row;
    $edit_link = '<a href =  "ys_makelaar/m_list/edit/"' . $rij['m_id'] . '>Edit</a>';
    $remove_link = '<a href =  "ys_makelaar/m_list/delete/"' . $rij['m_id']. '>Delete</a>';
    $feed_link = '<a href="ys_makelaar/feed/"' . $rij['m_id'] . '>Feed</a>';
    array_push($rij, $edit_link, $remove_link, $feed_link);
    $makelaars[]['data'] = $rij;
  }
  $header = array('Id', 'Name', 'Base URL', 'Start', 'Edit', 'Delete', 'Feed' );
  $output = theme('table', array('header' => $header, 'rows' => $makelaars));
  // TODO get the current feed locations for display
  $form['ys_display'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="ys-button-link"><a href = "node/add/page">' . t('add a new real estate agent') . '</a></div>' . $output,
  );
  $form['ys_settings_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of the makelaar'),
  //  '#description' => t('A text field will be available on these content types to make user-specific notes.'),
    '#prefix' => '<div id="ys-setting-form" style="display:none;">',
  );
  $form['ys_settings_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base URL of the website'),
    '#description' => t('The base URL of the website to crawl'),
  );
  $form['ys_settings_start'] = array(
    '#type' => 'textfield',
    '#title' => t('Startpage to begin the crawl'),
    '#description' => t('If the startingpoint is the base URL leave this blank'),
  );
  $form['ys_settings_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#suffix' => '</div>',
  );
  return $form;
}

function ys_makelaar_settings_form_submit($form, &$form_state) {
  $m_name = $form_state['values']['ys_settings_name'];
  $base_url = $form_state['values']['ys_settings_base_url'];
  $base_start = $form_state['values']['ys_settings_start'];
  drupal_set_message(t('Makelaar %m_name | Base URL %base_url  | startingpoint %base_start',
                       array(
                          '%m_name' => $m_name,
                          '%base_url' => $base_url,
                          '%base_start' => $base_start,))
                     );
  db_insert('ys_makelaars')
    ->fields(array(
      'm_name' => $m_name,
      'base_url' => $base_url,
      'start_url' => $base_start,
    )
  )
  ->execute();
}

/*
 * @file
 * deze functie haalt de basic links (realestate objects) voor één bepaalde makelaar em
 * slaat deze op in de database. $m_id is de Id van de makelaar
 * opegeroepen door callback ys_makelaar/feed/%
 * TODO hoevaak deze links ophalen
 */
function ys_makelaar_feed($m_id) {
  $result = db_query('SELECT * FROM {ys_makelaars} WHERE m_id = :m_id', array('m_id' => $m_id)) -> fetchObject();
    $makelaar = $result -> m_id;
    $base_url = $result-> base_url;
    $start_url = $result -> start_url;
    $feed_url = $base_url . (!empty($start_url) ? ('/' . $start_url):'');
    drupal_set_message('feed URL is : '. $feed_url);
    $ch = curl_init(); // Initialize a CURL session.
    if (empty($ch)) {
      drupal_set_message("Curl error#");
    }
    else {
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); // Return Page contents.
      curl_setopt($ch, CURLOPT_URL, $feed_url); // Pass URL as parameter.
      $curl_result = curl_exec($ch); // grab URL and pass it to the variable.
      curl_close($ch); // close curl resource, and free up system resources.
      /*** a new dom object ***/ 
      $dom = new domDocument; 
      /*** load the html into the object ***/ 
      @$dom->loadHTML($curl_result); 
      //Het gedeelte met alle huizen
      $div = $dom-> getElementById('content_small');
      $lnks = $div->getElementsByTagName('a'); 
      define ("DATE_MYSQL", "Y/m/d H:i:s");
      $now = new DateTime("now");
      print_r($now);
      echo $now->format(DATE_MYSQL);
      foreach ($lnks as $lnk) {
        $l = $lnk->attributes-> getNamedItem("href")->nodeValue;
        // link opslaan in database
        db_merge('ys_makelaar_links')  ->
          key(array('basic_link' => $l))  ->         
            fields(array(
             'm_id' => $m_id,
             'time_updated' => $now-> format(DATE_MYSQL),
              ))  ->execute();
      }
      //$output .= "</ul>";
      //return $output;
    }
  
 drupal_set_message('Basic links retrieved for '. $m_id);
 drupal_goto('');
}

/*
 * @file
 * functie haalt per basic-link de details op en slaat ze op in DB
 * Nu nog opgeroepen door callback ys_makelaar/feed_detail maar uiteindelijk
 * oproepen per cron
 */
function ys_makelaar_feed_detail($m_id) {
  $b = db_query('SELECT base_url FROM {ys_makelaars} WHERE m_id = :m_id', array('m_id' => $m_id)) -> fetchField();
  $result = db_query('SELECT * FROM {ys_makelaar_links} WHERE m_id = :m_id AND status = :status LIMIT 0, 5',array('m_id' => $m_id, 'status' => 1));
  //per basic link de gegevens downloaden of updaten (eens per 24 uur)
  foreach ($result as $row) {  
    $updated = $row-> time_updated;
    if (_update_required($updated)) {
      $l_id = $row-> id;
      $l_link = $b . $row-> basic_link;
      $ch = curl_init(); // Initialize a CURL session.
      if (empty($ch)) {
        drupal_set_message("Curl error");
      }
      else {
        // Curl is OK and starting the feed
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_URL, $l_link);
        $curl_result = curl_exec($ch);
        curl_close($ch); // close curl resource, and free up system resources.
        $main_page = new domDocument; 
        if (@$main_page->loadHTML($curl_result)) {
           /* deze loop stuurt iedere keer een $mainpage naar de subfunctie
           * de subfunctie haalt de details op voor opslag in DB
            * $l[id] is de id van de detail link (één per realty-item */
          ys_makelaar_fill_items($m_id, $l_id, $main_page);
        }
        else {
          drupal_set_message('loadHTML error on link: ' . $l);
        }
      }
    }  // if update required
  } //foreach $result as row
  drupal_set_message('Items retrieved');
  drupal_goto('');
}

// per realty-item wordt deze functie 1 X uitgevoerd
function ys_makelaar_fill_items($makelaars_id, $realty_item_id, $web_page) {
  $xpath = new DOMXpath($web_page);
  $Xresult = $xpath-> query('//div[@id="content_small"]/div[1]/div/h1');
  $object_title = $Xresult-> item(0) ->nodeValue;
  // DEBUG  drupal_set_message($object_title. " | ");
  $values = $xpath-> query('//div[(@id="detail_content_coll" or @id="detail_content")]/table/tr/td');
    /* DEBUG foreach($values as $value) {
    echo $value-> nodeValue ;
    echo '<br />';
  }*/
  $node = new stdClass();
	$node-> type = 'job_post';
	node_object_prepare($node);       //default node items invullen
  $node-> ysm_id = $realty_item_id; //TODOitem id van detail tabel koppelen aan die van de bron tabel
  $node-> title = $object_title;
	$node->language = 'en';
	
  for ($i = 0; $i < $values->length; $i=$i+2) {
    //detailgegevens parsen
    $value = $values-> item($i)->nodeValue;
    $value1 = strtr($value, array_flip(get_html_translation_table(HTML_ENTITIES, ENT_QUOTES))); 
    str_replace('&nbsp;','',$value);
    $next_value = $values-> item($i+1)->nodeValue;
    // DEBUG drupal_set_message(trim($value) .'| '. $next_value . '<br />');
    switch(trim($value1,chr(0xC2).chr(0xA0))) {
      case 'Prijs: ' :
        $node-> t_prijs[$node-> language][0]['value'] = $next_value; 
				drupal_set_message('next_value = '. $next_value . ' | node  = '. $node-> t_prijs[$node-> language][0]['value']); 
        break;
      case 'Wijk: ' :
        $node-> wijk[$node->language][0]['value'] = $next_value; break; 
      case 'Bouwjaar: ' :
        $node-> t_bouwjaar[$node->language][0]['value'] = $next_value; break; 
      case 'Slaapkamers: ' :
        $node-> t_slaapkamers[$node->language][0]['value'] = $next_value; break; 
      case 'Badkamers: ' :
        $node-> t_badkamers[$node->language][0]['value'] = $next_value; break; 
      case 'Datum oplevering: ' :
        $node-> oplevering[$node->language][0]['value'] = $next_value; break; 
      case 'Woonoppervlakte: ' :
        $node-> t_woonoppervl[$node->language][0]['value'] = $next_value; break; 
      case 'Kavelgrootte: ' :  
        $node-> t_kavel[$node->language][0]['value'] = $next_value; break;
      case 'Project: ' :  
        $node-> project[$node->language][0]['value'] = $next_value; break; 
      case 'Zwembad: ' :  
        $node-> zwembad[$node->language][0]['value'] = 1; break; 
      case 'Zeezicht: ' :  
        $node-> zeezicht[$node->language][0]['value'] = 1; break; 
      default:
        echo(trim($value1,chr(0xC2).chr(0xA0)). '| not matched<br />');
    }
  } // foreach
	  //drupal_set_message('buiten loop '. $node-> t_prijs[$node-> language][0]['value']);
  // omschrijving parsen
  $xpath = new DOMXpath($web_page);
  $values = $xpath-> query('//div[@id="detail_content_nocolor"]');
  $body_text = $values-> item(0) ->nodeValue;

// Object valuta ophalen uit omschrijving:
 // $node-> valuta[$node->language][0]['value'] = substr($body_text, -4, 3);
	
	// Items wegschrijven als ysm node.

  $node->body[$node->language][0]['value']   = $body_text;
  $node->body[$node->language][0]['summary'] = text_summary($body_text);
  $node->body[$node->language][0]['format']  = 1;
//  $path = 'content/programmatically_created_node_' . date('YmdHis');
//  $node->path = array('alias' => $path);
  // drupal_set_message('voor save '. $node-> t_prijs[$node-> language][0]['value']); debug
  node_save($node);
 //drupal_set_message('na save '. $node-> t_prijs[$node-> language][0]['value']); debug
 

  // url van de plaatjes opslaan
 ys_makelaar_get_images_links($makelaars_id, $realty_item_id, $web_page, $node-> nid);

}

/* funtie haalt per items alle foto´s op
 * Alleen de links. de daadwerkelijke binairies zelf worden
 * later door cron opgehaald
 * Wordt opgeroepen door ys_makelaar_fill_items (eenmaal per realty item) 
 */
function ys_makelaar_get_images_links($makelaars_id, $realty_item_id, $webpage, $nid) {
  $xpath = new DOMXpath($webpage);
  $values = $xpath-> query('//div[@id="detail_images"]/a[@href]/img/@src');
  foreach ($values as $value) {
    $image_rel_link = $value-> nodeValue;
    db_merge('ys_makelaar_image_cache')  ->
      key(array('image_link' => $image_rel_link))  ->
        fields(array(
          'item_id' => $realty_item_id,
          'image_link' => $image_rel_link,
          'time_saved' => REQUEST_TIME,
					'node_id' => $nid,
        ))  ->execute();
  }
}



/*
 * @file
 * $timestamp is de updated time in de DB vor dit object
 * @return TRUE of FALSE
 */
function _update_required($updated) {
 //  $dateTime = new DateTime("now");  

  //echo $dateTime->format(DATE_MYSQL); 
  return TRUE;
}
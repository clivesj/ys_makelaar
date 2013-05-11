<?php

function ys_makelaar_fields_ysm() {
  $t =get_t();
  return array(
		'ysm_id' => array(
      'field_name' => 'ysm_id',
      'type' => 'text',
      'label' => $t('Unique ident within ysm'),
     ),
    't_prijs' => array(
      'field_name' => 't_prijs',
      'type' => 'text',
      'label' => $t('Price as text - still to convert'),
     ),
    
    'wijk' => array(
      'field_name' => 'wijk',
      'type' => 'text',
      'label' => $t('Wijk'),
     ),
    
    't_bouwjaar' => array(
      'field_name' => 't_bouwjaar',
      'type' => 'text',
      'label' => $t('Bouwjaar as text'),
      ),
  
	  't_slaapkamers' => array(
      'field_name' => 't_slaapkamers',
      'type' => 'text',
      'label' => $t('Slaapkamers as text'),
      ),
    
    't_badkamers' => array(
      'field_name' => 't_badkamers',
      'type' => 'text',
      'label' => $t('Badkamers'),
      ),
    
    't_kavel' => array(
      'field_name' => 't_kavel',
      'type' => 'text',
      'label' => $t('Kavel as text'),
      ),
    
    't_woonoppervl' => array(
      'field_name' => 't_woonopppervl',
      'type' => 'text',
      'label' => $t('Woonoppervlakte as text'),
      ),
    
    'project' => array(
      'field_name' => 'project',
      'type' => 'text',
      'label' => $t('Project'),
      ),
    
    'zwembad' => array(
      'field_name' => 'zwembad',
      'type' => 'text',
      'label' => $t('Zwembad 1 is ja'),
      ),
    
    'zeezicht' => array(
      'field_name' => 'zeezicht',
      'type' => 'text',
      'label' => $t('Zeezicht'),
      ),
    
    'oplevering' => array(
      'field_name' => 'oplevering',
      'type' => 'text',
      'label' => $t('Oplevering'),
     ),
		  // image field
    'item_image' => array(
      'field_name' => 'item_image',
      'label' => $t('Foto'),
      'cardinality' => 1,
      'type' => 'image',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
    ),

  );
}

function ys_makelaar_instances_ysm() {
  $t =get_t();
  return array(
		'ysm_id' => array(
      'field_name' => 'ysm_id',
      'type' => 'text',
      'label' => $t('Unique ident within ysm'),
		  'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('text'),
          'type' => 'text',
        ),
      ),
    ),
    't_prijs' => array(
      'field_name' => 't_prijs',
      'type' => 'text',
      'label' => $t('Price as text - still to convert'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('text'),
          'type' => 'text',
        ),
      ),
    ),
    
    'wijk' => array(
      'field_name' => 'wijk',
      'type' => 'text',
      'label' => $t('Wijk'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Wijk'),
          'type' => 'text',
        ),
      ),
    ),
    
    't_bouwjaar' => array(
      'field_name' => 't_bouwjaar',
      'type' => 'text',
      'label' => $t('Bouwjaar as text'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Bouwjaar as text'),
          'type' => 'text',
        ),
      ),
    ),
    't_slaapkamers' => array(
      'field_name' => 't_slaapkamers',
      'type' => 'text',
      'label' => $t('Slaapkamers as text'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('slaapkamers as text'),
          'type' => 'text',
        ),
      ),
    ),
    
    't_badkamers' => array(
      'field_name' => 't_badkamers',
      'type' => 'text',
      'label' => $t('Badkamers'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Badkamers'),
          'type' => 'text',
        ),
      ),
    ),
    
    't_kavel' => array(
      'field_name' => 't_kavel',
      'type' => 'text',
      'label' => $t('Kavel as text'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Kavel as text'),
          'type' => 'text',
        ),
      ),
    ),
    
    't_woonoppervl' => array(
      'field_name' => 't_woonopppervl',
      'type' => 'text',
      'label' => $t('Woonoppervlakte as text'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Woonoppervlakte as text'),
          'type' => 'text',
        ),
      ),
    ),
    
    'project' => array(
      'field_name' => 'project',
      'type' => 'text',
      'label' => $t('Project'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Project'),
          'type' => 'text',
        ),
      ),
    ),
    
    'zwembad' => array(
      'field_name' => 'zwembad',
      'type' => 'text',
      'label' => $t('Zwembad 1 is ja'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Zwembad 1 is ja'),
          'type' => 'text',
        ),
      ),
    ),
    
    'zeezicht' => array(
      'field_name' => 'zeezicht',
      'type' => 'text',
      'label' => $t('Zeezicht'),
      'widget' => array(
        'type' => 'text_textfield',
         ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Zeezicht'),
          'type' => 'text',
          ),
       ),
    ),
    
    'oplevering' => array(
      'field_name' => 'oplevering',
      'type' => 'text',
      'label' => $t('Oplevering'),
      'widget' => array(
        'type' => 'text_textfield',
        ),
      'display' =>array(
        'example_node_list' => array(
          'label' => $t('Oplevering'),
          'type' => 'text',
        ),
      ),
    ),
		
		 // instance of the image field above
    'item_image' => array(
      'field_name' => 'item_image',
      'label' => $t('Foto'),
      'cardinality' => 1,
      'type' => 'image',
      'settings' => array(
        'alt_field' => 1,
        'file_directory' => 'image',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 1,
        'user_register_form' => FALSE,
        ),
      'widget' => array(
        'settings' => array(
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'throbber',
          ),
        ),
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'type' => 'image',
          'settings' => array('image_style' => 'bfi_common_features_image', 'image_link' => ''),
          'weight' => -1,
          ),
        'teaser' => array(
          'label' => 'hidden',
          'type' => 'image',
          'settings' => array('image_style' => 'thumbnail', 'image_link' => 'content'),
          'weight' => -1,
        ),
      ),
    ),

  );
}
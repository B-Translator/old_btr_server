<?php
/**
 * @file
 * btr_btrClient.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function btr_btrClient_field_default_fields() {
  $fields = array();

  // Exported field: 'user-user-field_auxiliary_languages'.
  $fields['user-user-field_auxiliary_languages'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '2',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'user',
      ),
      'field_name' => 'field_auxiliary_languages',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'fr' => 'French',
          'sq' => 'Albanian',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'You may select one or two auxiliary (helping) languages, especially if you are not very familiar with English. If the translation of the string in these languages exists, it will be displayed below the original (English) string. This may help you to get a better idea about how it could be translated.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_auxiliary_languages',
      'label' => 'Auxiliary Languages',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => '4',
      ),
    ),
  );

  // Exported field: 'user-user-field_data_sequential'.
  $fields['user-user-field_data_sequential'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'user',
      ),
      'field_name' => 'field_data_sequential',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => 20000,
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 5,
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_data_sequential',
      'label' => 'field_data_sequential',
      'required' => FALSE,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 7,
      ),
    ),
  );

  // Exported field: 'user-user-field_feedback_channels'.
  $fields['user-user-field_feedback_channels'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '10',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'user',
      ),
      'field_name' => 'field_feedback_channels',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'website' => 'Website',
          'email' => 'Email',
          'desktop' => 'Desktop App',
          'facebook' => 'Facebook App',
          'google+' => 'Google+ App',
          'twitter' => 'Twitter App',
          'android' => 'Android App',
          'iphone' => 'iPhone App',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => array(
        0 => array(
          'value' => 'website',
        ),
      ),
      'deleted' => '0',
      'description' => 'The ways that you would prefer to provide the feedback. <br/>
<strong>Note</strong>: Currently only <em>Website</em> and <em>Email</em> are implemented. You will be sent an email each day with the strings to be reviewed, and you can also provide feedback through the website',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => 4,
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_feedback_channels',
      'label' => 'Feedback Channels',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => '6',
      ),
    ),
  );

  // Exported field: 'user-user-field_order_of_strings'.
  $fields['user-user-field_order_of_strings'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'user',
      ),
      'field_name' => 'field_order_of_strings',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'random' => 'Random',
          'sequential' => 'Sequential',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => array(
        0 => array(
          'value' => 'random',
        ),
      ),
      'deleted' => '0',
      'description' => 'The order in which the strings that are to be reviewed/translated will be presented. By default, strings are selected randomly from the projects that you have selected to contribute. But you may wish to review them in sequential order, one after another, as they are listed on the translation (PO) files.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => 1,
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_order_of_strings',
      'label' => 'Order of Strings',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => 1,
      ),
      'widget' => array(
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_select',
        'weight' => '3',
      ),
    ),
  );

  // Exported field: 'user-user-field_preferred_projects'.
  $fields['user-user-field_preferred_projects'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'user',
      ),
      'field_name' => 'field_preferred_projects',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => 255,
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'If you want to contribute only to one or some of the projects, you can add them here. Then only strings from these projects will be presented for review/translation. You can enter projects in the form \'Origin/Project\', for example: KDE/kdeedu, Mozilla/browser, etc. Or you can include all the projects from a certain origin, like this: KDE, LibreOffice, etc. You can change the preferred projects later at any time. See a list of imported projects <a href=\'/translations/project/list/*/*/txt\' target=\'_blank\'>here</a>.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_preferred_projects',
      'label' => 'Preferred Projects',
      'required' => FALSE,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'module' => 'text',
        'settings' => array(
          'size' => '30',
        ),
        'type' => 'text_textfield',
        'weight' => '2',
      ),
    ),
  );

  // Exported field: 'user-user-field_translations_per_day'.
  $fields['user-user-field_translations_per_day'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'user',
      ),
      'field_name' => 'field_translations_per_day',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'number',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => array(
        0 => array(
          'value' => '1',
        ),
      ),
      'deleted' => '0',
      'description' => 'Each day an automatic email will be sent to you with some strings for review/translation (if you enable the email feedback channel). This is the number of strings that will be sent for review/translation each day by email.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'number',
          'settings' => array(
            'decimal_separator' => '.',
            'prefix_suffix' => TRUE,
            'scale' => 0,
            'thousand_separator' => ' ',
          ),
          'type' => 'number_integer',
          'weight' => 3,
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_translations_per_day',
      'label' => 'Translations per Day',
      'required' => FALSE,
      'settings' => array(
        'max' => '',
        'min' => '',
        'prefix' => '',
        'suffix' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'number',
        'settings' => array(),
        'type' => 'number',
        'weight' => '5',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Auxiliary Languages');
  t('Each day an automatic email will be sent to you with some strings for review/translation (if you enable the email feedback channel). This is the number of strings that will be sent for review/translation each day by email.');
  t('Feedback Channels');
  t('If you want to contribute only to one or some of the projects, you can add them here. Then only strings from these projects will be presented for review/translation. You can enter projects in the form \'Origin/Project\', for example: KDE/kdeedu, Mozilla/browser, etc. Or you can include all the projects from a certain origin, like this: KDE, LibreOffice, etc. You can change the preferred projects later at any time. See a list of imported projects <a href=\'/translations/project/list/*/*/txt\' target=\'_blank\'>here</a>.');
  t('Order of Strings');
  t('Preferred Projects');
  t('The order in which the strings that are to be reviewed/translated will be presented. By default, strings are selected randomly from the projects that you have selected to contribute. But you may wish to review them in sequential order, one after another, as they are listed on the translation (PO) files.');
  t('The ways that you would prefer to provide the feedback. <br/>
<strong>Note</strong>: Currently only <em>Website</em> and <em>Email</em> are implemented. You will be sent an email each day with the strings to be reviewed, and you can also provide feedback through the website');
  t('Translations per Day');
  t('You may select one or two auxiliary (helping) languages, especially if you are not very familiar with English. If the translation of the string in these languages exists, it will be displayed below the original (English) string. This may help you to get a better idea about how it could be translated.');
  t('field_data_sequential');

  return $fields;
}

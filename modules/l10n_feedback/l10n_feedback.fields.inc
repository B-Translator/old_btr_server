<?php
/**
 * This file contains functions for creating and deleting
 * user profile fields (which actually contain user preferencies).
 */

/**
 * This function is called by hook_uninstall(), in order
 * to delete the custom fields created by l10n_feedback.
 */
function l10n_feedback_delete_userprofile_fields() {

  $field_names = array(
    'field_preferred_projects',
    'field_order_of_strings',
    'field_auxiliary_languages',
    'field_translations_per_day',
    'field_feedback_channels',
    'field_data_sequential',
    'field_sequential_state',
  );

  foreach ($field_names as $field_name) {
    $instance = field_info_instance('user', $field_name, 'user');
    field_delete_instance($instance);
    $field = field_info_field($field_name);
    field_delete_field($field);
  }
}

/**
 * This function is called by hook_install(), in order
 * to create custom fields about user preferencies for
 * B-Translator.
 */
function l10n_feedback_create_userprofile_fields() {

  // create a field and instance for 'field_preferred_projects'
  field_create_field(
    array(
      'field_name' => 'field_preferred_projects',
      'type' => 'text',
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,  //multiple (unlimited) number of values
      'entity_types' => array('user'),
    ));
  field_create_instance(
    array(
      'field_name' => 'field_preferred_projects',
      'entity_type' => 'user',
      'bundle' => 'user',
      'label' => 'Preferred Projects',
      'description' => "If you want to contribute only to one or some of the projects, you can add them here. Then only strings from these projects will be presented for review/translation. You can enter projects in the form 'Origin/Project', for example: KDE/kdeedu, Mozilla/browser, etc. Or you can include all the projects from a certain origin, like this: KDE, LibreOffice, etc. You can change the preferred projects later at any time. See a list of imported projects <a href='/translations/project/list/*/*/txt' target='_blank'>here</a>.",
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'weight' => '2',
        'type' => 'text_textfield',
        'settings' => array('size' => '30'),
      ),
    ));

  // create a field and instance for 'field_preferred_projects'
  field_create_field(
    array(
      'field_name' => 'field_order_of_strings',
      'type' => 'list_text',
      'cardinality' => 1,
      'settings' => array(
        'allowed_values' => array('random' => 'Random', 'sequential' => 'Sequential'),
      ),
      'entity_types' => array('user'),
    ));
  field_create_instance(
    array(
      'field_name' => 'field_order_of_strings',
      'entity_type' => 'user',
      'bundle' => 'user',
      'label' => 'Order of Strings',
      'description' => 'The order in which the strings that are to be reviewed/translated will be presented. By default, strings are selected randomly from the projects that you have selected to contribute. But you may wish to review them in sequential order, one after another, as they are listed on the translation (PO) files.',
      'default_value' => array(array('value' => 'random')),
      'settings' => array('user_register_form' => 1),
      'widget' => array(
        'weight' => '3',
        'type' => 'options_select',
        'module' => 'options',
      ),
    ));

  // create a field and instance for 'field_auxiliary_languages'
  $languages = array();
  $arr_langs = l10n_feedback_get_languages();
  foreach ($arr_langs as $lng=>$language) {
    $languages[$lng] = $language['name'];
  }
  unset($languages['en']);

  field_create_field(
    array(
      'field_name' => 'field_auxiliary_languages',
      'type' => 'list_text',
      'cardinality' => 2,
      'entity_types' => array('user'),
      'settings' => array('allowed_values' => $arr_langs),
    ));
  field_create_instance(
    array(
      'field_name' => 'field_auxiliary_languages',
      'entity_type' => 'user',
      'bundle' => 'user',
      'label' => 'Auxiliary Languages',
      'description' => 'You may select one or two auxiliary (helping) languages, especially if you are not very familiar with English. If the translation of the string in these languages exists, it will be displayed below the original (English) string. This may help you to get a better idea about how it could be translated.',
      //'settings' => array('user_register_form' => 1),
      'widget' => array(
        'weight' => '4',
        'type' => 'options_buttons',
      ),
    ));

  // create a field and instance for 'field_translations_per_day'
  field_create_field(
    array(
      'field_name' => 'field_translations_per_day',
      'type' => 'number_integer',
      'cardinality' => 1,
      'entity_types' => array('user'),
    ));
  field_create_instance(
    array(
      'field_name' => 'field_translations_per_day',
      'entity_type' => 'user',
      'bundle' => 'user',
      'label' => 'Translations per Day',
      'description' => 'Each day an automatic email will be sent to you with some strings for review/translation (if you enable the email feedback channel). This is the number of strings that will be sent for review/translation each day by email.',
      //'settings' => array('user_register_form' => 1),
      'widget' => array(
        'weight' => '5',
        'type' => 'number',
      ),
      'default_value' => array(array('value' => '1')),
    ));

  // create a field and instance for 'field_feedback_channels'
  field_create_field(
    array(
      'field_name' => 'field_feedback_channels',
      'type' => 'list_text',
      'cardinality' => 10,
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
      ),
      'entity_types' => array('user'),
    ));
  field_create_instance(
    array(
      'field_name' => 'field_feedback_channels',
      'entity_type' => 'user',
      'bundle' => 'user',
      'label' => 'Feedback Channels',
      'description' => "The ways that you would prefer to provide the feedback. <br/>\r\n<strong>Note</strong>: Currently only <em>Website</em> and <em>Email</em> are implemented. You will be sent an email each day with the strings to be reviewed, and you can also provide feedback through the website",
      //'settings' => array('user_register_form' => 1),
      'widget' => array(
        'weight' => '6',
        'type' => 'options_buttons',
      ),
      'default_value' => array(array('value' => 'website')),
    ));

  // create a field and instance for 'field_data_sequential'
  // it is for internal use only, will not be viewed/edited by the user
  field_create_field(array(
      'field_name' => 'field_data_sequential',
      'type' => 'text',
      'entity_types' => array('user'),
      'settings' => array('max_length' => 20000),
    ));
  field_create_instance(array(
      'field_name' => 'field_data_sequential',
      'entity_type' => 'user',
      'bundle' => 'user',
    ));

}
?>
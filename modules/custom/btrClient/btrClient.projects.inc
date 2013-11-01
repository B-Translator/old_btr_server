<?php
/**
 * @file
 * This file contains functions for creating and deleting
 * a custom content type and related fields for translation projects.
 * The page of a project is a central place for all the information
 * and activity related to that translation project.
 *
 * Reference: http://www.thecarneyeffect.co.uk/creating-custom-content-type-adding-fields-programmatically-drupal-7
 */

/**
 * Create a new content type for translation projects.
 * This function is called by hook_install() of btrClient.
 */
function btrClient_create_project_content_type() {
  $t = get_t();

  /**** STEP 1 - Create and save a new content object ****/

  // machine name of the content type
  $content_name = 'projects';

  // define the node type
  $projects = array(
    'type' => $content_name,
    'name' => $t('Translation Projects'),
    'base' => 'node_content',
    'title_label' => $t('Project Title'),
    'description' => $t('Translating a software project.'),
    'custom' => TRUE,
  );

  // set other node defaults not declared above
  $content_type = node_type_set_defaults($projects);
  // add the body field
  node_add_body_field($content_type, $t('Project Description'));

  // save the content type
  node_type_save($content_type);


  /**** STEP 2 - update persistant variables with settings ****/

  // add persistent variables that control settings
  variable_set('additional_settings__active_tab_' . $content_name, 'edit-menu');
  variable_set('node_preview_' . $content_name, 1); // 0 = disabled, 1 = optional, 2 = required
  variable_set('node_options_' . $content_name, array(0 => 'status')); // array(0 => 'status', 1 => 'promote', 2 => 'sticky', 3 => 'revision') remove to uncheck
  variable_set('node_submitted_' . $content_name, 0); // 1 = Display author and date information, 0 = none
  variable_set('menu_options_' . $content_name, array(0 => 'main_menu'));
  variable_set('menu_parent_' . $content_name, 'main-menu:0');


  /**** STEP 3 - create and add instances of new fields ****/

  // create all the fields we are adding to our content type
  foreach (_btrClient_project_content_type_fields() as $field) {
    field_create_field($field);
  }

  // create all the instances for our fields
  foreach (_btrClient_project_content_type_instances() as $instance) {
    $instance['entity_type'] = 'node';
    $instance['bundle'] = $projects['type'];
    field_create_instance($instance);
  }
}


/**
 * Delete the project content type and anything related to it
 * This function is called by hook_uninstall() of btrClient.
 */
function btrClient_delete_project_content_type() {
  // machine name of the content type
  $content_name = 'projects';

  // gather all project nodes created
  $sql = 'SELECT nid FROM {node} n WHERE n.type = :type';
  $result = db_query($sql, array(':type' => $content_name));
  $nids = array();
  foreach ($result as $row) {
    $nids[] = $row->nid;
  }

  // delete all the project nodes at once
  node_delete_multiple($nids);

  // remove persistant variables that control settings
  variable_del('additional_settings__active_tab_' . $content_name);
  variable_del('node_preview_' . $content_name);
  variable_del('node_options_' . $content_name);
  variable_del('node_submitted_' . $content_name);
  variable_del('menu_options_' . $content_name);
  variable_del('menu_parent_' . $content_name);

  // delete our content type
  node_type_delete($content_name);

  // find all fields and delete them
  foreach (array_keys(_btrClient_project_content_type_fields()) as $field) {
    field_delete_field($field);
  }

  // find all fields and delete instance
  $instances = field_info_instances('node', $content_name);
  foreach ($instances as $instance_name => $instance) {
    field_delete_instance($instance);
  }

  // purge all field info
  field_purge_batch(1000);
}

/**
 * Returns a structured array defining the fields created by the project content type.
 *
 * @return
 *  An associative array specifying the fields we wish to add to our
 *  new content type.
 */
function _btrClient_project_content_type_fields() {
  return array(
    'field_project_origin' => array(
      'translatable' => '0',
      'entity_types' => array(),
      'settings' => array(
        'max_length' => '50',
      ),
      'storage' => array(
        'type' => 'field_sql_storage',
        'settings' => array(),
        'module' => 'field_sql_storage',
        'active' => '1',
        'details' => array(
          'sql' => array(
            'FIELD_LOAD_CURRENT' => array(
              'field_data_field_project_origin' => array(
                'value' => 'field_project_origin_value',
                'format' => 'field_project_origin_format',
              ),
            ),
            'FIELD_LOAD_REVISION' => array(
              'field_revision_field_project_origin' => array(
                'value' => 'field_project_origin_value',
                'format' => 'field_project_origin_format',
              ),
            ),
          ),
        ),
      ),
      'foreign keys' => array(
        'format' => array(
          'table' => 'filter_format',
          'columns' => array(
            'format' => 'format',
          ),
        ),
      ),
      'indexes' => array(
        'format' => array(
          'format',
        ),
      ),
      'field_name' => 'field_project_origin',
      'type' => 'text',
      'module' => 'text',
      'active' => '1',
      'locked' => '0',
      'cardinality' => '1',
      'deleted' => '0',
      'columns' => array(
        'value' => array(
          'type' => 'varchar',
          'length' => '50',
          'not null' => FALSE,
        ),
        'format' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => FALSE,
        ),
      ),
      'bundles' => array(
        'node' => array(
          'projects',
        ),
      ),
    ),
    'field_project_name' => array(
      'translatable' => '0',
      'entity_types' => array(),
      'settings' => array(
        'max_length' => '50',
      ),
      'storage' => array(
        'type' => 'field_sql_storage',
        'settings' => array(),
        'module' => 'field_sql_storage',
        'active' => '1',
        'details' => array(
          'sql' => array(
            'FIELD_LOAD_CURRENT' => array(
              'field_data_field_project_name' => array(
                'value' => 'field_project_name_value',
                'format' => 'field_project_name_format',
              ),
            ),
            'FIELD_LOAD_REVISION' => array(
              'field_revision_field_project_name' => array(
                'value' => 'field_project_name_value',
                'format' => 'field_project_name_format',
              ),
            ),
          ),
        ),
      ),
      'foreign keys' => array(
        'format' => array(
          'table' => 'filter_format',
          'columns' => array(
            'format' => 'format',
          ),
        ),
      ),
      'indexes' => array(
        'format' => array(
          'format',
        ),
      ),
      'field_name' => 'field_project_name',
      'type' => 'text',
      'module' => 'text',
      'active' => '1',
      'locked' => '0',
      'cardinality' => '1',
      'deleted' => '0',
      'columns' => array(
        'value' => array(
          'type' => 'varchar',
          'length' => '50',
          'not null' => FALSE,
        ),
        'format' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => FALSE,
        ),
      ),
      'bundles' => array(
        'node' => array(
          'projects',
        ),
      ),
    ),
    'field_project_icon' => array(
      'translatable' => '0',
      'entity_types' => array(),
      'settings' => array(
        'uri_scheme' => 'public',
        'default_image' => 0,
      ),
      'storage' => array(
        'type' => 'field_sql_storage',
        'settings' => array(),
        'module' => 'field_sql_storage',
        'active' => '1',
        'details' => array(
          'sql' => array(
            'FIELD_LOAD_CURRENT' => array(
              'field_data_field_project_icon' => array(
                'fid' => 'field_project_icon_fid',
                'alt' => 'field_project_icon_alt',
                'title' => 'field_project_icon_title',
                'width' => 'field_project_icon_width',
                'height' => 'field_project_icon_height',
              ),
            ),
            'FIELD_LOAD_REVISION' => array(
              'field_revision_field_project_icon' => array(
                'fid' => 'field_project_icon_fid',
                'alt' => 'field_project_icon_alt',
                'title' => 'field_project_icon_title',
                'width' => 'field_project_icon_width',
                'height' => 'field_project_icon_height',
              ),
            ),
          ),
        ),
      ),
      'foreign keys' => array(
        'fid' => array(
          'table' => 'file_managed',
          'columns' => array(
            'fid' => 'fid',
          ),
        ),
      ),
      'indexes' => array(
        'fid' => array(
          'fid',
        ),
      ),
      'field_name' => 'field_project_icon',
      'type' => 'image',
      'module' => 'image',
      'active' => '1',
      'locked' => '0',
      'cardinality' => '1',
      'deleted' => '0',
      'columns' => array(
        'fid' => array(
          'description' => 'The {file_managed}.fid being referenced in this field.',
          'type' => 'int',
          'not null' => FALSE,
          'unsigned' => TRUE,
        ),
        'alt' => array(
          'description' => "Alternative image text, for the image's 'alt' attribute.",
          'type' => 'varchar',
          'length' => 512,
          'not null' => FALSE,
        ),
        'title' => array(
          'description' => "Image title text, for the image's 'title' attribute.",
          'type' => 'varchar',
          'length' => 1024,
          'not null' => FALSE,
        ),
        'width' => array(
          'description' => 'The width of the image in pixels.',
          'type' => 'int',
          'unsigned' => TRUE,
        ),
        'height' => array(
          'description' => 'The height of the image in pixels.',
          'type' => 'int',
          'unsigned' => TRUE,
        ),
      ),
      'bundles' => array(
        'node' => array(
          'projects',
        ),
      ),
    ),
    'field_project_screenshots' => array(
      'translatable' => '0',
      'entity_types' => array(),
      'settings' => array(
        'uri_scheme' => 'public',
        'default_image' => 0,
      ),
      'storage' => array(
        'type' => 'field_sql_storage',
        'settings' => array(),
        'module' => 'field_sql_storage',
        'active' => '1',
        'details' => array(
          'sql' => array(
            'FIELD_LOAD_CURRENT' => array(
              'field_data_field_project_screenshots' => array(
                'fid' => 'field_project_screenshots_fid',
                'alt' => 'field_project_screenshots_alt',
                'title' => 'field_project_screenshots_title',
                'width' => 'field_project_screenshots_width',
                'height' => 'field_project_screenshots_height',
              ),
            ),
            'FIELD_LOAD_REVISION' => array(
              'field_revision_field_project_screenshots' => array(
                'fid' => 'field_project_screenshots_fid',
                'alt' => 'field_project_screenshots_alt',
                'title' => 'field_project_screenshots_title',
                'width' => 'field_project_screenshots_width',
                'height' => 'field_project_screenshots_height',
              ),
            ),
          ),
        ),
      ),
      'foreign keys' => array(
        'fid' => array(
          'table' => 'file_managed',
          'columns' => array(
            'fid' => 'fid',
          ),
        ),
      ),
      'indexes' => array(
        'fid' => array(
          'fid',
        ),
      ),
      'field_name' => 'field_project_screenshots',
      'type' => 'image',
      'module' => 'image',
      'active' => '1',
      'locked' => '0',
      'cardinality' => '5',
      'deleted' => '0',
      'columns' => array(
        'fid' => array(
          'description' => 'The {file_managed}.fid being referenced in this field.',
          'type' => 'int',
          'not null' => FALSE,
          'unsigned' => TRUE,
        ),
        'alt' => array(
          'description' => "Alternative image text, for the image's 'alt' attribute.",
          'type' => 'varchar',
          'length' => 512,
          'not null' => FALSE,
        ),
        'title' => array(
          'description' => "Image title text, for the image's 'title' attribute.",
          'type' => 'varchar',
          'length' => 1024,
          'not null' => FALSE,
        ),
        'width' => array(
          'description' => 'The width of the image in pixels.',
          'type' => 'int',
          'unsigned' => TRUE,
        ),
        'height' => array(
          'description' => 'The height of the image in pixels.',
          'type' => 'int',
          'unsigned' => TRUE,
        ),
      ),
      'bundles' => array(
        'node' => array(
          'projects',
        ),
      ),
    ),
  );
}

/**
 * Returns a structured array defining the instances for the project content type.
 *
 * @return
 *  An associative array specifying the instances we wish to add to our new
 *  content type.
 */
function _btrClient_project_content_type_instances() {
  return array(
    'field_project_origin' => array(
      'label' => 'Project Origin',
      'widget' => array(
        'weight' => '0',
        'type' => 'text_textfield',
        'module' => 'text',
        'active' => 1,
        'settings' => array(
          'size' => '60',
        ),
      ),
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'type' => 'text_default',
          'settings' => array(),
          'module' => 'text',
          'weight' => 2,
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'above',
          'settings' => array(),
          'weight' => 0,
        ),
      ),
      'required' => 1,
      'description' => 'The origin of the project, as registered by the import (for example: KDE, GNOME, Mozilla, etc.) See a <a href="translations/project/list/*/-/txt" target="_blank">list of available origins</a> that can be used.',
      'default_value' => NULL,
      'field_name' => 'field_project_origin',
      'entity_type' => 'node',
      'bundle' => 'projects',
      'deleted' => '0',
    ),
    'field_project_name' => array(
      'label' => 'Project Name',
      'widget' => array(
        'weight' => '1',
        'type' => 'text_textfield',
        'module' => 'text',
        'active' => 1,
        'settings' => array(
          'size' => '60',
        ),
      ),
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'type' => 'text_default',
          'settings' => array(),
          'module' => 'text',
          'weight' => 1,
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'above',
          'settings' => array(),
          'weight' => 0,
        ),
      ),
      'required' => 1,
      'description' => 'The name of the project, as registered during import (for example: kturtle or pingus.)',
      'default_value' => NULL,
      'field_name' => 'field_project_name',
      'entity_type' => 'node',
      'bundle' => 'projects',
      'deleted' => '0',
    ),
    'field_project_icon' => array(
      'label' => 'Project Icon',
      'widget' => array(
        'weight' => '4',
        'type' => 'image_image',
        'module' => 'image',
        'active' => 1,
        'settings' => array(
          'progress_indicator' => 'throbber',
          'preview_image_style' => 'large',
        ),
      ),
      'settings' => array(
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'alt_field' => 0,
        'title_field' => 0,
        'default_image' => 0,
        'user_register_form' => FALSE,
      ),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'type' => 'image',
          'settings' => array(
            'image_style' => '',
            'image_link' => '',
          ),
          'module' => 'image',
          'weight' => 3,
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'above',
          'settings' => array(),
          'weight' => 0,
        ),
      ),
      'required' => 0,
      'description' => 'The icon that usually represents the project (if any).',
      'field_name' => 'field_project_icon',
      'entity_type' => 'node',
      'bundle' => 'projects',
      'deleted' => '0',
    ),
    'field_project_screenshots' => array(
      'label' => 'Project Screenshots',
      'widget' => array(
        'weight' => '5',
        'type' => 'image_image',
        'module' => 'image',
        'active' => 1,
        'settings' => array(
          'progress_indicator' => 'throbber',
          'preview_image_style' => 'thumbnail',
        ),
      ),
      'settings' => array(
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'alt_field' => 0,
        'title_field' => 0,
        'default_image' => 0,
        'user_register_form' => FALSE,
      ),
      'display' => array(
        'default' => array(
          'label' => 'above',
          'type' => 'image',
          'settings' => array(
            'image_style' => '',
            'image_link' => '',
          ),
          'module' => 'image',
          'weight' => 4,
        ),
        'teaser' => array(
          'type' => 'hidden',
          'label' => 'above',
          'settings' => array(),
          'weight' => 0,
        ),
      ),
      'required' => 0,
      'description' => 'Any screenshots from the project.',
      'field_name' => 'field_project_screenshots',
      'entity_type' => 'node',
      'bundle' => 'projects',
      'deleted' => '0',
    ),
  );
}

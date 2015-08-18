<?php

// Set variables
$old_name = 'field_preferred_projects';
$new_name = 'field_projects';
$entity_type = 'user';
$bundle = 'user';

// Get old field info
$old_field = field_info_field($old_name);

// Create new field
$new_field = $old_field;
$new_field['field_name'] = $new_name;

if (!field_info_field($new_name)) {
  field_create_field($new_field);
}
else {
  field_update_field($new_field);
}

// Get old field instance
$old_instance = field_info_instance($entity_type, $old_name, $bundle);
$new_instance = $old_instance;
$new_instance['field_name'] = $new_name;

if (!field_info_instance($entity_type, $new_name, $bundle)) {
  field_create_instance($new_instance);
}
else {
  field_update_instance($new_instance);
}

// Migrate old fields' data to the new ones
$field_data = db_select('field_data_' . $old_name, 'old')
  ->fields('old')
  ->condition('entity_type', $entity_type)
  ->condition('bundle', $bundle)
  ->execute();

while ($data = $field_data->fetchAssoc()) {
  $data_new = array();
  foreach ($data as $column => $value) {
    $column = str_replace($old_name, $new_name, $column);
    $data_new[$column] = $value;
  }
  db_insert('field_data_' . $new_name)
    ->fields($data_new)
    ->execute();
}

// Migrate old fields' revision data to the new ones
$field_revision = db_select('field_revision_' . $old_name, 'old')
  ->fields('old')
  ->condition('entity_type', $entity_type)
  ->condition('bundle', $bundle)
  ->execute();

while ($revision = $field_revision->fetchAssoc()) {
  $revision_new = array();
  foreach ($revision as $column => $value) {
    $column = str_replace($old_name, $new_name, $column);
    $revision_new[$column] = $value;
  }
  db_insert('field_revision_' . $new_name)
    ->fields($revision_new)
    ->execute();
}

// Delete old instance
field_delete_instance($old_instance);

// Purge fields
field_purge_batch(1000);


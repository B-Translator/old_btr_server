<?php
/**
 * @file
 * btr_btrClient.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btr_btrClient_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'btrClient_topcontrib_period';
  $strongarm->value = 'week';
  $export['btrClient_topcontrib_period'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'btrClient_topcontrib_size';
  $strongarm->value = '5';
  $export['btrClient_topcontrib_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'btr_export_notify_admin';
  $strongarm->value = 1;
  $export['btr_export_notify_admin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'btr_export_path';
  $strongarm->value = '/var/www/exports';
  $export['btr_export_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'btr_preferred_projects';
  $strongarm->value = 'test';
  $export['btr_preferred_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'btr_translation_lng';
  $strongarm->value = 'sq';
  $export['btr_translation_lng'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'btr_voting_mode';
  $strongarm->value = 'single';
  $export['btr_voting_mode'] = $strongarm;

  return $export;
}

<?php
/**
 * @file
 * btranslator_l10n_feedback.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btranslator_l10n_feedback_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_export_notify_admin';
  $strongarm->value = 1;
  $export['l10n_feedback_export_notify_admin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_export_path';
  $strongarm->value = '/var/www/exports';
  $export['l10n_feedback_export_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_preferred_projects';
  $strongarm->value = 'test';
  $export['l10n_feedback_preferred_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_topcontrib_period';
  $strongarm->value = 'week';
  $export['l10n_feedback_topcontrib_period'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_topcontrib_size';
  $strongarm->value = '5';
  $export['l10n_feedback_topcontrib_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_translation_lng';
  $strongarm->value = 'sq';
  $export['l10n_feedback_translation_lng'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_voting_mode';
  $strongarm->value = 'single';
  $export['l10n_feedback_voting_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_projects';
  $strongarm->value = array(
    0 => 'main_menu',
  );
  $export['menu_options_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_projects';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_projects';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_projects';
  $strongarm->value = 1;
  $export['node_preview_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_projects';
  $strongarm->value = 0;
  $export['node_submitted_projects'] = $strongarm;

  return $export;
}

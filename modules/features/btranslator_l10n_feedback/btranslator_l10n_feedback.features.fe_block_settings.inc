<?php
/**
 * @file
 * btranslator_l10n_feedback.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function btranslator_l10n_feedback_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['l10n_feedback-latest'] = array(
    'cache' => -2,
    'custom' => '0',
    'delta' => 'latest',
    'module' => 'l10n_feedback',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap1',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['l10n_feedback-statistics'] = array(
    'cache' => -2,
    'custom' => '0',
    'delta' => 'statistics',
    'module' => 'l10n_feedback',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap1',
        'weight' => '-19',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['l10n_feedback-topcontrib'] = array(
    'cache' => -2,
    'custom' => '0',
    'delta' => 'topcontrib',
    'module' => 'l10n_feedback',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap1',
        'weight' => '-18',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  return $export;
}

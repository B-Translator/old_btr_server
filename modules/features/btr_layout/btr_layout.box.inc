<?php
/**
 * @file
 * btr_layout.box.inc
 */

/**
 * Implements hook_default_box().
 */
function btr_layout_default_box() {
  $export = array();

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'headerbox';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Displays the title and slogan at the top of the front page.';
  $box->options = array(
    'body' => array(
      'value' => '<p>Përkthimi i Programeve - E Duam Kompjuterin Shqip</p>',
      'format' => 'filtered_html',
    ),
    'additional_classes' => '',
  );
  $export['headerbox'] = $box;

  return $export;
}

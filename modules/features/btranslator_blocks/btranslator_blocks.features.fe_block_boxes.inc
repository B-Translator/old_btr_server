<?php
/**
 * @file
 * btranslator_blocks.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function btranslator_blocks_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Display the title/slogan at the top of the site.';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'titleslogan';
  $fe_block_boxes->body = '<div class="page-title" style="text-align: center;"><span style="font-size: x-large;"><strong><span style="font-family: \'comic sans ms\', sans-serif; color: #ff0000;">Përkthimi i Programeve - E Duam Kompjuterin Shqip</span></strong></span></div><div class="page-title" style="text-align: center;"><span style="font-family: \'comic sans ms\', sans-serif; font-size: xx-large; color: #ff0000;">&nbsp;</span></div>';

  $export['titleslogan'] = $fe_block_boxes;

  return $export;
}

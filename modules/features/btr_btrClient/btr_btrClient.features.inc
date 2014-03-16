<?php
/**
 * @file
 * btr_btrClient.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function btr_btrClient_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

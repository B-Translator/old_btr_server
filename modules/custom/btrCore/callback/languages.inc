<?php

/**
 * Menu callback for 'languages'.
 * Returns a json list of languages and their details.
 */
function btrCore_languages() {
  $languages = btr::languages_get_details();
  drupal_json_output($languages);
  drupal_exit();
}

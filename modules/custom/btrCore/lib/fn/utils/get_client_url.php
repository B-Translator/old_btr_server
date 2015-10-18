<?php
/**
 * @file
 * Function: utils_get_client_url()
 */

namespace BTranslator;

/**
 * Return the url of the client site of a language, or the default client url
 * if the site of that language is not defined.
 */
function utils_get_client_url($lng) {
  $sites = btr_get_sites();
  if ( isset($sites[$lng]['url']) ) {
    $site_url = $sites[$lng]['url'];
  }
  else {
    $site_url = variable_get('btr_client', 'https://l10n.example.org');
  }

  return $site_url;
}

/**
 * Return an array of sites for each language
 * and their metadata (like url etc.)
 */
function btr_get_sites() {
  return [
    'fr' => [
      //'url' => 'https://example.org',
    ],
    'sq' => [
      //'url' => 'https://l10n.org.al',
    ],
  ];
}

<?php
/**
 * @file
 * Return a random string in a suitable form for the twitter.
 *
 * If the request header 'Accept: application/json' is set, then
 * the output will be in JSON, for example:
 *   curl -k -i -H 'Accept: application/json' \
 *        'https://dev.btranslator.org/translations/twitter/sq/test'
 * This can be useful for adding your custom hashtags, url, etc.
 */

function btrCore_twitter($lng =NULL, $origin =NULL, $project =NULL) {
  if (empty($lng))  $lng = 'fr';

  // Get the search scope.
  $scope = "vocabulary/ICT_$lng";
  if (!empty($origin)) {
    $scope = $origin;
    if (!empty($project)) {
      $scope .= '/' . $project;
    }
  }

  // Get a translated string shorter than 50 chars.
  $i = 0;
  do {
    list($sguid, $messages) = btr_get_random_sguid('translated', $lng, array($scope));
    list($string, $translations) = btr_get_string_and_translations($sguid, $lng);
    $i++;
  } while (strlen($string) > 50 and $i < 10);

  // Build the tweet
  if (empty($string)) {
    $twitter = t('Error: No string found!');
  }
  else {
    $twitter = $string . ' <==> ';
    $twitter .= implode(' / ', $translations);
    if (strlen($twitter) > 100) {
      $twitter = substr($twitter, 0, strrpos(substr($twitter, 0, 100-3), ' '));
      $twitter .= '...';
    }
  }

  // If the request has the header 'Accept: application/json'
  // return the output in JSON format.
  if ($_SERVER['HTTP_ACCEPT'] == 'application/json') {
    //drupal_add_http_header('Content-Type', 'application/json; utf-8');
    print drupal_json_encode(array(
        'lng' => $lng,
        'sguid' => $sguid,
        'twitter' => $twitter,
      ));
    exit;
  }

  // Append hash tags.
  $twitter .= " #l10n_$lng";
  if (!empty($origin))  $twitter .= " #$origin";
  if (!empty($project)) $twitter .= " #$project";

  // Append the url.
  module_load_include('inc', 'btrCore', 'includes/sites');
  $base_url = btr_get_base_url($lng);
  $twitter .= ' ' . $base_url . "/translations/$lng/$sguid";

  print $twitter;
  exit(0);
}
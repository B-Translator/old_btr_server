<?php
/**
 * @file
 * Return a random string in a suitable form for the twitter.
 */

function btrCore_twitter($lng =NULL, $origin =NULL, $project =NULL) {
  if (empty($lng))  $lng = 'fr';

  // Get the search scope.
  $scope = 'vocabulary';
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

  // Append hash tags.
  $twitter .= " #l10n_$lng";
  if (!empty($origin))  $twitter .= " #$origin";
  if (!empty($project)) $twitter .= " #$project";

  // Append the url.
  module_load_include('inc', 'btrCore', 'includes/sites');
  $sites = btr_get_sites();
  $base_url = isset($sites[$lng]['base_url']) ? $sites[$lng]['base_url'] : $GLOBALS['base_url'];
  $url = $base_url . "/translations/$lng/$sguid";
  $twitter .= ' ' . $url;

  print $twitter;
  exit(0);
}
<?php
/**
 * @file
 * Return a random string in a suitable form for the twitter.
 */

function btrCore_twitter($lng =NULL, $origin =NULL, $project =NULL) {
  if (empty($lng)) {
    $lng = variable_get('btr_translation_lng', 'fr');
  }

  // Get the search scope.
  $scope = 'misc/vocabulary';
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
  if ($lng == 'sq' and $scope == 'misc/vocabulary') {
    $twitter .= ' #fjalori';
  }
  else {
    if (!empty($origin))  $twitter .= " #$origin";
    if (!empty($project)) $twitter .= " #$project";
  }

  // Append the url.
  $url = url("translations/$lng/$sguid", array('absolute' => TRUE));
  $twitter .= ' ' . $url;

  print $twitter;
  exit(0);
}
<?php
/**
 * @file
 * Return a random string in a suitable form for the twitter.
 */

function btrCore_twitter($lng =NULL) {
  if (empty($lng)) {
    $lng = variable_get('btr_translation_lng', 'fr');
  }

  $sguid = btr_sguid_get_random(NULL, array('misc/vocabulary'));
  list($string, $translations) = btr_get_string_and_translations($sguid, $lng);

  $twitter = $string . ' <==> ';
  $twitter .= implode(' / ', $translations);

  if (strlen($twitter) > 100) {
    $twitter = substr($twitter, 0, strrpos(substr($twitter, 0, 100-3), ' '));
    $twitter .= '...';
  }

  $url = url("translations/$lng/$sguid", array('absolute' => TRUE));
  $twitter .= " #fjalori $url";

  print $twitter;
  exit(0);
}
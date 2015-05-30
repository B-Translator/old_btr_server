<?php
namespace BTranslator;
use \btr;

/**
 * Send by email a string to be reviewed.
 */
{
  list($string, $translations) = btr::string_get_translations($params->sguid, $lng);
  // Get the url of the string.
  list($origin, $project) = explode('/', $params->project);
  $app_url = btr_get_app_url($lng, $origin, $project);
  if ($app_url and $origin=='vocabulary') {
    $url = "$app_url?lng=$lng&proj=$project#$string";
  }

  $subject = "[$subject_prefix] " . cut($string, 60);
  $body = array(
    t("Greetings !username,

       If you have time, please help to review the translation
       of the string at this link: !url

       Thanks

       ---------- Original (English) String:
       !string
       ---------- Available Translations:
      ",
      array(
        '!username' => $params->username,
        '!url' => $url,
        '!string' => $string,
      )),
  );
  foreach ($translations as $translation) {
    $body[] = ' * ' . $translation;
  }
}

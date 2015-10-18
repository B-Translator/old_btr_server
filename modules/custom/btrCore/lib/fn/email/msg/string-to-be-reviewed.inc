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
  $app_url = btr::utils_get_app_url($lng, $origin, $project);
  if ($app_url and $origin=='vocabulary') {
    $url = "$app_url?lng=$lng&proj=$project#$string";
  }
  elseif ($project) {
    $client_url = btr::utils_get_client_url($lng);
    $url = $client_url . "/btr/project/$origin/$project/$lng/" . $params->sguid;
  }

  $subject = "[$subject_prefix] " . cut($string, 60);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t('If you have time, please help to review the translation of the string at this link:');
  $body[] = $url;
  $body[] = t('Thanks');

  $string_header = t('String:');
  $translations_header = t('Translations:');
  $body[] = "
    <hr/>

    <h4>$string_header</h4>
    <ul>
      <li>$string</li>
    </ul>

    <h4>$translations_header</h4>
    <ul>
  ";
  foreach ($translations as $translation) {
    $body[] = "<li>" . $translation . "</li>\n";
  }
  $body[] = "</ul>\n";
}

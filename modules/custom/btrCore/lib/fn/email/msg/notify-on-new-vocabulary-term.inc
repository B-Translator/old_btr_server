<?php
namespace BTranslator;
use \btr;

/**
 * Notify translators that a new term has been added to the vocabulary.
 */
{
  $subject = "[$params->project] "
    . t('New term: !string', ['!string' => $params->string]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $app_url = btr::utils_get_app_url($lng, 'vocabulary', $params->project);
  if ($app_url) {
    $url = $app_url . '/#' . $params->string;
  }
  else {
    $url = $GLOBALS['base_url'] . '/vocabulary/'
      . $params->project . '/' . $params->string;
  }
  $body[] = t("A new term has been added to the vocabulary !project by !author.
Check it out at the mobile app: !url",
            array(
              '!project' => $params->project,
              '!author' => $params->author,
              '!url' => $url,
            ));
  $body[] = t('Thanks');
}

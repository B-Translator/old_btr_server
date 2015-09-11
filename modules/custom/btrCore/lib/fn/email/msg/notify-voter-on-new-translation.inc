<?php
namespace BTranslator;
use \btr;

/**
 * Notify the previous voters of a string that a new translation has been
 * submitted. Maybe they would like to review it and change their vote.
 */
{
  $subject = "[$subject_prefix]" . t('New translation for: !string',
             ['!string' => cut($params->string, 30)]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);

  $body[] = t("A new translation has been suggested for a string
that you have voted for. If you think that the new
translation is more suitable than the one that you have
voted for, then you can change your vote at this link:");
  $body[] = $url;
  $body[] = t('Thanks');

  $string = t('String:');
  $voted_translation = t('Voted Translation:');
  $new_translation = t('New Translation:');
  $body[] = "
    <hr/>

    <h4>$string</h4>
    <ul>
      <li>$params->string</li>
    </ul>

    <h4>$voted_translation</h4>
    <ul>
      <li>$params->voted_translation</li>
    </ul>

    <h4>$new_translation</h4>
    <ul>
      <li>$params->new_translation</li>
    </ul>
  ";
}

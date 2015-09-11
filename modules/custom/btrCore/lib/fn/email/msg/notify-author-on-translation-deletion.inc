<?php
namespace BTranslator;
use \btr;

/**
 * Notify the author of a translation, when it is deleted.
 */
{
  $subject = "[$subject_prefix] "
    . t('Translation deleted: !translation',
      ['!translation' => cut($params->translation, 30)]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t("A translation that you have submitted, has been deleted by a moderator.
You can see the string and the rest of translations at this link:");
  $body[] = $url;
  $body[] = t('Thanks');

  $string = t('String:');
  $deleted_translation = t('Deleted Translation:');
  $body[] = "
    <hr/>

    <h4>$string</h4>
    <ul>
      <li>$params->string</li>
    </ul>

    <h4>$deleted_translation</h4>
    <ul>
      <li>$params->translation</li>
    </ul>
  ";
}

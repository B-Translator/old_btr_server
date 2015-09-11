<?php
namespace BTranslator;
use \btr;

/**
 * Notify the voters of a translation, when it is deleted.
 */
{
  $subject = "[$subject_prefix] "
    . t('Translation deleted: !translation',
      ['!translation' => cut($params->translation, 30)]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t("A translation that you have voted, has been deleted by a moderator.
You can see the string and the rest of translations at this link:");
  $body[] = $url;
  $body[] = t('Thanks');

  $string_header = t('String:');
  $deleted_translation = t('Deleted Translation:');
  $body[] = "
    <hr/>

    <h4>$string_header</h4>
    <ul>
      <li>$params->string</li>
    </ul>

    <h4>$deleted_translation</h4>
    <ul>
      <li>$params->translation</li>
    </ul>
  ";
}

<?php
namespace BTranslator;
use \btr;

/**
 * Send an email notification to a user, when a translation that he has voted
 * for is modified.
 */
{
  $subject = "[$subject_prefix] "
    . t("Translation modified for: !string",
      ['!string' => cut($params->string, 30)]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t("The following translation has been modified by its author.
You are being notified because you have voted for the old
translation and your vote now counts for the new version
of the translation.

If the new version of the translation is OK for you,
then there is nothing you should do. Otherwise, you
can change your vote at this link:");
  $body[] = $url;
  $body[] = t('Thanks');

  $string = t('String:');
  $old_translation = t('Old Translation:');
  $new_translation = t('New Translation:');
  $body[] = "
    <hr/>

    <h4>$string:</h4>
    <ul>
      <li>$params->string</li>
    </ul>

    <h4>$old_translation</h4>
    <ul>
      <li>$params->old_translation</li>
    </ul>

    <h4>$new_translation</h4>
    <ul>
      <li>$params->new_translation</li>
    </ul>
   ";
}

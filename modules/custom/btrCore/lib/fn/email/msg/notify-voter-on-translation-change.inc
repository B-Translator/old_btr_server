<?php
namespace BTranslator;
use \btr;

/**
 * Send an email notification to a user, when a translation that he has voted
 * for is modified.
 */
{
  $subject = t("[!prefix] Translation modified for: !string",
             array(
               '!prefix' => $subject_prefix,
               '!string' => cut($params->string, 30),
             ));
  $body = array(
    t("Greetings !username,

       The following translation has been modified by its author.
       You are being notified because you have voted for the old
       translation and your vote now counts for the new version
       of the translation.

       If the new version of the translation is OK for you,
       then there is nothing you should do. Otherwise, you
       can change your vote at this link: !url

       Thanks

       ---------- Original (English) String:
       !string
       ---------- Old Translation:
       !old_translation
       ---------- New Translation:
       !new_translation
       ----------
      ",
      array(
        '!username' => $params->username,
        '!url' => $url,
        '!string' => $params->string,
        '!old_translation' => $params->old_translation,
        '!new_translation' => $params->new_translation,
      )),
  );

}

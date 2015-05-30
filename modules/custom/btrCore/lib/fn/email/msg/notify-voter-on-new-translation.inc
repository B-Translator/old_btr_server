<?php
/**
 * Notify the previous voters of a string that a new translation has been
 * submitted. Maybe they would like to review it and change their vote.
 */
{
  $subject = t("[!prefix] New translation for: !string",
             array(
               '!prefix' => $subject_prefix,
               '!string' => btrCore_shorten($params->string, 30),
             ));
  $body = array(
    t("Greetings !username,

       A new translation has been suggested for a string
       that you have voted for. If you think that the new
       translation is more suitable than the one that you
       have voted for, then you can change your vote
       at this link: !url

       Thanks

       ---------- Original (English) String:
       !string
       ---------- Voted Translation:
       !voted_translation
       ---------- New Translation:
       !new_translation
       ----------
      ",
      array(
        '!username' => $params->username,
        '!url' => $url,
        '!string' => $params->string,
        '!voted_translation' => $params->voted_translation,
        '!new_translation' => $params->new_translation,
      )),
  );
}

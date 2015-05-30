<?php
/**
 * Notify the voters of a translation, when it is deleted.
 */
{
  $subject = t("[!prefix] Translation deleted: !translation",
             array(
               '!prefix' => $subject_prefix,
               '!translation' => btrCore_shorten($params->translation, 30),
             ));
  $body = array(
    t("Greetings !username,

       A translation that you have voted, has been deleted by a moderator.
       You can see the string and the rest of translations at this link: !url

       Thanks

       ---------- Original (English) String:
       !string
       ---------- Deleted Translation:
       !translation
       ----------
      ",
      array(
        '!username' => $params->username,
        '!url' => $url,
        '!string' => $params->string,
        '!translation' => $params->translation,
      )),
  );
}

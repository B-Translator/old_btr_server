<?php
namespace BTranslator;
use \btr;

/**
 * Notify the user that the import is done.
 */
{
  $subject = t("[!prefix] Import of !filename",
             array(
               '!prefix' => $subject_prefix,
               '!filename' => $params->filename,
             ));
  $body = array(
    t("Greetings !username,

       The import of '!filename', that you have requested, is done.
       Check out the new translations here:
       !search_url
      ",
      array(
        '!username' => $params->username,
        '!filename' => $params->filename,
        '!search_url' => $params->search_url,
      )),
  );
  if ($params->messages) {
    $body .= "\n\n" . t('Output messages:') . "\n" . $params->messages;
  }
}

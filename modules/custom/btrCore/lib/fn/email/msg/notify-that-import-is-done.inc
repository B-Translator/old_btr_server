<?php
namespace BTranslator;
use \btr;

/**
 * Notify the user that the import is done.
 */
{
  $subject = "[$subject_prefix] "
    . t('Import of !filename', ['!filename' => $params->filename]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t("The import of the file '!filename', that you have requested,
is done. Check out the new translations here:",
            ['!filename' => $params->filename]);
  $body[] = $params->search_url;
  $body[] = t('Thanks');

  if ($params->messages) {
    $output_messages = t('Output messages:');
    $body[] = "
      <hr/>
      <h4>$output_messages</h4>
      <xmp>$params->messages</xmp>
    ";
  }
}

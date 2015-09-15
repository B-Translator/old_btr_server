<?php
namespace BTranslator;
use \btr;

/**
 * Notify the user that the project import is done.
 */
{
  $subject = "[$subject_prefix] "
    . t('Import of project !project', ['!project' => $params->project]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t("The import of the project '!project', that you have requested,
is done. Check it out here:",
            ['!project' => $params->project]);
  $body[] = $params->url;
  $body[] = t('Thanks');

  if ($params->output) {
    $output_messages = t('Output messages:');
    $body[] = "
      <hr/>
      <h4>$output_messages</h4>
      <xmp>$params->output</xmp>
    ";
  }

}

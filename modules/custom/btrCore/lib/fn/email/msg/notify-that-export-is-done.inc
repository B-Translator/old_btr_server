<?php
namespace BTranslator;
use \btr;

/**
 * Notify the user that the export is ready for download.
 */
{
  $subject = "[$subject_prefix] "
    . t('Export: !project', ['!project' => $params->project]);

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t("The export of the project '!project', that you have requested,
is done. You can download it from these links:",
            ['!project' => $params->project]);
  $body[] = "
    <ul>
      <li>$params->export_url_tgz</li>
      <li>$params->export_url_diff</li>
      <li>$params->export_url_ediff</li>
    </ul>
  ";
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

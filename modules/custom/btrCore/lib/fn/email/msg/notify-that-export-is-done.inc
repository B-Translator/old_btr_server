<?php
namespace BTranslator;
use \btr;

/**
 * Notify the user that the export is ready for download.
 */
{
  $subject = t("[!prefix] Export: !project",
             array(
               '!prefix' => $subject_prefix,
               '!project' => $params->project,
             ));
  $body = array(
    t("Greetings !username,

       The export of '!project', that you have requested, is done.
       You can download it from these links:
       * !export_url_tgz
       * !export_url_diff
       * !export_url_ediff
      ",
      array(
        '!username' => $params->username,
        '!project' => $params->project,
        '!export_url_tgz' => $params->export_url_tgz,
        '!export_url_diff' => $params->export_url_diff,
        '!export_url_ediff' => $params->export_url_ediff,
      )),
  );
}

<?php
namespace BTranslator;
use \btr;

/**
 * Notify admin about an export request.
 */
{
  $subject = t("[!prefix] Export request: !origin/!project",
             array(
               '!prefix' => $subject_prefix,
               '!project' => $params->project,
               '!origin' => $params->origin,
             ));
  $body = array(
    t("Export request by user !uid for '!origin/!project'.",
      array(
        '!uid' => $params->uid,
        '!project' => $params->project,
        '!origin' => $params->origin,
      )),
  );
}

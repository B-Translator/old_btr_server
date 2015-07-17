<?php
namespace BTranslator;
use \btr;

/**
 * Notify admin about an export request.
 */
{
  $subject = "[$subject_prefix] " . t('Export request:')
    . " $params->origin/$params->project";

  $body = array();
  $body[] = t("Export request by user !uid for '!origin/!project'.",
            array(
              '!uid' => $params->uid,
              '!project' => $params->project,
              '!origin' => $params->origin,
            ));
}

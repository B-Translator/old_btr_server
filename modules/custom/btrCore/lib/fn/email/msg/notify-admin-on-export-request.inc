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
  $body[] = t("Export request by '!user' for '!origin/!project/!lng'.", [
              '!user' => $params->username,
              '!origin' => $params->origin,
              '!project' => $params->project,
              '!lng' => $params->lng,
            ]);
  $body[] = "
    <ul>
      <li>export_mode: $params->export_mode</li>
      <li>preferred_voters: $params->preferred_voters</li>
    </ul>
  ";
}

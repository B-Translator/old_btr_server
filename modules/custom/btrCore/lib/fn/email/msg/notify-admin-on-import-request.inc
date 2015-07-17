<?php
namespace BTranslator;
use \btr;

/**
 * Notify admin about an import request.
 */
{
  $subject = "[$subject_prefix] " . t('Import request');

  $body = array();
  $body[] = t('Import request by user !username (!uid): !filename.',
          array(
            '!username' => $params->username,
            '!uid' => $params->uid,
            '!filename' => $params->filename,
          ));
}

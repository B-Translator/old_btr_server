<?php
/**
 * Notify admin about an import request.
 */
{
  $subject = t("[!prefix] Import request",
             array('!prefix' => $subject_prefix));
  $body = array(
    t("Import request by user !username (!uid): !filename.",
      array(
        '!username' => $params->username,
        '!uid' => $params->uid,
        '!filename' => $params->filename,
      )),
  );
}

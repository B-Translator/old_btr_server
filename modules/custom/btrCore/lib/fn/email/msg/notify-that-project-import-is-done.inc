<?php
namespace BTranslator;
use \btr;

/**
 * Notify the user that the project import is done.
 */
{
  $subject = t("[!prefix] Import of project !project",
             array(
               '!prefix' => $subject_prefix,
               '!project' => $params->project,
             ));
  $body = array(
    t("Greetings !username,

       The import of the project '!project', that you have requested,
       is done. Check it out here:
       !search_url
      ",
      array(
        '!username' => $params->username,
        '!project' => $params->project,
        '!search_url' => $params->search_url,
      )),
  );
}

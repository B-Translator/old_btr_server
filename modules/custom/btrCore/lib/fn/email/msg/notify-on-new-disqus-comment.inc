<?php
namespace BTranslator;
use \btr;

/**
 * Notify voters that a new comment has been added.
 */
{
  $subject = t("[!prefix] !title",
             array(
               '!prefix' => $subject_prefix,
               '!title' => $params->title,
             ));
  $body = array(
    t("Greetings !username,

       A new comment has been added to a string that you have voted.
       !link

       -----
       !comment
       -----

       Thanks
      ",
      array(
        '!username' => $params->username,
        '!link' => $params->link,
        '!comment' => $params->comment,
      )),
  );
}

<?php
/**
 * Notify translators that a new term has been added to the vocabulary.
 */
{
  $app_url = btr_get_app_url($lng, 'vocabulary', $params->project);
  $subject = t("[!prefix] New term: !string",
             array(
               '!prefix' => $params->project,
               '!string' => $params->string,
             ));
  $body = array(
    t("Greetings !username,

       A new term has been added to the vocabulary !project by !author.
       Check it out at the mobile app: !url

       Thanks
      ",
      array(
        '!username' => $params->username,
        '!project' => $params->project,
        '!author' => $params->author,
        '!string' => $params->string,
        '!url' => $app_url . '/#' . $params->string,
      )),
  );
}

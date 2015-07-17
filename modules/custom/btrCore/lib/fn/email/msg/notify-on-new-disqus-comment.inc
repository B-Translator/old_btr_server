<?php
namespace BTranslator;
use \btr;

/**
 * Notify voters that a new comment has been added.
 */
{
  $subject = "[$subject_prefix] $params->title";

  $body = array();
  $body[] = t('Greetings !username,', ['!username' => $params->username]);
  $body[] = t('A new comment has been added to a string that you have voted.');
  $body[] = $params->link;
  $body[] = t('Thanks');

  $new_comment = t('New comment:');
  $body[] = "
    <hr/>
    <h4>$new_comment</h4>
    $params->comment
  ";
}

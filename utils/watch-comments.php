#!/usr/bin/drush php-script
<?php
/**
 * Watch the latest Disqus comments for l10n-sq
 * and notify the relevant users about them.
 */

// Process the output from rsstail.
while ($line = fgets(STDIN)){
  if (trim($line) == '') {
    $title = preg_replace('/^Title: /', '', trim(fgets(STDIN)));
    $link = preg_replace('/^Link: /', '', trim(fgets(STDIN)));
    $description = preg_replace('/^Description: /', '', trim(fgets(STDIN)));
    process_comment($title, $link, $description);
  }
}

function process_comment($title, $link, $description) {
  // Extract from the link the language and string id.
  $substr = preg_replace('|.*/translations/|', '', $link);
  $substr = preg_replace('|#comment-.*|', '', $substr);
  list($lng, $sguid) = explode('/', $substr);

  // Get a list of users who have voted for this string.
  $uids = btr::db_query(
    'SELECT u.uid FROM {btr_translations} t
     INNER JOIN {btr_votes} v ON (v.tguid = t.tguid)
     INNER JOIN {btr_users} u ON (u.umail = v.umail AND u.ulng = v.ulng)
     WHERE t.sguid = :sguid AND t.lng = :lng',
    array(':sguid' => $sguid, ':lng' => $lng)
  )->fetchCol();
  if (empty($uids))  return;
  $users = user_load_multiple($uids);

  // Notify each user about this comment.
  foreach ($users as $user) {
    btrCore_send_notification_by_email((object) array(
        'type' => 'notify-on-new-disqus-comment',
        'uid' => $user->uid,
        'username' => $user->name,
        'recipient' => $user->name . ' <' . $user->mail . '>',
        'title' => $title,
        'link' => $link,
        'comment' => $description,
      ));
  }
}

<?php
/*
 * Implements hook_cron().
 */
function l10n_suggestions_cron() {

  $queue = DrupalQueue::get('send_string_emails');
  $queue->createQueue();  // There is no harm in trying to recreate existing.

  $accounts = entity_load('user');
  foreach ($accounts as $account) {
    if ($account->uid < 2) {
      continue; // skip admin
    }

    $account_data = (object) array(
      'uid' => $account->uid,
      'name' => $account->name,
      'pass' => $account->pass,
      'mail' => $account->mail,
      'lng' => $account->language,
      'login' => $account->login,
    );
    $queue->createItem($account_data);
  }
}

/*
 * Implements hook_cron_queue_info().
 */
function l10n_suggestions_cron_queue_info() {
  $queues['send_string_emails'] = array(
    'worker callback' => 'send_string_by_email',
    'time' => 120,
  );
  return $queues;
}

function send_string_by_email($account) {

  require_once(dirname(__FILE__) . '/translations/vote.inc');
  $sguid = l10n_suggestions_get_random_sguid();

  $lng = $account->lng;
  $uid = $account->uid;
  $timestamp = REQUEST_TIME;
  $rehash = user_pass_rehash($account->pass, $timestamp, $account->login);
  $url = url("translations/$sguid/$timestamp.$uid.$rehash", array('absolute' => TRUE));

  $text_message = "
If you have time, please help to review the translation of the string at this link:
$url

Thanks.
";
  $html_message = "
<p>If you have time, please help to review the translation of the string at this link:
<a href='$url'>$url</a></p>

<p>Thanks.</p>
";
  //send_html_mail($from_name, $from_email, $to, $subject, $html_message, $text_message);
  send_html_mail('l10n-sq.org', 'noreply@l10n-sq.org', $account->mail, 'Translations', $html_message, $text_message);
}
?>
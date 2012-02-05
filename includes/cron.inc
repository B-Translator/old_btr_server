<?php
/*
 * Implements hook_cron().
 */
function l10n_suggestions_cron() {

  $queue = DrupalQueue::get('send_string_emails');
  $queue->createQueue();  // There is no harm in trying to recreate existing.

  $accounts = entity_load('user');
  foreach ($accounts as $account) {
    if ($account->uid < 2 or $account->status != 1) {
      continue; // skip admin and disabled accounts
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

  // Get a random sguid.
  require_once(dirname(__FILE__) . '/translations/vote.inc');
  $sguid = l10n_suggestions_get_random_sguid();

  $lng = $account->lng;
  $uid = $account->uid;
  $timestamp = REQUEST_TIME;
  $rehash = user_pass_rehash($account->pass, $timestamp, $account->login);
  $url = url("translations/$sguid/$timestamp.$uid.$rehash", array('absolute' => TRUE));

  // Get a short url.
  $short_url = get_short_url($url);
  if ($short_url == 'wait') {
    sleep(60);
    $short_url = get_short_url($url);
  }
  if ($short_url != null and $short_url != 'wait') {
    $url = $short_url;
  }

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

  $module = 'l10n_suggestions';
  $key = 'send_string_by_email';
  $from = "l10n-sq.org <noreply@l10n-sq.org>";
  $to = $account->name . ' <' .$account->mail . '>';
  $language = $account->lng;
  $send = TRUE;

  $params['subject'] = t('Translation Review');
  $params['text_message'] = $text_message;
  $params['html_message'] = $html_message;

  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
  return $result;
}

/**
 * Get a short URL, using http://is.gd/ .
 */
function get_short_url($url)
{
  $url = urlencode($url);
  $path = "http://v.gd/create.php?format=simple&url=$url";

  //We need to set a context with ignore_errors on otherwise PHP doesn't fetch
  //page content for failure HTTP status codes (v.gd needs this to return error
  //messages when using simple format)
  $opts = array("http" => array("ignore_errors" => true));
  $context = stream_context_create($opts);

  $response = @file_get_contents($path,false,$context);

  if(!isset($http_response_header)) {
    return null;
  }

  //Hacky way of getting the HTTP status code from the response headers
  if (!preg_match("{[0-9]{3}}",$http_response_header[0],$httpStatus)) {
    return null;
  }

  if ($httpStatus[0] == 200) {
    return $response;
  }
  else if ($httpStatus[0] == 502) {
    return 'wait';
  }
  else {
    return null;
  }
}
?>
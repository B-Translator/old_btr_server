<?php
/*
 * Implements hook_cron().
 */
function l10n_feedback_cron() {

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
      'language' => $account->language,
      'lng' => l10n_feedback_get_translation_lng($account),
      'login' => $account->login,
    );
    $queue->createItem($account_data);
  }
}

/*
 * Implements hook_cron_queue_info().
 */
function l10n_feedback_cron_queue_info() {
  $queues['send_string_emails'] = array(
    'worker callback' => 'send_string_by_email',
    'time' => 120,
  );
  return $queues;
}

function send_string_by_email($account) {

  $lng = $account->lng;
  $uid = $account->uid;
  $timestamp = REQUEST_TIME;

  // get a sguid according to the user preferencies
  // get also the details of the selected sguid
  require_once(dirname(__FILE__) . '/translations/vote.inc');
  $sguid = l10n_feedback_get_sguid($uid);
  $query = db_select('l10n_feedback_strings', 's')
    ->fields('s', array('sguid'))
    ->where('s.sguid = :sguid', array(':sguid' => $sguid));
  $strings = l10n_feedback_get_strings($query, $lng);
  $string = $strings[$sguid]->string;
  $translations = array();
  foreach ($strings[$sguid]->translations as $tguid => $obj_translation) {
    $translations[] = $obj_translation->translation;
  }

  // get the url of the string
  $rehash = user_pass_rehash($account->pass, $timestamp, $account->login);
  $url = url("translations/$lng/$sguid/$timestamp.$uid.$rehash", array('absolute' => TRUE));

  // get a short url
  $short_url = get_short_url($url);
  if ($short_url == 'wait') {
    sleep(60);
    $short_url = get_short_url($url);
  }
  if ($short_url != null and $short_url != 'wait') {
    $url = $short_url;
  }

  // build the subject of the message
  $subject = strip_tags(str_replace("\n", ' ', $string));
  if (strlen($subject) > 60) {
    $subject = substr($subject, 0, strrpos(substr($subject, 0, 57), ' '));
    $subject .= '...';
  }
  $subject = '[l10n-sq] ' . $subject;

  // build the body of the message
  $body = array(
    'Greetings ' . $account->name . ',',
    t("If you have time, please help to review the translation into '$lng' of the string at this link: $url"),
    t('Thanks'),
    '----- Original (English) String:',
    $string,
    '----- Available Translations:',
  );
  foreach ($translations as $translation) {
    $body[] = ' * ' . $translation;
  }

  // set the drupal_mail() parameters
  $module = 'l10n_feedback';
  $key = 'send_string_by_email';
  $smtp_from = variable_get('smtp_from');
  $smtp_fromname = variable_get('smtp_fromname');
  $from = "$smtp_fromname <$smtp_from>";
  $to = $account->name . ' <' .$account->mail . '>';
  $language = $account->language;
  $send = TRUE;
  $params['subject'] = $subject;
  $params['body'] = $body;

  // send the mail
  drupal_mail($module, $key, $to, $language, $params, $from, $send);
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

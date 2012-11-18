<?php
/**
 * @file
 * Functions called by cron.
 */

/*
 * Implements hook_cron().
 */
function l10n_feedback_cron() {

  // make sure that l10n_feedback_cron runs only once per day
  // no matter how often cron is called
  $crontime = variable_get('l10n_feedback_crontime', '0');
  if (time() < $crontime)  return;
  // set this cron to run only after the next midnight (after 03:00 AM)
  $crontime = strtotime(date('Y-m-d 02:55', strtotime('+1 day')));
  variable_set('l10n_feedback_crontime', $crontime);


  $queue = DrupalQueue::get('send-string-emails');
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
      'lng' => variable_get('l10n_feedback_translation_lng', 'fr'),
      'login' => $account->login,
    );
    $queue->createItem($account_data);
  }
}

/*
 * Implements hook_cron_queue_info().
 */
function l10n_feedback_cron_queue_info() {
  $queues['send-string-emails'] = array(
    'worker callback' => 'l10n_feedback_send_string_by_email',
    'time' => 120,
  );
  $queues['notify-voter-on-translation-change'] = array(
    'worker callback' => 'l10n_feedback_notify_voter_on_translation_change',
    'time' => 120,
  );
  return $queues;
}

function l10n_feedback_send_string_by_email($account) {

  $lng = $account->lng;
  $uid = $account->uid;
  $timestamp = REQUEST_TIME;

  // get a sguid according to the user preferencies
  // get also the details of the selected sguid
  require_once(dirname(__FILE__) . '/translations/vote.inc');
  $sguid = l10n_feedback_get_sguid($uid);
  $db = $GLOBALS['l10n_feedback_db'];
  $query = $db->select('l10n_feedback_strings', 's')
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
  if ($short_url != NULL and $short_url != 'wait') {
    $url = $short_url;
  }

  // build the subject of the message
  $subject = l10n_feedback_shorten($string, 60);
  $subject = "[l10n-$lng] $subject";

  // build the body of the message
  $body = array(
    t('Greetings !username,', array('!username' => $account->name)),
    t("If you have time, please help to review the translation into '!lng' of the string at this link: !url",
      array('!lng' => $lng, '!url' => $url)),
    t('Thanks'),
    t('----- Original (English) String:'),
    $string,
    t('----- Available Translations:'),
  );
  foreach ($translations as $translation) {
    $body[] = ' * ' . $translation;
  }

  // set the drupal_mail() parameters
  $module = 'l10n_feedback';
  $key = 'send-string-by-email';
  $smtp_from = variable_get('smtp_from');
  $smtp_fromname = variable_get('smtp_fromname');
  $from = "$smtp_fromname <$smtp_from>";
  $to = $account->name . ' <' . $account->mail . '>';
  $language = $account->language;
  $send = TRUE;
  $params['subject'] = $subject;
  $params['body'] = $body;

  // send the mail
  drupal_mail($module, $key, $to, $language, $params, $from, $send);
}


/**
 * Send an email notification to a user, when a translation that he
 * has voted for is modified.
 * Parameter $data is an object with this attributes:
 *     uid, recipient, sender,
 *     sguid, string, old_translation, new_translation
 */
function l10n_feedback_notify_voter_on_translation_change($data) {

  $account = user_load($data->uid);
  $lng = variable_get('l10n_feedback_translation_lng', 'fr');

  // get the url of the string
  $timestamp = REQUEST_TIME;
  $rehash = user_pass_rehash($account->pass, $timestamp, $account->login);
  $url = url("translations/$lng/$data->sguid/$timestamp.$data->uid.$rehash", array('absolute' => TRUE));

  // get a short url
  $short_url = get_short_url($url);
  if ($short_url == 'wait') {
    sleep(60);
    $short_url = get_short_url($url);
  }
  if ($short_url != NULL and $short_url != 'wait') {
    $url = $short_url;
  }

  // build the subject of the message
  $subject = t("[!prefix] Translation modified for: !string",
             array(
               '!prefix' => "l10n-$lng",
               '!string' => l10n_feedback_shorten($data->string, 30)
             ));

  // build the body of the message
  $body = array(
    t('Greetings !username,', array('!username' => $account->name)),
    t("The following translation has been modified by its author. You are being notified because you have voted for the old translation and your vote now counts for the new version of the translation. If the new version of the translation is OK for you, then there is nothing you should do. Otherwise, you can change your vote at this link: !url",
      array('!url' => $url)),
    t('Thanks'),
    t('----- Original (English) String:'),
    $data->string,
    t('----- Old Translation:'),
    $data->old_translation,
    t('----- New Translation:'),
    $data->new_translation
  );

  // set the drupal_mail() parameters
  $module = 'l10n_feedback';
  $key = 'notify-voter-on-translation-change';
  $from = $data->sender;
  $to = $data->recipient;
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
function get_short_url($url) {

  $url = urlencode($url);
  $path = "http://v.gd/create.php?format=simple&url=$url";

  //We need to set a context with ignore_errors on otherwise PHP doesn't fetch
  //page content for failure HTTP status codes (v.gd needs this to return error
  //messages when using simple format)
  $opts = array("http" => array("ignore_errors" => TRUE));
  $context = stream_context_create($opts);

  $response = @file_get_contents($path, FALSE, $context);

  if (!isset($http_response_header)) {
    return NULL;
  }

  //Hacky way of getting the HTTP status code from the response headers
  if (!preg_match("{[0-9]{3}}", $http_response_header[0], $http_status)) {
    return NULL;
  }

  if ($http_status[0] == 200) {
    return $response;
  }
  elseif ($http_status[0] == 502) {
    return 'wait';
  }
  else {
    return NULL;
  }
}

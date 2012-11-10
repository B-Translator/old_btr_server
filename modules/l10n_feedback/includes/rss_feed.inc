<?php
/**
 * @file
 * RSS feed from l10n_feedback.
 */

function l10n_feedback_rss_feed($origin =NULL, $project =NULL) {

  $lng = variable_get('l10n_feedback_translation_lng', 'fr');
  $from_date = date('Y-m-d', strtotime("-1 day"));
  $to_date = date('Y-m-d');  // last midnight

  // get the domain of the feed in the form of 'origin/project' (or just 'origin')
  $domain = '';
  if ( ! empty($origin) ) {
    $domain = $origin;
    if ( ! empty($project) ) {
      $domain .= '/' . $project;
    }
  }

  // Get the feed data from cache, if possible.
  $cid = "l10n_feedback_rss_feed:$lng:$domain";
  $cache = cache_get($cid, 'cache_l10n_feedback');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
    print $cache->data;
    return
  }

  $rss_feed = '<?xml version="1.0" encoding="utf-8"?>' . "\n";
  $rss_feed .= '<rss version="2.0">';

  $link = url('translations/rss_feed', array('absolute' => TRUE)) . '/' . $domain;
  $title = variable_get('site_name', 'B-Translator');
  if (empty($domain)) {
    $description = t('Translation suggestions on B-Translator from @from_date to @to_date',
                   array('@from_date' => $from_date, '@to_date' => $to_date));
  }
  else {
    $description = t('Latest translation suggestions on B-Translator from @from_date to @to_date, for @domain',
                   array('@from_date' => $from_date, '@to_date' => $to_date, '@domain' => $domain));
  }
  $lng = variable_get('l10n_feedback_translation_lng', 'fr');
  $ttl = 1440;  // 1 day = 24*60 min
  $site_mail = variable_get('site_mail');
  $site_name = variable_get('site_name');
  $webMaster = "$site_mail ($site_name)";

  $lastBuildDate = date('r');
  $rss_feed .= "
    <channel>
      <title>$title</title>
      <link>$link</link>
      <description>$description</description>
      <category>B-Translator</category>
      <language>$lng</language>
      <ttl>$ttl</ttl>
      <webMaster>$webMaster</webMaster>
      <lastBuildDate>$lastBuildDate</lastBuildDate>
    ";

  $base_url = url('translations', array('absolute' => TRUE));
  $translations = _l10n_feedback_get_latest_translations($lng, $from_date, $to_date, $origin, $project);
  foreach ($translations as $tran) {
    $title = l10n_feedback_shorten($tran->string, 60);
    $link = $base_url . '/' . $tran->lng . '/' . $tran->sguid;
    $description = t("Translation Suggestion.

        Original string:
        !string

        Suggested translation:
        !translation
        ",
                   array(
                     '!string' => strip_tags($tran->string),
                     '!translation' => strip_tags($tran->translation)
                   ));
    $pubDate = date('r', strtotime($tran->time));
    $rss_feed .= "
      <item>
        <title>$title</title>
        <link>$link</link>
        <description><![CDATA[$description]]></description>
        <author>$tran->umail ($tran->name)</author>
        <category>$tran->origin</category>
        <category>$tran->project</category>
        <guid isPermaLink='false'>$tran->tguid</guid>
        <pubDate>$pubDate</pubDate>
      </item>
    ";
  }

  $rss_feed .= "</channel>\n";
  $rss_feed .= "</rss>\n";

  // Cache until the next midnight.
  $next_midnight = strtotime(date('Y-m-d', strtotime('+1 day')));
  cache_set($cid, $rss_feed, 'cache_l10n_feedback', $next_midnight);

  drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
  print $rss_feed;
}


/**
 * Get and return an array of the latest translation suggestions,
 * submitted between the last midnight and the midnight before.
 * If $origin and $project are given, then they will be used
 * to filter only the translations that belong to them.
 * The fields that are returned are:
 *   origin, project, sguid, string, lng, translation, tguid, time, name, umail
 */
function _l10n_feedback_get_latest_translations($lng, $from_date, $to_date, $origin =NULL, $project =NULL) {

  $get_latest_translations = "
    SELECT p.origin, p.project,
           s.sguid, s.string,
           t.lng, t.translation, t.tguid, t.time,
           u.name, u.umail
    FROM l10n_feedback_translations t
    LEFT JOIN l10n_feedback_strings s ON (s.sguid = t.sguid)
    LEFT JOIN l10n_feedback_users u ON (u.umail = t.umail AND u.ulng = t.ulng)
    LEFT JOIN l10n_feedback_locations l ON (l.sguid = s.sguid)
    LEFT JOIN l10n_feedback_templates tpl ON (tpl.potid = l.potid)
    LEFT JOIN l10n_feedback_projects p ON (p.pguid = tpl.pguid)
    WHERE t.lng = :lng
      AND t.time BETWEEN :from_date AND :to_date
    ";

  $args = array(
    ':lng' => $lng,
    ':from_date' => $from_date,
    ':to_date' => $to_date,
  );

  if ( ! empty($origin) ) {
    // filter by origin
    $get_latest_translations .= " AND p.origin = :origin";
    $args[':origin'] = $origin;

    if ( ! empty($project) ) {
      // filter also by project
      $get_latest_translations .= " AND p.project = :project";
      $args[':project'] = $project;
    }
  }

  // display the latest first
  $get_latest_translations .= "\n    ORDER BY t.time DESC";

  // run the query and get the translations
  $db = $GLOBALS['l10n_feedback_db'];
  $translations = $db->query($get_latest_translations, $args)->fetchAll();

  return $translations;
}
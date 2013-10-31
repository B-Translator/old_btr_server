<?php
/**
 * @file
 * RSS feed from btrCore.
 */

function btrCore_rss_feed($lng =NULL, $origin =NULL, $project =NULL) {

  if (empty($lng)) {
    $lng = variable_get('btr_translation_lng', 'fr');
  }

  // get the domain of the feed in the form of 'origin/project' (or just 'origin')
  $domain = '';
  if ( ! empty($origin) ) {
    $domain = $origin;
    if ( ! empty($project) ) {
      $domain .= '/' . $project;
    }
  }

  // Get the feed data from cache, if possible.
  $cid = "btrCore_rss_feed:$lng:$domain";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
    print $cache->data;
    return;
  }

  $rss_feed = '<?xml version="1.0" encoding="utf-8"?>' . "\n";
  $rss_feed .= '<rss version="2.0">';

  $link = url("translations/rss-feed/$lng", array('absolute' => TRUE));
  if (!empty($domain)) {
    $link .= '/' . $domain;
  }
  $title = variable_get('site_name', 'B-Translator');
  if (empty($domain)) {
    $description = t('Latest translation suggestions on B-Translator');
  }
  else {
    $description = t('Latest translation suggestions on B-Translator, for @domain', array('@domain' => $domain));
  }
  $ttl = 180;  // 3 hours = 3*60 min
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
  $translations = _btrCore_get_latest_translations($lng, $origin, $project);
  foreach ($translations as $tran) {
    $title = btrCore_shorten($tran->string, 60);
    $link = $base_url . '/' . $tran->lng . '/' . $tran->sguid;
    $str_original_string = t("Original string:");
    $str_suggested_translation = t("Suggested translation:");
    $description = "
	    <strong>$str_original_string</strong><br/>
	    <xmp>$tran->string</xmp>
	    <br/><br/>
	    <strong>$str_suggested_translation</strong><br/>
	    <xmp>$tran->translation</xmp><br/>
        ";
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

  // Cache for 2 hours.
  cache_set($cid, $rss_feed, 'cache_btrCore', strtotime('+2 hours'));

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
function _btrCore_get_latest_translations($lng, $origin =NULL, $project =NULL) {

  $get_latest_translations = "
    SELECT p.origin, p.project,
           s.sguid, s.string,
           t.lng, t.translation, t.tguid, t.time,
           u.name, u.umail
    FROM {btr_translations} t
    LEFT JOIN {btr_strings} s ON (s.sguid = t.sguid)
    LEFT JOIN {btr_users} u ON (u.umail = t.umail AND u.ulng = t.ulng)
    LEFT JOIN {btr_locations} l ON (l.sguid = s.sguid)
    LEFT JOIN {btr_templates} tpl ON (tpl.potid = l.potid)
    LEFT JOIN {btr_projects} p ON (p.pguid = tpl.pguid)
    WHERE t.umail != 'admin@example.com' AND t.lng = :lng AND t.time > :from_date
    ";

  $args = array(
    ':lng' => $lng,
    ':from_date' => date('Y-m-d', strtotime("-1 day")),
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
  $translations = btr_query($get_latest_translations, $args)->fetchAll();

  return $translations;
}
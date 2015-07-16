<?php
/**
 * @file
 * Menu callbacks.
 */

/**
 * Callback for 'translations/rss_feed'.
 */
function btrCore_rss_feed($lng = 'fr', $origin = NULL, $project = NULL) {
  // Get the domain of the feed in the form of 'origin/project'
  // (or just 'origin').
  $domain = '';
  if (!empty($origin)) {
    $domain = $origin;
    if (!empty($project)) {
      $domain .= '/' . $project;
    }
  }

  // Get the feed data from cache, if possible.
  $cid = "btrCore_rss_feed:$lng:$domain";
  $cache = cache_get($cid, 'cache_btrCore');
  if (!empty($cache) && isset($cache->data) && !empty($cache->data)) {
    $rss_feed = $cache->data;
    drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
    print $rss_feed;
    return;
  }

  // Get the latest translations.
  $translations = btr::translation_latest($lng, $origin, $project);

  // Start building the RSS feed output.
  $rss_feed = '<?xml version="1.0" encoding="utf-8"?>' . "\n";
  $rss_feed .= '<rss version="2.0">';

  $link = url("rss-feed/$lng", array('absolute' => TRUE));
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
  $ttl = 180;
  $site_mail = variable_get('site_mail');
  $site_name = variable_get('site_name');
  $web_master = "$site_mail ($site_name)";

  $last_build_date = date('r');
  $rss_feed .= "
    <channel>
      <title>$title</title>
      <link>$link</link>
      <description>$description</description>
      <category>B-Translator</category>
      <language>$lng</language>
      <ttl>$ttl</ttl>
      <webMaster>$web_master</webMaster>
      <lastBuildDate>$last_build_date</lastBuildDate>
    ";

  // Append an item for each translation.
  foreach ($translations as $translation) {
    extract(get_object_vars($translation));
    $title = btr::utils_shorten($string, 60);
    $link = isset($_GET['url']) ?
      $_GET['url'] . "/?lng=$lng&proj=$project#$string" :
      url('translations', array('absolute' => TRUE)) . "/$lng/$sguid";
    $description = "<xmp>$string</xmp> -- <xmp>$translation</xmp>";
    $pub_date = date('r', strtotime($time));
    $rss_feed .= "
      <item>
        <title>$title</title>
        <link>$link</link>
        <description><![CDATA[$description]]></description>
        <author>$umail ($name)</author>
        <category>$origin</category>
        <category>$project</category>
        <guid isPermaLink='false'>$tguid</guid>
        <pubDate>$pub_date</pubDate>
      </item>
    ";
  }
  // Close the XML elements.
  $rss_feed .= "</channel>\n";
  $rss_feed .= "</rss>\n";

  // Cache for 2 hours.
  cache_set($cid, $rss_feed, 'cache_btrCore', strtotime('+2 hours'));

  // Send the output.
  drupal_add_http_header('Content-Type', 'application/rss+xml; charset=utf-8');
  print $rss_feed;
}

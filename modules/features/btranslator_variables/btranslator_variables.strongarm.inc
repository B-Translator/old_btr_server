<?php
/**
 * @file
 * btranslator_variables.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btranslator_variables_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab';
  $strongarm->value = 'edit-context';
  $export['additional_settings__active_tab'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_article';
  $strongarm->value = 'edit-comment';
  $export['additional_settings__active_tab_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_blog';
  $strongarm->value = 'edit-comment';
  $export['additional_settings__active_tab_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_book';
  $strongarm->value = 'edit-comment';
  $export['additional_settings__active_tab_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_page';
  $strongarm->value = 'edit-comment';
  $export['additional_settings__active_tab_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_projects';
  $strongarm->value = 'edit-menu';
  $export['additional_settings__active_tab_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_simplenews';
  $strongarm->value = 'edit-rpx-ui';
  $export['additional_settings__active_tab_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_theme';
  $strongarm->value = 'seven';
  $export['admin_theme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'aggregator_allowed_html_tags';
  $strongarm->value = '<a> <b> <br> <dd> <dl> <dt> <em> <i> <li> <ol> <p> <strong> <u> <ul>';
  $export['aggregator_allowed_html_tags'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'aggregator_category_selector';
  $strongarm->value = 'checkboxes';
  $export['aggregator_category_selector'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'aggregator_clear';
  $strongarm->value = '1209600';
  $export['aggregator_clear'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'aggregator_summary_items';
  $strongarm->value = '5';
  $export['aggregator_summary_items'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'aggregator_teaser_length';
  $strongarm->value = '600';
  $export['aggregator_teaser_length'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'anonymous';
  $strongarm->value = 'Anonymous';
  $export['anonymous'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autoloader_mode';
  $strongarm->value = 'apc';
  $export['autoloader_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'block_cache';
  $strongarm->value = 1;
  $export['block_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'book_allowed_types';
  $strongarm->value = array(
    0 => 'book',
  );
  $export['book_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'book_child_type';
  $strongarm->value = 'book';
  $export['book_child_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_cacheability_option';
  $strongarm->value = '0';
  $export['boost_cacheability_option'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_cacheability_pages';
  $strongarm->value = 'translations/sq/*
translations/fr/*
translations/de/*
translations/it/*
translations/sl/*';
  $export['boost_cacheability_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_end_application/rss';
  $strongarm->value = ' -->';
  $export['boost_comment_end_application/rss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_end_application/rss+xml';
  $strongarm->value = ' -->';
  $export['boost_comment_end_application/rss+xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_end_application/xml';
  $strongarm->value = ' -->';
  $export['boost_comment_end_application/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_end_text/html';
  $strongarm->value = ' -->';
  $export['boost_comment_end_text/html'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_end_text/javascript';
  $strongarm->value = ' */';
  $export['boost_comment_end_text/javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_end_text/xml';
  $strongarm->value = ' -->';
  $export['boost_comment_end_text/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_start_application/rss';
  $strongarm->value = '<!-- ';
  $export['boost_comment_start_application/rss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_start_application/rss+xml';
  $strongarm->value = '<!-- ';
  $export['boost_comment_start_application/rss+xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_start_application/xml';
  $strongarm->value = '<!-- ';
  $export['boost_comment_start_application/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_start_text/html';
  $strongarm->value = '<!-- ';
  $export['boost_comment_start_text/html'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_start_text/javascript';
  $strongarm->value = '/* ';
  $export['boost_comment_start_text/javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_comment_start_text/xml';
  $strongarm->value = '<!-- ';
  $export['boost_comment_start_text/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_enabled_application/json';
  $strongarm->value = FALSE;
  $export['boost_enabled_application/json'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_enabled_application/rss';
  $strongarm->value = 1;
  $export['boost_enabled_application/rss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_enabled_application/rss+xml';
  $strongarm->value = 1;
  $export['boost_enabled_application/rss+xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_enabled_application/xml';
  $strongarm->value = 1;
  $export['boost_enabled_application/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_enabled_text/html';
  $strongarm->value = 1;
  $export['boost_enabled_text/html'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_enabled_text/javascript';
  $strongarm->value = 1;
  $export['boost_enabled_text/javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_enabled_text/xml';
  $strongarm->value = 1;
  $export['boost_enabled_text/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_expire_cron';
  $strongarm->value = 1;
  $export['boost_expire_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_extension_application/rss';
  $strongarm->value = 'xml';
  $export['boost_extension_application/rss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_extension_application/rss+xml';
  $strongarm->value = 'xml';
  $export['boost_extension_application/rss+xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_extension_application/xml';
  $strongarm->value = 'xml';
  $export['boost_extension_application/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_extension_text/html';
  $strongarm->value = 'html';
  $export['boost_extension_text/html'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_extension_text/javascript';
  $strongarm->value = 'json';
  $export['boost_extension_text/javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_extension_text/xml';
  $strongarm->value = 'xml';
  $export['boost_extension_text/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_gzip_application/rss';
  $strongarm->value = TRUE;
  $export['boost_gzip_application/rss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_gzip_application/rss+xml';
  $strongarm->value = TRUE;
  $export['boost_gzip_application/rss+xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_gzip_application/xml';
  $strongarm->value = TRUE;
  $export['boost_gzip_application/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_gzip_text/html';
  $strongarm->value = TRUE;
  $export['boost_gzip_text/html'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_gzip_text/javascript';
  $strongarm->value = TRUE;
  $export['boost_gzip_text/javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_gzip_text/xml';
  $strongarm->value = TRUE;
  $export['boost_gzip_text/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_ignore_flush';
  $strongarm->value = 0;
  $export['boost_ignore_flush'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_max_application/rss';
  $strongarm->value = '10800';
  $export['boost_lifetime_max_application/rss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_max_application/rss+xml';
  $strongarm->value = '10800';
  $export['boost_lifetime_max_application/rss+xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_max_application/xml';
  $strongarm->value = '10800';
  $export['boost_lifetime_max_application/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_max_text/html';
  $strongarm->value = '43200';
  $export['boost_lifetime_max_text/html'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_max_text/javascript';
  $strongarm->value = '43200';
  $export['boost_lifetime_max_text/javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_max_text/xml';
  $strongarm->value = '43200';
  $export['boost_lifetime_max_text/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_min_application/rss';
  $strongarm->value = '3600';
  $export['boost_lifetime_min_application/rss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_min_application/rss+xml';
  $strongarm->value = '3600';
  $export['boost_lifetime_min_application/rss+xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_min_application/xml';
  $strongarm->value = '3600';
  $export['boost_lifetime_min_application/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_min_text/html';
  $strongarm->value = '10800';
  $export['boost_lifetime_min_text/html'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_min_text/javascript';
  $strongarm->value = '10800';
  $export['boost_lifetime_min_text/javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'boost_lifetime_min_text/xml';
  $strongarm->value = '10800';
  $export['boost_lifetime_min_text/xml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_auto_reconnect';
  $strongarm->value = 1;
  $export['bot_auto_reconnect'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_auto_retry';
  $strongarm->value = 1;
  $export['bot_auto_retry'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_channels';
  $strongarm->value = '#btranslator';
  $export['bot_channels'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_debugging';
  $strongarm->value = 0;
  $export['bot_debugging'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_drupal_api_function_dumps';
  $strongarm->value = 'http://api.drupal.org/api/function_dump/7:7
http://drupalcontrib.org/api/function_dump/7:contrib-7';
  $export['bot_drupal_api_function_dumps'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_drupal_api_function_dump_update_frequency';
  $strongarm->value = '1814400';
  $export['bot_drupal_api_function_dump_update_frequency'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_ghost';
  $strongarm->value = '/msg NickServ GHOST !bot_nickname !bot_password';
  $export['bot_ghost'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_identify';
  $strongarm->value = '/msg NickServ IDENTIFY !bot_password';
  $export['bot_identify'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_nickname';
  $strongarm->value = 'btranslator';
  $export['bot_nickname'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_password';
  $strongarm->value = '7Dryunjis';
  $export['bot_password'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_real_sockets';
  $strongarm->value = 0;
  $export['bot_real_sockets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_server';
  $strongarm->value = 'irc.freenode.net';
  $export['bot_server'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bot_server_port';
  $strongarm->value = '6667';
  $export['bot_server_port'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'browscap_imported';
  $strongarm->value = 1349171095;
  $export['browscap_imported'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'browscap_version';
  $strongarm->value = '5015';
  $export['browscap_version'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache';
  $strongarm->value = 0;
  $export['cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_content_flush_cache_block';
  $strongarm->value = 1364117965;
  $export['cache_content_flush_cache_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_content_flush_cache_page';
  $strongarm->value = 1364117965;
  $export['cache_content_flush_cache_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_block';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_bootstrap';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_bootstrap'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_field';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_filter';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_filter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_form';
  $strongarm->value = 0;
  $export['cache_flush_cache_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_image';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_l10n_feedback';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_l10n_feedback'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_libraries';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_libraries'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_menu';
  $strongarm->value = 1364117965;
  $export['cache_flush_cache_menu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_page';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_path';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_rules';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_rules'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_token';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_token'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_views';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_views'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_flush_cache_views_data';
  $strongarm->value = 1364117972;
  $export['cache_flush_cache_views_data'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cache_lifetime';
  $strongarm->value = '1800';
  $export['cache_lifetime'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_add_captcha_description';
  $strongarm->value = 0;
  $export['captcha_add_captcha_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_administration_mode';
  $strongarm->value = 0;
  $export['captcha_administration_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_allow_on_admin_pages';
  $strongarm->value = 0;
  $export['captcha_allow_on_admin_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_default_challenge';
  $strongarm->value = 'recaptcha/reCAPTCHA';
  $export['captcha_default_challenge'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_default_validation';
  $strongarm->value = '1';
  $export['captcha_default_validation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_description_en';
  $strongarm->value = 'This question is for testing whether you are a human visitor and to prevent automated spam submissions.';
  $export['captcha_description_en'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_description_sq';
  $strongarm->value = 'This question is for testing whether you are a human visitor and to prevent automated spam submissions.';
  $export['captcha_description_sq'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_log_wrong_responses';
  $strongarm->value = 0;
  $export['captcha_log_wrong_responses'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_persistence';
  $strongarm->value = '0';
  $export['captcha_persistence'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_placement_map_cache';
  $strongarm->value = array(
    'contact_site_form' => array(
      'path' => array(),
      'key' => 'actions',
      'weight' => 99,
    ),
    'user_register_form' => array(
      'path' => array(),
      'key' => 'actions',
      'weight' => 99,
    ),
    'user_pass' => array(
      'path' => array(),
      'key' => 'actions',
      'weight' => 99,
    ),
  );
  $export['captcha_placement_map_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'captcha_wrong_response_counter';
  $strongarm->value = 7299;
  $export['captcha_wrong_response_counter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'clean_url';
  $strongarm->value = TRUE;
  $export['clean_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik1_files';
  $strongarm->value = array(
    0 => 'public://color/bartik1-5672d3bd/logo.png',
    1 => 'public://color/bartik1-5672d3bd/colors.css',
  );
  $export['color_bartik1_files'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik1_logo';
  $strongarm->value = 'public://color/bartik1-5672d3bd/logo.png';
  $export['color_bartik1_logo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik1_palette';
  $strongarm->value = array(
    'top' => '#2268a1',
    'bottom' => '#48a9e4',
    'bg' => '#ffffff',
    'sidebar' => '#d8eaf9',
    'sidebarborders' => '#b7d7f1',
    'footer' => '#2268a1',
    'titleslogan' => '#fffeff',
    'text' => '#3b3b3b',
    'link' => '#0071B3',
  );
  $export['color_bartik1_palette'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik1_stylesheets';
  $strongarm->value = array(
    0 => 'public://color/bartik1-5672d3bd/colors.css',
  );
  $export['color_bartik1_stylesheets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_fb_files';
  $strongarm->value = array(
    0 => 'public://color/bartik_fb-eca54fcf/logo.png',
    1 => 'public://color/bartik_fb-eca54fcf/colors.css',
  );
  $export['color_bartik_fb_files'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_fb_logo';
  $strongarm->value = 'public://color/bartik_fb-eca54fcf/logo.png';
  $export['color_bartik_fb_logo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_fb_palette';
  $strongarm->value = array(
    'bg' => '#ffffff',
    'link' => '#0071B3',
    'top' => '#2268a1',
    'bottom' => '#48a9e4',
    'text' => '#3b3b3b',
    'sidebar' => '#d8eaf9',
    'sidebarborders' => '#b7d7f1',
    'footer' => '#2268a1',
    'titleslogan' => '#fffeff',
  );
  $export['color_bartik_fb_palette'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_fb_stylesheets';
  $strongarm->value = array(
    0 => 'public://color/bartik_fb-eca54fcf/colors.css',
  );
  $export['color_bartik_fb_stylesheets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_files';
  $strongarm->value = array(
    0 => 'public://color/bartik-34087440/logo.png',
    1 => 'public://color/bartik-34087440/colors.css',
  );
  $export['color_bartik_files'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_logo';
  $strongarm->value = 'public://color/bartik-34087440/logo.png';
  $export['color_bartik_logo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_palette';
  $strongarm->value = array(
    'top' => '#2268a1',
    'bottom' => '#48a9e4',
    'bg' => '#ffffff',
    'sidebar' => '#d8eaf9',
    'sidebarborders' => '#b7d7f1',
    'footer' => '#2268a1',
    'titleslogan' => '#fffeff',
    'text' => '#3b3b3b',
    'link' => '#0071B3',
  );
  $export['color_bartik_palette'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'color_bartik_stylesheets';
  $strongarm->value = array(
    0 => 'public://color/bartik-34087440/colors.css',
  );
  $export['color_bartik_stylesheets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_article';
  $strongarm->value = 0;
  $export['comment_anonymous_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_blog';
  $strongarm->value = 0;
  $export['comment_anonymous_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_book';
  $strongarm->value = 0;
  $export['comment_anonymous_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_page';
  $strongarm->value = 0;
  $export['comment_anonymous_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_simplenews';
  $strongarm->value = 0;
  $export['comment_anonymous_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_article';
  $strongarm->value = '2';
  $export['comment_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_blog';
  $strongarm->value = '2';
  $export['comment_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_book';
  $strongarm->value = '2';
  $export['comment_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_article';
  $strongarm->value = 1;
  $export['comment_default_mode_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_blog';
  $strongarm->value = 1;
  $export['comment_default_mode_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_book';
  $strongarm->value = 1;
  $export['comment_default_mode_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_page';
  $strongarm->value = 1;
  $export['comment_default_mode_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_simplenews';
  $strongarm->value = 1;
  $export['comment_default_mode_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_article';
  $strongarm->value = '50';
  $export['comment_default_per_page_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_blog';
  $strongarm->value = '50';
  $export['comment_default_per_page_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_book';
  $strongarm->value = '50';
  $export['comment_default_per_page_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_page';
  $strongarm->value = '50';
  $export['comment_default_per_page_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_simplenews';
  $strongarm->value = '50';
  $export['comment_default_per_page_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_article';
  $strongarm->value = 1;
  $export['comment_form_location_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_blog';
  $strongarm->value = 1;
  $export['comment_form_location_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_book';
  $strongarm->value = 1;
  $export['comment_form_location_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_page';
  $strongarm->value = 1;
  $export['comment_form_location_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_simplenews';
  $strongarm->value = 1;
  $export['comment_form_location_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_page';
  $strongarm->value = '2';
  $export['comment_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_article';
  $strongarm->value = '1';
  $export['comment_preview_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_blog';
  $strongarm->value = '1';
  $export['comment_preview_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_book';
  $strongarm->value = '1';
  $export['comment_preview_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_page';
  $strongarm->value = '1';
  $export['comment_preview_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_simplenews';
  $strongarm->value = '1';
  $export['comment_preview_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_simplenews';
  $strongarm->value = '1';
  $export['comment_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_article';
  $strongarm->value = 1;
  $export['comment_subject_field_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_blog';
  $strongarm->value = 1;
  $export['comment_subject_field_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_book';
  $strongarm->value = 1;
  $export['comment_subject_field_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_page';
  $strongarm->value = 1;
  $export['comment_subject_field_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_simplenews';
  $strongarm->value = 1;
  $export['comment_subject_field_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'configurable_timezones';
  $strongarm->value = 1;
  $export['configurable_timezones'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'contact_default_status';
  $strongarm->value = 1;
  $export['contact_default_status'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'context_block_rebuild_needed';
  $strongarm->value = TRUE;
  $export['context_block_rebuild_needed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cron_key';
  $strongarm->value = 'tCQgWN2IJbQ7UZ87zV5NaNDeObI_cC1HXJHG6Kdby98';
  $export['cron_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cron_last';
  $strongarm->value = 1364115662;
  $export['cron_last'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cron_safe_threshold';
  $strongarm->value = '0';
  $export['cron_safe_threshold'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'css_js_query_string';
  $strongarm->value = 'mk5s2l';
  $export['css_js_query_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ctools_last_cron';
  $strongarm->value = 1364068863;
  $export['ctools_last_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_default_timezone';
  $strongarm->value = 'Europe/Tirane';
  $export['date_default_timezone'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_first_day';
  $strongarm->value = '1';
  $export['date_first_day'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_long';
  $strongarm->value = 'l, F j, Y - H:i';
  $export['date_format_long'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_medium';
  $strongarm->value = 'D, d/m/Y - H:i';
  $export['date_format_medium'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_short';
  $strongarm->value = 'd/m/Y - H:i';
  $export['date_format_short'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'default_nodes_main';
  $strongarm->value = '10';
  $export['default_nodes_main'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_developer';
  $strongarm->value = 0;
  $export['disqus_developer'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_domain';
  $strongarm->value = 'l10n-sq';
  $export['disqus_domain'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_inherit_login';
  $strongarm->value = 1;
  $export['disqus_inherit_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_localization';
  $strongarm->value = 1;
  $export['disqus_localization'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_location';
  $strongarm->value = 'content_area';
  $export['disqus_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_nodetypes';
  $strongarm->value = array(
    'blog' => 'blog',
    'article' => 'article',
    'book' => 'book',
    'mass_contact' => 'mass_contact',
    'page' => 'page',
    'simplenews' => 'simplenews',
  );
  $export['disqus_nodetypes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_publickey';
  $strongarm->value = 'iK4bWgbfIrGm5JPRiG8igoNrf0zVW6PxiBEZ2JgwVEJrd4OjPCmr8Vt7p7cZwwEh';
  $export['disqus_publickey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_secretkey';
  $strongarm->value = '84QxPGVk4cx61FfFDquLO1x5Kfljdu6CK34qCP0pM83URlywP47e5xHXGKhN6EHa';
  $export['disqus_secretkey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_sso';
  $strongarm->value = 1;
  $export['disqus_sso'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_userapikey';
  $strongarm->value = 'jY36xKWOn1MibB0RiZ2zonErZfEx0q6h0SF9Ht5zwsAP0dSFpSBKNSufLfiTsI6y';
  $export['disqus_userapikey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_weight';
  $strongarm->value = '100';
  $export['disqus_weight'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_allow_anon_links';
  $strongarm->value = '1';
  $export['drupalchat_allow_anon_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_anon_name_set';
  $strongarm->value = 'usa';
  $export['drupalchat_anon_name_set'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_anon_prefix';
  $strongarm->value = 'Guest';
  $export['drupalchat_anon_prefix'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_chat_list_header';
  $strongarm->value = 'Chat';
  $export['drupalchat_chat_list_header'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_chat_topbar_color';
  $strongarm->value = '#222222';
  $export['drupalchat_chat_topbar_color'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_chat_topbar_text_color';
  $strongarm->value = '#FFFFFF';
  $export['drupalchat_chat_topbar_text_color'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_enable_chatroom';
  $strongarm->value = '1';
  $export['drupalchat_enable_chatroom'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_enable_smiley';
  $strongarm->value = '1';
  $export['drupalchat_enable_smiley'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_external_api_key';
  $strongarm->value = '';
  $export['drupalchat_external_api_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_font_color';
  $strongarm->value = '#222222';
  $export['drupalchat_font_color'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_load_chat_async';
  $strongarm->value = '1';
  $export['drupalchat_load_chat_async'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_log_messages';
  $strongarm->value = '1';
  $export['drupalchat_log_messages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_notification_sound';
  $strongarm->value = '1';
  $export['drupalchat_notification_sound'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_path_pages';
  $strongarm->value = '';
  $export['drupalchat_path_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_path_visibility';
  $strongarm->value = '0';
  $export['drupalchat_path_visibility'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_polling_method';
  $strongarm->value = '0';
  $export['drupalchat_polling_method'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_public_chatroom_header';
  $strongarm->value = 'Public Chatroom';
  $export['drupalchat_public_chatroom_header'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_refresh_rate';
  $strongarm->value = '10';
  $export['drupalchat_refresh_rate'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_rel';
  $strongarm->value = '0';
  $export['drupalchat_rel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_send_rate';
  $strongarm->value = '3';
  $export['drupalchat_send_rate'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_show_admin_list';
  $strongarm->value = '2';
  $export['drupalchat_show_admin_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_stop_links';
  $strongarm->value = '1';
  $export['drupalchat_stop_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_stop_word_list';
  $strongarm->value = 'asshole,assholes,bastard,beastial,beastiality,beastility,bestial,bestiality,bitch,bitcher,bitchers,bitches,bitchin,bitching,blowjob,blowjobs,bullshit,clit,cock,cocks,cocksuck,cocksucked,cocksucker,cocksucking,cocksucks,cum,cummer,cumming,cums,cumshot,cunillingus,cunnilingus,cunt,cuntlick,cuntlicker,cuntlicking,cunts,cyberfuc,cyberfuck,cyberfucked,cyberfucker,cyberfuckers,cyberfucking,damn,dildo,dildos,dick,dink,dinks,ejaculate,ejaculated,ejaculates,ejaculating,ejaculatings,ejaculation,fag,fagging,faggot,faggs,fagot,fagots,fags,fart,farted,farting,fartings,farts,farty,felatio,fellatio,fingerfuck,fingerfucked,fingerfucker,fingerfuckers,fingerfucking,fingerfucks,fistfuck,fistfucked,fistfucker,fistfuckers,fistfucking,fistfuckings,fistfucks,fuck,fucked,fucker,fuckers,fuckin,fucking,fuckings,fuckme,fucks,fuk,fuks,gangbang,gangbanged,gangbangs,gaysex,goddamn,hardcoresex,horniest,horny,hotsex,jism,jiz,jizm,kock,kondum,kondums,kum,kumer,kummer,kumming,kums,kunilingus,lust,lusting,mothafuck,mothafucka,mothafuckas,mothafuckaz,mothafucked,mothafucker,mothafuckers,mothafuckin,mothafucking,mothafuckings,mothafucks,motherfuck,motherfucked,motherfucker,motherfuckers,motherfuckin,motherfucking,motherfuckings,motherfucks,niger,nigger,niggers,orgasim,orgasims,orgasm,orgasms,phonesex,phuk,phuked,phuking,phukked,phukking,phuks,phuq,pis,piss,pisser,pissed,pisser,pissers,pises,pisses,pisin,pissin,pising,pissing,pisof,pissoff,porn,porno,pornography,pornos,prick,pricks,pussies,pusies,pussy,pusy,pussys,pusys,slut,sluts,smut,spunk';
  $export['drupalchat_stop_word_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_theme';
  $strongarm->value = 'light';
  $export['drupalchat_theme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_ur_name';
  $strongarm->value = '';
  $export['drupalchat_ur_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_user_latency';
  $strongarm->value = '10';
  $export['drupalchat_user_latency'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_user_picture';
  $strongarm->value = '1';
  $export['drupalchat_user_picture'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupalchat_use_stop_word_list';
  $strongarm->value = '1';
  $export['drupalchat_use_stop_word_list'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupal_http_request_fails';
  $strongarm->value = FALSE;
  $export['drupal_http_request_fails'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'drupal_private_key';
  $strongarm->value = 'REB1mbtvcKM4cG8_PHHa460vWvaFX63IUUtV8F68ZFY';
  $export['drupal_private_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'email__active_tab';
  $strongarm->value = 'edit-email-admin-created';
  $export['email__active_tab'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'empty_timezone_message';
  $strongarm->value = 0;
  $export['empty_timezone_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'enable_revisions_page_article';
  $strongarm->value = 1;
  $export['enable_revisions_page_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'enable_revisions_page_blog';
  $strongarm->value = 1;
  $export['enable_revisions_page_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'enable_revisions_page_book';
  $strongarm->value = 1;
  $export['enable_revisions_page_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'enable_revisions_page_page';
  $strongarm->value = 1;
  $export['enable_revisions_page_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_button_text_login';
  $strongarm->value = 'Use Facebook Login';
  $export['fb_button_text_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_button_text_login_block';
  $strongarm->value = 'Use Facebook Login';
  $export['fb_button_text_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_button_text_register';
  $strongarm->value = 'Use Facebook Account';
  $export['fb_button_text_register'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_canvas_process_absolute_links';
  $strongarm->value = 0;
  $export['fb_canvas_process_absolute_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_canvas_process_iframe';
  $strongarm->value = 1;
  $export['fb_canvas_process_iframe'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_connect_primary_label';
  $strongarm->value = 'l10nsq';
  $export['fb_connect_primary_label'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_connect_theme_username_1';
  $strongarm->value = 1;
  $export['fb_connect_theme_username_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_connect_theme_username_2';
  $strongarm->value = 1;
  $export['fb_connect_theme_username_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_connect_theme_userpic_1';
  $strongarm->value = 1;
  $export['fb_connect_theme_userpic_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_connect_theme_userpic_2';
  $strongarm->value = 1;
  $export['fb_connect_theme_userpic_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_format_username';
  $strongarm->value = 'when_not_theming';
  $export['fb_format_username'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_js_get_login_status';
  $strongarm->value = 0;
  $export['fb_js_get_login_status'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_js_oauth';
  $strongarm->value = TRUE;
  $export['fb_js_oauth'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_js_session_token';
  $strongarm->value = 0;
  $export['fb_js_session_token'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_js_test_login_status';
  $strongarm->value = FALSE;
  $export['fb_js_test_login_status'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_language_en';
  $strongarm->value = 'en_US';
  $export['fb_language_en'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_language_override';
  $strongarm->value = 'override';
  $export['fb_language_override'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_language_sq';
  $strongarm->value = 'sq_AL';
  $export['fb_language_sq'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_secure_urls';
  $strongarm->value = '1';
  $export['fb_secure_urls'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_stream_token';
  $strongarm->value = 'AAADxHrpZB34MBAIjleFLC9Lr1kdLH6EZCEhLEPvL4cUahhxVbl58QIOXQ53RAGhEn2sFkEGf0FNpjZAWDcFZCHbZCAcvhMj5knkTvAQt3qIF4DCiOiTN2';
  $export['fb_stream_token'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_tab_process_absolute_links';
  $strongarm->value = 1;
  $export['fb_tab_process_absolute_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_tab_process_iframe';
  $strongarm->value = 1;
  $export['fb_tab_process_iframe'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_tab_process_to_canvas';
  $strongarm->value = 1;
  $export['fb_tab_process_to_canvas'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_alter_contact';
  $strongarm->value = 1;
  $export['fb_user_alter_contact'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_alter_login';
  $strongarm->value = 1;
  $export['fb_user_alter_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_alter_login_block';
  $strongarm->value = 1;
  $export['fb_user_alter_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_alter_register';
  $strongarm->value = 1;
  $export['fb_user_alter_register'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_app_track_every_page';
  $strongarm->value = 0;
  $export['fb_user_app_track_every_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_app_track_pages';
  $strongarm->value = 1;
  $export['fb_user_app_track_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_app_track_users';
  $strongarm->value = 1;
  $export['fb_user_app_track_users'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_app_users_that_grant_offline';
  $strongarm->value = 0;
  $export['fb_user_app_users_that_grant_offline'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_check_session';
  $strongarm->value = 0;
  $export['fb_user_check_session'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_user_username_style';
  $strongarm->value = '1';
  $export['fb_user_username_style'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_use_cookie';
  $strongarm->value = 1;
  $export['fb_use_cookie'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_use_session';
  $strongarm->value = 0;
  $export['fb_use_session'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'features_ignored_orphans';
  $strongarm->value = array();
  $export['features_ignored_orphans'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_temporary_path';
  $strongarm->value = '/tmp';
  $export['file_temporary_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'filter_fallback_format';
  $strongarm->value = 'plain_text';
  $export['filter_fallback_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_available_languages_cache';
  $strongarm->value = array(
    '4cs' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'GADV 4CS',
    ),
    '6502acme' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MOS 6502 (6510) ACME Cross Assembler format',
    ),
    '6502kickass' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MOS 6502 (6510) Kick Assembler format',
    ),
    '6502tasm' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MOS 6502 (6510) TASM/64TASS 1.46 Assembler format',
    ),
    '68000devpac' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Motorola 68000 - HiSoft Devpac ST 2 Assembler format',
    ),
    'abap' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ABAP',
    ),
    'actionscript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ActionScript',
    ),
    'actionscript3' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ActionScript 3',
    ),
    'ada' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Ada',
    ),
    'algol68' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ALGOL 68',
    ),
    'apache' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Apache configuration',
    ),
    'applescript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'AppleScript',
    ),
    'apt_sources' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Apt sources',
    ),
    'asm' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ASM',
    ),
    'asp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ASP',
    ),
    'autoconf' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Autoconf',
    ),
    'autohotkey' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Autohotkey',
    ),
    'autoit' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'AutoIt',
    ),
    'avisynth' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'AviSynth',
    ),
    'awk' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'awk',
    ),
    'bascomavr' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'BASCOM AVR',
    ),
    'bash' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Bash',
    ),
    'basic4gl' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Basic4GL',
    ),
    'bf' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Brainfuck',
    ),
    'bibtex' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'BibTeX',
    ),
    'blitzbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'BlitzBasic',
    ),
    'bnf' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'bnf',
    ),
    'boo' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Boo',
    ),
    'c' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'C',
    ),
    'c_loadrunner' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'C (LoadRunner)',
    ),
    'c_mac' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'C (Mac)',
    ),
    'caddcl' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'CAD DCL',
    ),
    'cadlisp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'CAD Lisp',
    ),
    'cfdg' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'CFDG',
    ),
    'cfm' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ColdFusion',
    ),
    'chaiscript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ChaiScript',
    ),
    'cil' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'CIL',
    ),
    'clojure' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Clojure',
    ),
    'cmake' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'CMake',
    ),
    'cobol' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'COBOL',
    ),
    'coffeescript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'CoffeeScript',
    ),
    'cpp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'C++',
    ),
    'cpp-qt' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'C++ (QT)',
    ),
    'csharp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'C#',
    ),
    'css' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'CSS',
    ),
    'cuesheet' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Cuesheet',
    ),
    'd' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'D',
    ),
    'dcs' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'DCS',
    ),
    'delphi' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Delphi',
    ),
    'diff' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Diff',
    ),
    'div' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'DIV',
    ),
    'dos' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'DOS',
    ),
    'dot' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'dot',
    ),
    'drupal5' => array(
      'language_path' => 'profiles/btranslator/modules/geshifilter/geshi-extra',
      'fullname' => 'Drupal 5',
    ),
    'drupal6' => array(
      'language_path' => 'profiles/btranslator/modules/geshifilter/geshi-extra',
      'fullname' => 'Drupal 6',
    ),
    'e' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'E',
    ),
    'ecmascript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ECMAScript',
    ),
    'eiffel' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Eiffel',
    ),
    'email' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'eMail (mbox)',
    ),
    'epc' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'EPC',
    ),
    'erlang' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Erlang',
    ),
    'euphoria' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Euphoria',
    ),
    'f1' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Formula One',
    ),
    'falcon' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Falcon',
    ),
    'fo' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'FO (abas-ERP)',
    ),
    'fortran' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Fortran',
    ),
    'freebasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'FreeBasic',
    ),
    'fsharp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'F#',
    ),
    'gambas' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'GAMBAS',
    ),
    'gdb' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'GDB',
    ),
    'genero' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'genero',
    ),
    'genie' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Genie',
    ),
    'gettext' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'GNU Gettext',
    ),
    'glsl' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'glSlang',
    ),
    'gml' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'GML',
    ),
    'gnuplot' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Gnuplot',
    ),
    'go' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Go',
    ),
    'groovy' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Groovy',
    ),
    'gwbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'GwBasic',
    ),
    'haskell' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Haskell',
    ),
    'hicest' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'HicEst',
    ),
    'hq9plus' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'HQ9+',
    ),
    'html4strict' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'HTML',
    ),
    'html5' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'HTML',
    ),
    'icon' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Icon',
    ),
    'idl' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Uno Idl',
    ),
    'ini' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'INI',
    ),
    'inno' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Inno',
    ),
    'intercal' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'INTERCAL',
    ),
    'io' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Io',
    ),
    'j' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'J',
    ),
    'java' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Java',
    ),
    'java5' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Java(TM) 2 Platform Standard Edition 5.0',
    ),
    'javascript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Javascript',
    ),
    'jquery' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'jQuery',
    ),
    'kixtart' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'KiXtart',
    ),
    'klonec' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'KLone C',
    ),
    'klonecpp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'KLone C++',
    ),
    'latex' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'LaTeX',
    ),
    'lb' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Liberty BASIC',
    ),
    'lisp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Lisp',
    ),
    'llvm' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'LLVM Intermediate Representation',
    ),
    'locobasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Locomotive Basic',
    ),
    'logtalk' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Logtalk',
    ),
    'lolcode' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'LOLcode',
    ),
    'lotusformulas' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Lotus Notes @Formulas',
    ),
    'lotusscript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'LotusScript',
    ),
    'lscript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'LScript',
    ),
    'lsl2' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'LSL2',
    ),
    'lua' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Lua',
    ),
    'm68k' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Motorola 68000 Assembler',
    ),
    'magiksf' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MagikSF',
    ),
    'make' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'GNU make',
    ),
    'mapbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MapBasic',
    ),
    'matlab' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Matlab M',
    ),
    'mirc' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'mIRC Scripting',
    ),
    'mmix' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MMIX',
    ),
    'modula2' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Modula-2',
    ),
    'modula3' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Modula-3',
    ),
    'mpasm' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Microchip Assembler',
    ),
    'mxml' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MXML',
    ),
    'mysql' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'MySQL',
    ),
    'newlisp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'newlisp',
    ),
    'nsis' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'NSIS',
    ),
    'oberon2' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Oberon-2',
    ),
    'objc' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Objective-C',
    ),
    'objeck' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Objeck Programming Language',
    ),
    'ocaml' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'OCaml',
    ),
    'ocaml-brief' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'OCaml (brief)',
    ),
    'oobas' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'OpenOffice.org Basic',
    ),
    'oracle11' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Oracle 11 SQL',
    ),
    'oracle8' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Oracle 8 SQL',
    ),
    'oxygene' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Oxygene (Delphi Prism)',
    ),
    'oz' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'OZ',
    ),
    'pascal' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Pascal',
    ),
    'pcre' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PCRE',
    ),
    'per' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'per',
    ),
    'perl' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Perl',
    ),
    'perl6' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Perl 6',
    ),
    'pf' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'OpenBSD Packet Filter',
    ),
    'php' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PHP',
    ),
    'php-brief' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PHP (brief)',
    ),
    'pic16' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PIC16',
    ),
    'pike' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Pike',
    ),
    'pixelbender' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Pixel Bender 1.0',
    ),
    'pli' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PL/I',
    ),
    'plsql' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PL/SQL',
    ),
    'postgresql' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PostgreSQL',
    ),
    'povray' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'POVRAY',
    ),
    'powerbuilder' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PowerBuilder',
    ),
    'powershell' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PowerShell',
    ),
    'proftpd' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ProFTPd configuration',
    ),
    'progress' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Progress',
    ),
    'prolog' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Prolog',
    ),
    'properties' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PROPERTIES',
    ),
    'providex' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ProvideX',
    ),
    'purebasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'PureBasic',
    ),
    'pycon' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Python (console mode)',
    ),
    'python' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Python',
    ),
    'q' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'q/kdb+',
    ),
    'qbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'QBasic/QuickBASIC',
    ),
    'rails' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Rails',
    ),
    'rebol' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'REBOL',
    ),
    'reg' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Microsoft Registry',
    ),
    'robots' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'robots.txt',
    ),
    'rpmspec' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'RPM Specification File',
    ),
    'rsplus' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'R / S+',
    ),
    'ruby' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Ruby',
    ),
    'sas' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'SAS',
    ),
    'scala' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Scala',
    ),
    'scheme' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Scheme',
    ),
    'scilab' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'SciLab',
    ),
    'sdlbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'sdlBasic',
    ),
    'smalltalk' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Smalltalk',
    ),
    'smarty' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Smarty',
    ),
    'sql' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'SQL',
    ),
    'systemverilog' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'SystemVerilog',
    ),
    'tcl' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'TCL',
    ),
    'teraterm' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Tera Term Macro',
    ),
    'text' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Text',
    ),
    'thinbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'thinBasic',
    ),
    'tsql' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'T-SQL',
    ),
    'typoscript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'TypoScript',
    ),
    'unicon' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Unicon (Unified Extended Dialect of Icon)',
    ),
    'uscript' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Unreal Script',
    ),
    'vala' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Vala',
    ),
    'vb' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Visual Basic',
    ),
    'vbnet' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'vb.net',
    ),
    'verilog' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Verilog',
    ),
    'vhdl' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'VHDL',
    ),
    'vim' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Vim Script',
    ),
    'visualfoxpro' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Visual Fox Pro',
    ),
    'visualprolog' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Visual Prolog',
    ),
    'whitespace' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Whitespace',
    ),
    'whois' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Whois (RPSL format)',
    ),
    'winbatch' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Winbatch',
    ),
    'xbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'XBasic',
    ),
    'xml' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'XML',
    ),
    'xorg_conf' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'Xorg configuration',
    ),
    'xpp' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'X++',
    ),
    'yaml' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'YAML',
    ),
    'z80' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ZiLOG Z80 Assembler',
    ),
    'zxbasic' => array(
      'language_path' => 'profiles/btranslator/libraries/geshi/geshi',
      'fullname' => 'ZXBasic',
    ),
  );
  $export['geshifilter_available_languages_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_c';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_c'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_cpp';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_cpp'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_drupal5';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_drupal5'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_drupal6';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_drupal6'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_java';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_java'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_javascript';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_php';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_php'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_python';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_python'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_enabled_ruby';
  $strongarm->value = TRUE;
  $export['geshifilter_language_enabled_ruby'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_c';
  $strongarm->value = '<c>';
  $export['geshifilter_language_tags_c'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_cpp';
  $strongarm->value = '<cpp>';
  $export['geshifilter_language_tags_cpp'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_drupal5';
  $strongarm->value = '<drupal5>';
  $export['geshifilter_language_tags_drupal5'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_drupal6';
  $strongarm->value = '<drupal6>';
  $export['geshifilter_language_tags_drupal6'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_java';
  $strongarm->value = '<java>';
  $export['geshifilter_language_tags_java'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_javascript';
  $strongarm->value = '<javascript>';
  $export['geshifilter_language_tags_javascript'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_php';
  $strongarm->value = '<php>';
  $export['geshifilter_language_tags_php'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_python';
  $strongarm->value = '<python>';
  $export['geshifilter_language_tags_python'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'geshifilter_language_tags_ruby';
  $strongarm->value = '<ruby>';
  $export['geshifilter_language_tags_ruby'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_account';
  $strongarm->value = 'UA-33852995-1';
  $export['googleanalytics_account'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_cache';
  $strongarm->value = 1;
  $export['googleanalytics_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_codesnippet_after';
  $strongarm->value = '';
  $export['googleanalytics_codesnippet_after'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_codesnippet_before';
  $strongarm->value = '';
  $export['googleanalytics_codesnippet_before'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_cross_domains';
  $strongarm->value = '';
  $export['googleanalytics_cross_domains'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_custom';
  $strongarm->value = '0';
  $export['googleanalytics_custom'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_custom_var';
  $strongarm->value = array(
    'slots' => array(
      1 => array(
        'slot' => 1,
        'name' => '',
        'value' => '',
        'scope' => '3',
      ),
      2 => array(
        'slot' => 2,
        'name' => '',
        'value' => '',
        'scope' => '3',
      ),
      3 => array(
        'slot' => 3,
        'name' => '',
        'value' => '',
        'scope' => '3',
      ),
      4 => array(
        'slot' => 4,
        'name' => '',
        'value' => '',
        'scope' => '3',
      ),
      5 => array(
        'slot' => 5,
        'name' => '',
        'value' => '',
        'scope' => '3',
      ),
    ),
  );
  $export['googleanalytics_custom_var'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_domain_mode';
  $strongarm->value = '0';
  $export['googleanalytics_domain_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_js_scope';
  $strongarm->value = 'header';
  $export['googleanalytics_js_scope'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_last_cache';
  $strongarm->value = 1364050862;
  $export['googleanalytics_last_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_pages';
  $strongarm->value = 'admin
admin/*
batch
node/add*
node/*/*
user/*/*';
  $export['googleanalytics_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_privacy_donottrack';
  $strongarm->value = 1;
  $export['googleanalytics_privacy_donottrack'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_roles';
  $strongarm->value = array(
    1 => 0,
    2 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  );
  $export['googleanalytics_roles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_site_search';
  $strongarm->value = 0;
  $export['googleanalytics_site_search'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_trackadsense';
  $strongarm->value = 0;
  $export['googleanalytics_trackadsense'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_trackdoubleclick';
  $strongarm->value = 0;
  $export['googleanalytics_trackdoubleclick'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_tracker_anonymizeip';
  $strongarm->value = 0;
  $export['googleanalytics_tracker_anonymizeip'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_trackfiles';
  $strongarm->value = 1;
  $export['googleanalytics_trackfiles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_trackfiles_extensions';
  $strongarm->value = '7z|aac|arc|arj|asf|asx|avi|bin|csv|doc|exe|flv|gif|gz|gzip|hqx|jar|jpe?g|js|mp(2|3|4|e?g)|mov(ie)?|msi|msp|pdf|phps|png|ppt|qtm?|ra(m|r)?|sea|sit|tar|tgz|torrent|txt|wav|wma|wmv|wpd|xls|xml|z|zip';
  $export['googleanalytics_trackfiles_extensions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_trackmailto';
  $strongarm->value = 1;
  $export['googleanalytics_trackmailto'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_trackmessages';
  $strongarm->value = array(
    'status' => 'status',
    'warning' => 'warning',
    'error' => 'error',
  );
  $export['googleanalytics_trackmessages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_trackoutbound';
  $strongarm->value = 1;
  $export['googleanalytics_trackoutbound'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_visibility_pages';
  $strongarm->value = '0';
  $export['googleanalytics_visibility_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googleanalytics_visibility_roles';
  $strongarm->value = '0';
  $export['googleanalytics_visibility_roles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_element_name';
  $strongarm->value = 'email';
  $export['honeypot_element_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_article_node_form';
  $strongarm->value = 0;
  $export['honeypot_form_article_node_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_blog_node_form';
  $strongarm->value = 0;
  $export['honeypot_form_blog_node_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_book_node_form';
  $strongarm->value = 0;
  $export['honeypot_form_book_node_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_comment_node_article_form';
  $strongarm->value = 0;
  $export['honeypot_form_comment_node_article_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_comment_node_blog_form';
  $strongarm->value = 0;
  $export['honeypot_form_comment_node_blog_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_comment_node_book_form';
  $strongarm->value = 0;
  $export['honeypot_form_comment_node_book_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_comment_node_mass_contact_form';
  $strongarm->value = 0;
  $export['honeypot_form_comment_node_mass_contact_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_comment_node_page_form';
  $strongarm->value = 0;
  $export['honeypot_form_comment_node_page_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_comment_node_simplenews_form';
  $strongarm->value = 0;
  $export['honeypot_form_comment_node_simplenews_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_contact_personal_form';
  $strongarm->value = 1;
  $export['honeypot_form_contact_personal_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_contact_site_form';
  $strongarm->value = 1;
  $export['honeypot_form_contact_site_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_mass_contact_node_form';
  $strongarm->value = 0;
  $export['honeypot_form_mass_contact_node_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_page_node_form';
  $strongarm->value = 0;
  $export['honeypot_form_page_node_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_simplenews_node_form';
  $strongarm->value = 0;
  $export['honeypot_form_simplenews_node_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_user_pass';
  $strongarm->value = 1;
  $export['honeypot_form_user_pass'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_form_user_register_form';
  $strongarm->value = 1;
  $export['honeypot_form_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_log';
  $strongarm->value = 0;
  $export['honeypot_log'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_protect_all_forms';
  $strongarm->value = 0;
  $export['honeypot_protect_all_forms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_time_limit';
  $strongarm->value = '0';
  $export['honeypot_time_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_toolkit';
  $strongarm->value = 'gd';
  $export['image_toolkit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'install_profile';
  $strongarm->value = 'btranslator';
  $export['install_profile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'install_task';
  $strongarm->value = 'done';
  $export['install_task'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'install_time';
  $strongarm->value = 1342607877;
  $export['install_time'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_default_mail_template';
  $strongarm->value = '[invite:inviter-raw] has invited you to join [site:name] at [site:url].

To become a member of [site:name], click the link below or paste it into the address bar of your browser.

[invite:join-link]
';
  $export['invite_default_mail_template'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_expiry';
  $strongarm->value = '30';
  $export['invite_expiry'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_manual_from';
  $strongarm->value = '';
  $export['invite_manual_from'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_manual_reply_to';
  $strongarm->value = '';
  $export['invite_manual_reply_to'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_maxnum_1';
  $strongarm->value = '1000';
  $export['invite_maxnum_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_maxnum_2';
  $strongarm->value = '50';
  $export['invite_maxnum_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_maxnum_3';
  $strongarm->value = '50';
  $export['invite_maxnum_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_page_title';
  $strongarm->value = 'Invite a friend';
  $export['invite_page_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_profile_inviter';
  $strongarm->value = 1;
  $export['invite_profile_inviter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_registration_path';
  $strongarm->value = 'user/register';
  $export['invite_registration_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_require_approval';
  $strongarm->value = 0;
  $export['invite_require_approval'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_subject';
  $strongarm->value = '[invite:inviter-raw] has sent you an invite!';
  $export['invite_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_subject_editable';
  $strongarm->value = 1;
  $export['invite_subject_editable'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_target_role_1';
  $strongarm->value = '5';
  $export['invite_target_role_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_target_role_2';
  $strongarm->value = '5';
  $export['invite_target_role_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_target_role_3';
  $strongarm->value = '4';
  $export['invite_target_role_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_target_role_default';
  $strongarm->value = '5';
  $export['invite_target_role_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_use_users_email';
  $strongarm->value = '1';
  $export['invite_use_users_email'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'invite_use_users_email_replyto';
  $strongarm->value = '1';
  $export['invite_use_users_email_replyto'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_client_server';
  $strongarm->value = 'http://localize.drupal.org';
  $export['l10n_client_server'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_client_use_server';
  $strongarm->value = 1;
  $export['l10n_client_use_server'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_crontime';
  $strongarm->value = 1364176500;
  $export['l10n_feedback_crontime'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_cron_send_review_time';
  $strongarm->value = 1354326900;
  $export['l10n_feedback_cron_send_review_time'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_default_lng';
  $strongarm->value = 'sq';
  $export['l10n_feedback_default_lng'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_export_path';
  $strongarm->value = '/var/www/exports';
  $export['l10n_feedback_export_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_preferred_projects';
  $strongarm->value = 'misc/pingus
LibreOffice/sw
Mozilla/browser';
  $export['l10n_feedback_preferred_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_topcontrib_period';
  $strongarm->value = 'week';
  $export['l10n_feedback_topcontrib_period'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_topcontrib_size';
  $strongarm->value = '5';
  $export['l10n_feedback_topcontrib_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_translation_lng';
  $strongarm->value = 'sq';
  $export['l10n_feedback_translation_lng'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_feedback_voting_mode';
  $strongarm->value = 'single';
  $export['l10n_feedback_voting_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_update_check_disabled';
  $strongarm->value = 0;
  $export['l10n_update_check_disabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_update_check_frequency';
  $strongarm->value = '7';
  $export['l10n_update_check_frequency'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_update_check_mode';
  $strongarm->value = '3';
  $export['l10n_update_check_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_update_download_store';
  $strongarm->value = 'sites/all/translations';
  $export['l10n_update_download_store'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'l10n_update_import_mode';
  $strongarm->value = '0';
  $export['l10n_update_import_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_article';
  $strongarm->value = '0';
  $export['language_content_type_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_blog';
  $strongarm->value = '0';
  $export['language_content_type_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_book';
  $strongarm->value = '0';
  $export['language_content_type_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_page';
  $strongarm->value = '0';
  $export['language_content_type_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_simplenews';
  $strongarm->value = '0';
  $export['language_content_type_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_count';
  $strongarm->value = 2;
  $export['language_count'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_default';
  $strongarm->value = (object) array(
    'language' => 'en',
    'name' => 'English',
    'native' => 'English',
    'direction' => '0',
    'enabled' => 1,
    'plurals' => '0',
    'formula' => '',
    'domain' => '',
    'prefix' => 'en',
    'weight' => '0',
    'javascript' => '',
  );
  $export['language_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negotiation_language';
  $strongarm->value = array(
    'locale-user' => array(
      'callbacks' => array(
        'language' => 'locale_language_from_user',
      ),
      'file' => 'includes/locale.inc',
    ),
    'locale-browser' => array(
      'callbacks' => array(
        'language' => 'locale_language_from_browser',
      ),
      'file' => 'includes/locale.inc',
      'cache' => 0,
    ),
    'language-default' => array(
      'callbacks' => array(
        'language' => 'language_from_default',
      ),
    ),
  );
  $export['language_negotiation_language'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negotiation_language_content';
  $strongarm->value = array(
    'locale-interface' => array(
      'callbacks' => array(
        'language' => 'locale_language_from_interface',
      ),
      'file' => 'includes/locale.inc',
    ),
  );
  $export['language_negotiation_language_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_negotiation_language_url';
  $strongarm->value = array(
    'locale-url' => array(
      'callbacks' => array(
        'language' => 'locale_language_from_url',
        'switcher' => 'locale_language_switcher_url',
        'url_rewrite' => 'locale_language_url_rewrite_url',
      ),
      'file' => 'includes/locale.inc',
    ),
    'locale-url-fallback' => array(
      'callbacks' => array(
        'language' => 'locale_language_url_fallback',
      ),
      'file' => 'includes/locale.inc',
    ),
  );
  $export['language_negotiation_language_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_types';
  $strongarm->value = array(
    'language' => TRUE,
    'language_content' => FALSE,
    'language_url' => FALSE,
  );
  $export['language_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'locale_language_providers_weight_language';
  $strongarm->value = array(
    'locale-url' => '-8',
    'locale-session' => '-6',
    'locale-user' => '-4',
    'locale-browser' => '-2',
    'language-default' => '10',
  );
  $export['locale_language_providers_weight_language'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mailsystem_theme';
  $strongarm->value = 'current';
  $export['mailsystem_theme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mail_system';
  $strongarm->value = array(
    'default-system' => 'MimeMailSystem',
  );
  $export['mail_system'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'maintenance_mode';
  $strongarm->value = 0;
  $export['maintenance_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'maintenance_mode_message';
  $strongarm->value = 'Përkthimi i Programeve në Shqip is currently under maintenance. We should be back shortly. Thank you for your patience.';
  $export['maintenance_mode_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_attachment_location';
  $strongarm->value = 'mass_contact_attachments';
  $export['mass_contact_attachment_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_bcc_d';
  $strongarm->value = 1;
  $export['mass_contact_bcc_d'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_category_override';
  $strongarm->value = 0;
  $export['mass_contact_category_override'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_character_set';
  $strongarm->value = '';
  $export['mass_contact_character_set'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_default_sender_email';
  $strongarm->value = 'info@l10n.org.al';
  $export['mass_contact_default_sender_email'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_default_sender_name';
  $strongarm->value = 'l10n-sq';
  $export['mass_contact_default_sender_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_form_information';
  $strongarm->value = 'Send email messages using the following form.';
  $export['mass_contact_form_information'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_hourly_threshold';
  $strongarm->value = '3';
  $export['mass_contact_hourly_threshold'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_html_format';
  $strongarm->value = array(
    'value' => '<p>This text of this field is not saved or used anywhere.</p>',
    'format' => 'plain_text',
  );
  $export['mass_contact_html_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_message_prefix';
  $strongarm->value = array(
    'value' => '',
    'format' => 'filtered_html',
  );
  $export['mass_contact_message_prefix'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_message_suffix';
  $strongarm->value = array(
    'value' => '',
    'format' => 'filtered_html',
  );
  $export['mass_contact_message_suffix'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_nodecc_d';
  $strongarm->value = 0;
  $export['mass_contact_nodecc_d'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_number_of_attachments';
  $strongarm->value = '3';
  $export['mass_contact_number_of_attachments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_optout_d';
  $strongarm->value = '0';
  $export['mass_contact_optout_d'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_optout_message';
  $strongarm->value = 'Allows you to opt-out of receiving mass email messages from privileged users. Note that site administrators are able to include you in mass email messages even if you choose not to enable this feature, and the ability to opt-out may be removed by the administrator at any time.';
  $export['mass_contact_optout_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mass_contact_recipient_limit';
  $strongarm->value = '100';
  $export['mass_contact_recipient_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'memcache_wildcard_flushes';
  $strongarm->value = array(
    'cache' => array(
      'context' => array(
        7 => 1363514462,
      ),
      'plugins' => array(
        15 => 1363514462,
      ),
      'entity_' => array(
        21 => 1363514462,
        12 => 1364000316,
      ),
      'ctools_' => array(
        20 => 1363375336,
      ),
      'theme_r' => array(
        14 => 1364000316,
      ),
      'node_ty' => array(
        11 => 1364000316,
      ),
      'locale:' => array(
        7 => 1363874461,
      ),
      'schema:' => array(
        7 => 1364008436,
      ),
      'filter_' => array(
        14 => 1349510463,
        18 => 1349510463,
      ),
      'image_e' => array(
        14 => 1363423971,
      ),
    ),
    'cache_menu' => array(
      'links:devel:' => array(
        12 => 1363423971,
      ),
      'links:manage' => array(
        17 => 1364000762,
      ),
      'links:naviga' => array(
        17 => 1363423971,
      ),
      'links:user-m' => array(
        16 => 1363423971,
      ),
      'links:main-m' => array(
        16 => 1363423971,
      ),
    ),
    'cache_field' => array(
      'field_info_types:' => array(
        17 => 1349510268,
      ),
    ),
    'cache_rules' => array(
      'event_' => array(
        6 => 1349530596,
      ),
    ),
    'cache_l10n_feedback' => array(
      'l10n_feedback_rss_feed' => array(
        22 => 1353437933,
      ),
    ),
    'cache_filter' => array(
      'full_html:' => array(
        10 => 1363423971,
      ),
      'plain_text' => array(
        11 => 1363423971,
      ),
    ),
  );
  $export['memcache_wildcard_flushes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_expanded';
  $strongarm->value = array();
  $export['menu_expanded'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_masks';
  $strongarm->value = array(
    0 => 507,
    1 => 506,
    2 => 501,
    3 => 493,
    4 => 253,
    5 => 252,
    6 => 250,
    7 => 247,
    8 => 246,
    9 => 245,
    10 => 127,
    11 => 126,
    12 => 125,
    13 => 124,
    14 => 123,
    15 => 122,
    16 => 121,
    17 => 117,
    18 => 63,
    19 => 62,
    20 => 61,
    21 => 60,
    22 => 59,
    23 => 58,
    24 => 52,
    25 => 44,
    26 => 31,
    27 => 30,
    28 => 29,
    29 => 28,
    30 => 27,
    31 => 25,
    32 => 24,
    33 => 21,
    34 => 15,
    35 => 14,
    36 => 13,
    37 => 12,
    38 => 11,
    39 => 7,
    40 => 6,
    41 => 5,
    42 => 3,
    43 => 2,
    44 => 1,
  );
  $export['menu_masks'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_article';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_blog';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_book';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_page';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_projects';
  $strongarm->value = array(
    0 => 'main_menu',
  );
  $export['menu_options_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_simplenews';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_article';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_blog';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_book';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_page';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_projects';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_simplenews';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_engine';
  $strongarm->value = 'phpmailer';
  $export['mimemail_engine'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_format';
  $strongarm->value = 'full_html';
  $export['mimemail_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_incoming';
  $strongarm->value = 0;
  $export['mimemail_incoming'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_key';
  $strongarm->value = 'f21eaf5327ff03d33e684c6dee1b36bf';
  $export['mimemail_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_linkonly';
  $strongarm->value = 1;
  $export['mimemail_linkonly'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_mail';
  $strongarm->value = 'info@l10n.org.al';
  $export['mimemail_mail'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_name';
  $strongarm->value = 'Përkthimi i Programeve';
  $export['mimemail_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_preserve_class';
  $strongarm->value = 0;
  $export['mimemail_preserve_class'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_simple_address';
  $strongarm->value = 1;
  $export['mimemail_simple_address'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_sitestyle';
  $strongarm->value = 1;
  $export['mimemail_sitestyle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mimemail_textonly';
  $strongarm->value = 0;
  $export['mimemail_textonly'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_admin_theme';
  $strongarm->value = '1';
  $export['node_admin_theme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_cron_last';
  $strongarm->value = '1361571285';
  $export['node_cron_last'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_article';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_blog';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_book';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_page';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_projects';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_simplenews';
  $strongarm->value = array();
  $export['node_options_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_article';
  $strongarm->value = '1';
  $export['node_preview_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_blog';
  $strongarm->value = '1';
  $export['node_preview_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_book';
  $strongarm->value = '1';
  $export['node_preview_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_page';
  $strongarm->value = '1';
  $export['node_preview_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_projects';
  $strongarm->value = 1;
  $export['node_preview_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_simplenews';
  $strongarm->value = '1';
  $export['node_preview_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_article';
  $strongarm->value = 1;
  $export['node_submitted_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_blog';
  $strongarm->value = 1;
  $export['node_submitted_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_book';
  $strongarm->value = 1;
  $export['node_submitted_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_page';
  $strongarm->value = 0;
  $export['node_submitted_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_projects';
  $strongarm->value = 0;
  $export['node_submitted_projects'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_simplenews';
  $strongarm->value = 1;
  $export['node_submitted_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_cache_maximum_age';
  $strongarm->value = '3600';
  $export['page_cache_maximum_age'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_compression';
  $strongarm->value = 1;
  $export['page_compression'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'path_alias_whitelist';
  $strongarm->value = array(
    'node' => TRUE,
  );
  $export['path_alias_whitelist'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'phpmailer_test';
  $strongarm->value = '';
  $export['phpmailer_test'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'preprocess_css';
  $strongarm->value = 1;
  $export['preprocess_css'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'preprocess_js';
  $strongarm->value = 1;
  $export['preprocess_js'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recaptcha_ajax_api';
  $strongarm->value = 1;
  $export['recaptcha_ajax_api'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recaptcha_nocookies';
  $strongarm->value = 1;
  $export['recaptcha_nocookies'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recaptcha_private_key';
  $strongarm->value = '6Ldy99kSAAAAAHyOKD67PDYgCRYo7JQMhWKChJep';
  $export['recaptcha_private_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recaptcha_public_key';
  $strongarm->value = '6Ldy99kSAAAAAKJb6SP38FOO1iuLtD0lqSTw4wcI';
  $export['recaptcha_public_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recaptcha_secure_connection';
  $strongarm->value = 1;
  $export['recaptcha_secure_connection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recaptcha_tabindex';
  $strongarm->value = '';
  $export['recaptcha_tabindex'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'recaptcha_theme';
  $strongarm->value = 'red';
  $export['recaptcha_theme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reroute_email_address';
  $strongarm->value = 'dashohoxha@gmail.com';
  $export['reroute_email_address'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reroute_email_enable';
  $strongarm->value = 0;
  $export['reroute_email_enable'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'reroute_email_enable_message';
  $strongarm->value = 0;
  $export['reroute_email_enable_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_accounts_string';
  $strongarm->value = 'Linked accounts';
  $export['rpx_accounts_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_admin_url';
  $strongarm->value = 'https://rpxnow.com/relying_parties/l10n-sq';
  $export['rpx_admin_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_apikey';
  $strongarm->value = '103558b4ea0b138909029b819232cb72916ed4ef';
  $export['rpx_apikey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_app_id';
  $strongarm->value = 'fonjnfhnjmhaimefiolj';
  $export['rpx_app_id'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_login_form';
  $strongarm->value = 1;
  $export['rpx_attach_login_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_comments_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_comments_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_nodecont_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_nodecont_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_nodecont_weight_simplenews';
  $strongarm->value = '40';
  $export['rpx_attach_share_link_to_nodecont_weight_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_nodelink_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_nodelink_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_teasers_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_teasers_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_bypass_email_verification';
  $strongarm->value = 0;
  $export['rpx_bypass_email_verification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_comment_popup_social_at_once_simplenews';
  $strongarm->value = 0;
  $export['rpx_comment_popup_social_at_once_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_label_comments';
  $strongarm->value = 'Share your comment:';
  $export['rpx_default_label_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_label_nodes';
  $strongarm->value = 'Comment:';
  $export['rpx_default_label_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_linktext_comments';
  $strongarm->value = '[comment:subject]';
  $export['rpx_default_linktext_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_linktext_nodes';
  $strongarm->value = '[node:title]';
  $export['rpx_default_linktext_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_message_comments';
  $strongarm->value = 'Commented on [site:name].';
  $export['rpx_default_message_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_message_nodes';
  $strongarm->value = 'Shared [node:title] on [site:name].';
  $export['rpx_default_message_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_summary_comments';
  $strongarm->value = '[comment:body]';
  $export['rpx_default_summary_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_summary_nodes';
  $strongarm->value = '[node:body]';
  $export['rpx_default_summary_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_title_comments';
  $strongarm->value = '[node:title] | [site:name]';
  $export['rpx_default_title_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_title_nodes';
  $strongarm->value = '[node:title] | [site:name]';
  $export['rpx_default_title_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_enabled_providers';
  $strongarm->value = array(
    0 => 'google',
    1 => 'facebook',
    2 => 'twitter',
    3 => 'linkedin',
    4 => 'paypal',
  );
  $export['rpx_enabled_providers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_extended_authinfo';
  $strongarm->value = 0;
  $export['rpx_extended_authinfo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_force_registration_form';
  $strongarm->value = 1;
  $export['rpx_force_registration_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_import_profile_photo';
  $strongarm->value = 1;
  $export['rpx_import_profile_photo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_javascript_global';
  $strongarm->value = 1;
  $export['rpx_javascript_global'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_label_comments_simplenews';
  $strongarm->value = 'Share your comment:';
  $export['rpx_label_comments_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_label_nodes_simplenews';
  $strongarm->value = 'Comment:';
  $export['rpx_label_nodes_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_linktext_comments_simplenews';
  $strongarm->value = '[comment:subject]';
  $export['rpx_linktext_comments_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_linktext_nodes_simplenews';
  $strongarm->value = '[node:title]';
  $export['rpx_linktext_nodes_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_login_icons_size';
  $strongarm->value = 'medium';
  $export['rpx_login_icons_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_login_links_weight';
  $strongarm->value = '-150';
  $export['rpx_login_links_weight'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_mail_rpx_confirm_email_body';
  $strongarm->value = '[user:name],

Thank you for registering at [site:name].

To confirm your email address, click on this link or copy and paste it in your browser:

[user:one-time-login-url]

After confirming your email address, you will be able to log in to [site:name] using your new account.

--  [site:name] team';
  $export['rpx_mail_rpx_confirm_email_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_mail_rpx_confirm_email_subject';
  $strongarm->value = 'Confirm your account at [site:name]';
  $export['rpx_mail_rpx_confirm_email_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_mapping_api';
  $strongarm->value = 0;
  $export['rpx_mapping_api'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_message_comments_simplenews';
  $strongarm->value = 'Commented on [site:name].';
  $export['rpx_message_comments_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_message_nodes_simplenews';
  $strongarm->value = 'Shared [node:title] on [site:name].';
  $export['rpx_message_nodes_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_openid_override';
  $strongarm->value = 1;
  $export['rpx_openid_override'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_realm';
  $strongarm->value = 'l10n-sq.rpxnow.com';
  $export['rpx_realm'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_realm_scheme';
  $strongarm->value = 'https';
  $export['rpx_realm_scheme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_signin_string';
  $strongarm->value = 'Sign in with one of these:';
  $export['rpx_signin_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_social_enabled';
  $strongarm->value = 1;
  $export['rpx_social_enabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_social_pub';
  $strongarm->value = '';
  $export['rpx_social_pub'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_summary_comments_simplenews';
  $strongarm->value = '[comment:body]';
  $export['rpx_summary_comments_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_summary_nodes_simplenews';
  $strongarm->value = '[node:body]';
  $export['rpx_summary_nodes_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_title_comments_simplenews';
  $strongarm->value = '[node:title] | [site:name]';
  $export['rpx_title_comments_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_title_nodes_simplenews';
  $strongarm->value = '[node:title] | [site:name]';
  $export['rpx_title_nodes_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_user_help_text';
  $strongarm->value = '<p>This site supports <a href="http://www.janrain.com/products/engage/">Janrain Engage</a>, an easy way to log in to many websites using your account with Facebook, Google, Yahoo!, Twitter and other identity providers. Janrain Engage can reduce the necessity of managing many usernames and passwords for many websites.</p><p>To use Janrain Engage, choose a provider and sign in if prompted. Upon successful signin you will be returned to this site as a registered user. Next time you log in, you will be able to use the same 3rd party account instead of a regular username and password. You can have multiple 3rd party accounts if you like; just keep adding them here.</p>';
  $export['rpx_user_help_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'settings__active_tab';
  $strongarm->value = 'edit-visibility';
  $export['settings__active_tab'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_button_option';
  $strongarm->value = 'stbc_button';
  $export['sharethis_button_option'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_comments';
  $strongarm->value = 0;
  $export['sharethis_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_late_load';
  $strongarm->value = 1;
  $export['sharethis_late_load'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_location';
  $strongarm->value = 'content';
  $export['sharethis_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_node_option';
  $strongarm->value = 'blog,article,book,page,simplenews,0';
  $export['sharethis_node_option'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_option_extras';
  $strongarm->value = array(
    'Google Plus One:plusone' => 'Google Plus One:plusone',
    'Facebook Like:fblike' => 'Facebook Like:fblike',
  );
  $export['sharethis_option_extras'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_publisherID';
  $strongarm->value = 'dr-672ae048-d016-4521-d2b0-21ad1caa3490';
  $export['sharethis_publisherID'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_service_option';
  $strongarm->value = '"Google +:googleplus","Facebook:facebook","Tweet:twitter","LinkedIn:linkedin","Email:email","ShareThis:sharethis"';
  $export['sharethis_service_option'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_teaser_option';
  $strongarm->value = 1;
  $export['sharethis_teaser_option'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_twitter_handle';
  $strongarm->value = 'https://twitter.com/l10n_sq';
  $export['sharethis_twitter_handle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_twitter_suffix';
  $strongarm->value = 'l10n_sq';
  $export['sharethis_twitter_suffix'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_weight';
  $strongarm->value = '50';
  $export['sharethis_weight'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'sharethis_widget_option';
  $strongarm->value = 'st_multi';
  $export['sharethis_widget_option'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_article';
  $strongarm->value = 0;
  $export['show_diff_inline_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_blog';
  $strongarm->value = 0;
  $export['show_diff_inline_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_book';
  $strongarm->value = 0;
  $export['show_diff_inline_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_diff_inline_page';
  $strongarm->value = 0;
  $export['show_diff_inline_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_article';
  $strongarm->value = 1;
  $export['show_preview_changes_article'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_blog';
  $strongarm->value = 1;
  $export['show_preview_changes_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_book';
  $strongarm->value = 1;
  $export['show_preview_changes_book'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'show_preview_changes_page';
  $strongarm->value = 1;
  $export['show_preview_changes_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_combined_body';
  $strongarm->value = 'We have received a request for the following subscription changes for [simplenews-subscriber:mail] at [site:url]:

[changes-list]

To confirm please use the link below.

[simplenews-subscriber:combined-url]';
  $export['simplenews_confirm_combined_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_combined_body_unchanged';
  $strongarm->value = 'We have received a request for the following subscription changes for [simplenews-subscriber:mail] at [site:url]:

[changes-list]

No confirmation necessary because all requested changes equal the current state.';
  $export['simplenews_confirm_combined_body_unchanged'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_combined_line_subscribe_subscribed';
  $strongarm->value = 'Already subscribed to [simplenews-category:name]';
  $export['simplenews_confirm_combined_line_subscribe_subscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_combined_line_subscribe_unsubscribed';
  $strongarm->value = 'Subscribe to [simplenews-category:name]';
  $export['simplenews_confirm_combined_line_subscribe_unsubscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_combined_line_unsubscribe_subscribed';
  $strongarm->value = 'Unsubscribe from [simplenews-category:name]';
  $export['simplenews_confirm_combined_line_unsubscribe_subscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_combined_line_unsubscribe_unsubscribed';
  $strongarm->value = 'Already unsubscribed from [simplenews-category:name]';
  $export['simplenews_confirm_combined_line_unsubscribe_unsubscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_combined_subject';
  $strongarm->value = 'Confirmation for [site:name]';
  $export['simplenews_confirm_combined_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_subscribe_page';
  $strongarm->value = '';
  $export['simplenews_confirm_subscribe_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_subscribe_subject';
  $strongarm->value = 'Confirmation for [simplenews-category:name] from [site:name]';
  $export['simplenews_confirm_subscribe_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_subscribe_subscribed';
  $strongarm->value = 'We have received a request to subscribe [simplenews-subscriber:mail] to the [simplenews-category:name]  newsletter on [site:name] website at [site:url]. However, this email is already subscribed to this newsletter. If you intended to unsubscribe please visit our site: [site:url]';
  $export['simplenews_confirm_subscribe_subscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_subscribe_unsubscribed';
  $strongarm->value = 'We have received a request to subscribe [simplenews-subscriber:mail] to the [simplenews-category:name] newsletter on [site:name] website at [site:url]. To confirm please use the link below.

[simplenews-subscriber:subscribe-url]';
  $export['simplenews_confirm_subscribe_unsubscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_unsubscribe_page';
  $strongarm->value = '';
  $export['simplenews_confirm_unsubscribe_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_unsubscribe_subscribed';
  $strongarm->value = 'We have received a request to remove the [simplenews-subscriber:mail] from the [simplenews-category:name] mailing list on [site:name] website at [site:url]. To confirm please use the link below.

[simplenews-subscriber:unsubscribe-url]';
  $export['simplenews_confirm_unsubscribe_subscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_confirm_unsubscribe_unsubscribed';
  $strongarm->value = 'We have received a request to remove the [simplenews-subscriber:mail] from the [simplenews-category:name] mailing list on [site:name] website at [site:url]. However, this email is not subscribed to this mailing list. If you intended to subscribe please visit our site at [site:url]';
  $export['simplenews_confirm_unsubscribe_unsubscribed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_content_type_simplenews';
  $strongarm->value = 1;
  $export['simplenews_content_type_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_debug';
  $strongarm->value = 1;
  $export['simplenews_debug'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_format';
  $strongarm->value = 'html';
  $export['simplenews_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_from_address';
  $strongarm->value = 'info@l10n.org.al';
  $export['simplenews_from_address'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_from_name';
  $strongarm->value = 'Përkthimi i Programeve';
  $export['simplenews_from_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_last_cron';
  $strongarm->value = 1358845261;
  $export['simplenews_last_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_last_sent';
  $strongarm->value = 31;
  $export['simplenews_last_sent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_priority';
  $strongarm->value = '0';
  $export['simplenews_priority'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_private_key';
  $strongarm->value = 'b8eb19dccd40fcbcb17138824480de50';
  $export['simplenews_private_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_receipt';
  $strongarm->value = 0;
  $export['simplenews_receipt'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_send';
  $strongarm->value = '0';
  $export['simplenews_send'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_source_cache';
  $strongarm->value = 'SimplenewsSourceCacheBuild';
  $export['simplenews_source_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_spool_expire';
  $strongarm->value = '0';
  $export['simplenews_spool_expire'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_sync_account';
  $strongarm->value = 1;
  $export['simplenews_sync_account'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_test_address';
  $strongarm->value = 'dashohoxha@gmail.com';
  $export['simplenews_test_address'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_test_address_override';
  $strongarm->value = 1;
  $export['simplenews_test_address_override'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_throttle';
  $strongarm->value = '50';
  $export['simplenews_throttle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_use_combined';
  $strongarm->value = 'multiple';
  $export['simplenews_use_combined'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_use_cron';
  $strongarm->value = 1;
  $export['simplenews_use_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplenews_vid';
  $strongarm->value = '2';
  $export['simplenews_vid'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_403';
  $strongarm->value = '';
  $export['site_403'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_404';
  $strongarm->value = '';
  $export['site_404'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_default_country';
  $strongarm->value = 'AL';
  $export['site_default_country'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'node';
  $export['site_frontpage'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_mail';
  $strongarm->value = 'info@l10n.org.al';
  $export['site_mail'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_name';
  $strongarm->value = 'Përkthimi i Programeve në Shqip';
  $export['site_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_slogan';
  $strongarm->value = 'E duam kompjuterin në gjuhën shqipe.';
  $export['site_slogan'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_allowhtml';
  $strongarm->value = 1;
  $export['smtp_allowhtml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_always_replyto';
  $strongarm->value = 1;
  $export['smtp_always_replyto'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_debug';
  $strongarm->value = '0';
  $export['smtp_debug'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_debugging';
  $strongarm->value = 0;
  $export['smtp_debugging'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_from';
  $strongarm->value = 'info@l10n.org.al';
  $export['smtp_from'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_fromname';
  $strongarm->value = 'l10n sq';
  $export['smtp_fromname'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_hide_password';
  $strongarm->value = 1;
  $export['smtp_hide_password'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_host';
  $strongarm->value = 'smtp.googlemail.com';
  $export['smtp_host'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_hostbackup';
  $strongarm->value = '';
  $export['smtp_hostbackup'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_keepalive';
  $strongarm->value = 1;
  $export['smtp_keepalive'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_library';
  $strongarm->value = 'profiles/btranslator/modules/smtp/smtp.module';
  $export['smtp_library'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_on';
  $strongarm->value = 1;
  $export['smtp_on'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_password';
  $strongarm->value = 'lakVirn7';
  $export['smtp_password'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_port';
  $strongarm->value = '465';
  $export['smtp_port'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_protocol';
  $strongarm->value = 'ssl';
  $export['smtp_protocol'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'smtp_username';
  $strongarm->value = 'info@l10n.org.al';
  $export['smtp_username'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_bartik1_settings';
  $strongarm->value = array(
    'toggle_logo' => 0,
    'toggle_name' => 1,
    'toggle_slogan' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 1,
    'toggle_main_menu' => 1,
    'toggle_secondary_menu' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
    'scheme' => '',
    'palette' => array(
      'top' => '#2268a1',
      'bottom' => '#48a9e4',
      'bg' => '#ffffff',
      'sidebar' => '#d8eaf9',
      'sidebarborders' => '#b7d7f1',
      'footer' => '#2268a1',
      'titleslogan' => '#fffeff',
      'text' => '#3b3b3b',
      'link' => '#0071B3',
    ),
    'theme' => 'bartik1',
    'info' => array(
      'fields' => array(
        'top' => 'Header top',
        'bottom' => 'Header bottom',
        'bg' => 'Main background',
        'sidebar' => 'Sidebar background',
        'sidebarborders' => 'Sidebar borders',
        'footer' => 'Footer background',
        'titleslogan' => 'Title and slogan',
        'text' => 'Text color',
        'link' => 'Link color',
      ),
      'schemes' => array(
        'default' => array(
          'title' => 'Blue Lagoon (default)',
          'colors' => array(
            'top' => '#0779bf',
            'bottom' => '#48a9e4',
            'bg' => '#ffffff',
            'sidebar' => '#f6f6f2',
            'sidebarborders' => '#f9f9f9',
            'footer' => '#292929',
            'titleslogan' => '#fffeff',
            'text' => '#3b3b3b',
            'link' => '#0071B3',
          ),
        ),
        'firehouse' => array(
          'title' => 'Firehouse',
          'colors' => array(
            'top' => '#cd2d2d',
            'bottom' => '#cf3535',
            'bg' => '#ffffff',
            'sidebar' => '#f1f4f0',
            'sidebarborders' => '#ededed',
            'footer' => '#1f1d1c',
            'titleslogan' => '#fffeff',
            'text' => '#3b3b3b',
            'link' => '#d6121f',
          ),
        ),
        'ice' => array(
          'title' => 'Ice',
          'colors' => array(
            'top' => '#d0d0d0',
            'bottom' => '#c2c4c5',
            'bg' => '#ffffff',
            'sidebar' => '#ffffff',
            'sidebarborders' => '#cccccc',
            'footer' => '#24272c',
            'titleslogan' => '#000000',
            'text' => '#4a4a4a',
            'link' => '#019dbf',
          ),
        ),
        'plum' => array(
          'title' => 'Plum',
          'colors' => array(
            'top' => '#4c1c58',
            'bottom' => '#593662',
            'bg' => '#fffdf7',
            'sidebar' => '#edede7',
            'sidebarborders' => '#e7e7e7',
            'footer' => '#2c2c28',
            'titleslogan' => '#ffffff',
            'text' => '#301313',
            'link' => '#9d408d',
          ),
        ),
        'slate' => array(
          'title' => 'Slate',
          'colors' => array(
            'top' => '#4a4a4a',
            'bottom' => '#4e4e4e',
            'bg' => '#ffffff',
            'sidebar' => '#ffffff',
            'sidebarborders' => '#d0d0d0',
            'footer' => '#161617',
            'titleslogan' => '#ffffff',
            'text' => '#3b3b3b',
            'link' => '#0073b6',
          ),
        ),
        '' => array(
          'title' => 'Custom',
          'colors' => array(),
        ),
      ),
      'css' => array(
        0 => 'css/colors.css',
      ),
      'copy' => array(
        0 => 'logo.png',
      ),
      'gradients' => array(
        0 => array(
          'dimension' => array(
            0 => 0,
            1 => 0,
            2 => 0,
            3 => 0,
          ),
          'direction' => 'vertical',
          'colors' => array(
            0 => 'top',
            1 => 'bottom',
          ),
        ),
      ),
      'fill' => array(),
      'slices' => array(),
      'blend_target' => '#ffffff',
      'preview_css' => 'color/preview.css',
      'preview_js' => 'color/preview.js',
      'preview_html' => 'color/preview.html',
      'base_image' => 'color/base.png',
    ),
  );
  $export['theme_bartik1_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_bartik_fb_settings';
  $strongarm->value = array(
    'toggle_logo' => 0,
    'toggle_name' => 1,
    'toggle_slogan' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 1,
    'toggle_main_menu' => 1,
    'toggle_secondary_menu' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
    'scheme' => '',
    'palette' => array(
      'bg' => '#ffffff',
      'link' => '#0071B3',
      'top' => '#2268a1',
      'bottom' => '#48a9e4',
      'text' => '#3b3b3b',
      'sidebar' => '#d8eaf9',
      'sidebarborders' => '#b7d7f1',
      'footer' => '#2268a1',
      'titleslogan' => '#fffeff',
    ),
    'theme' => 'bartik_fb',
    'info' => array(
      'fields' => array(
        'bg' => 'Main background',
        'link' => 'Link color',
        'top' => 'Header top',
        'bottom' => 'Header bottom',
        'text' => 'Text color',
        'sidebar' => 'Sidebar background',
        'sidebarborders' => 'Sidebar borders',
        'footer' => 'Footer background',
        'titleslogan' => 'Title and slogan',
      ),
      'schemes' => array(
        'default' => array(
          'title' => 'Blue Lagoon (default)',
          'colors' => array(
            'bg' => '#ffffff',
            'link' => '#0071B3',
            'top' => '#0779bf',
            'bottom' => '#48a9e4',
            'text' => '#3b3b3b',
            'sidebar' => '#f6f6f2',
            'sidebarborders' => '#f9f9f9',
            'footer' => '#292929',
            'titleslogan' => '#fffeff',
          ),
        ),
        'facebook' => array(
          'title' => 'Facebook',
          'colors' => array(
            'bg' => '#ffffff',
            'link' => '#3b5998',
            'top' => '#3b5998',
            'bottom' => '#627aad',
            'text' => '#333',
            'sidebar' => '#e5e5e5',
            'sidebarborders' => '#ccc',
            'footer' => '#292929',
            'titleslogan' => '#fffeff',
          ),
        ),
        'firehouse' => array(
          'title' => 'Firehouse',
          'colors' => array(
            'bg' => '#ffffff',
            'link' => '#d6121f',
            'top' => '#cd2d2d',
            'bottom' => '#cf3535',
            'text' => '#3b3b3b',
            'sidebar' => '#f1f4f0',
            'sidebarborders' => '#ededed',
            'footer' => '#1f1d1c',
            'titleslogan' => '#fffeff',
          ),
        ),
        'ice' => array(
          'title' => 'Ice',
          'colors' => array(
            'bg' => '#ffffff',
            'link' => '#019dbf',
            'top' => '#d0d0d0',
            'bottom' => '#c2c4c5',
            'text' => '#4a4a4a',
            'sidebar' => '#ffffff',
            'sidebarborders' => '#cccccc',
            'footer' => '#24272c',
            'titleslogan' => '#000000',
          ),
        ),
        'plum' => array(
          'title' => 'Plum',
          'colors' => array(
            'bg' => '#fffdf7',
            'link' => '#9d408d',
            'top' => '#4c1c58',
            'bottom' => '#593662',
            'text' => '#301313',
            'sidebar' => '#edede7',
            'sidebarborders' => '#e7e7e7',
            'footer' => '#2c2c28',
            'titleslogan' => '#ffffff',
          ),
        ),
        'slate' => array(
          'title' => 'Slate',
          'colors' => array(
            'bg' => '#ffffff',
            'link' => '#0073b6',
            'top' => '#4a4a4a',
            'bottom' => '#4e4e4e',
            'text' => '#3b3b3b',
            'sidebar' => '#ffffff',
            'sidebarborders' => '#d0d0d0',
            'footer' => '#161617',
            'titleslogan' => '#ffffff',
          ),
        ),
        '' => array(
          'title' => 'Custom',
          'colors' => array(),
        ),
      ),
      'css' => array(
        0 => 'css/colors.css',
      ),
      'copy' => array(
        0 => 'logo.png',
      ),
      'gradients' => array(
        0 => array(
          'dimension' => array(
            0 => 0,
            1 => 0,
            2 => 0,
            3 => 0,
          ),
          'direction' => 'vertical',
          'colors' => array(
            0 => 'top',
            1 => 'bottom',
          ),
        ),
      ),
      'fill' => array(),
      'slices' => array(),
      'blend_target' => '#ffffff',
      'preview_css' => 'color/preview.css',
      'preview_js' => 'color/preview.js',
      'preview_html' => 'color/preview.html',
      'base_image' => 'color/base.png',
    ),
  );
  $export['theme_bartik_fb_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_bartik_settings';
  $strongarm->value = array(
    'toggle_logo' => 0,
    'toggle_name' => 1,
    'toggle_slogan' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 0,
    'toggle_main_menu' => 1,
    'toggle_secondary_menu' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
    'scheme' => '',
    'palette' => array(
      'top' => '#2268a1',
      'bottom' => '#48a9e4',
      'bg' => '#ffffff',
      'sidebar' => '#d8eaf9',
      'sidebarborders' => '#b7d7f1',
      'footer' => '#2268a1',
      'titleslogan' => '#fffeff',
      'text' => '#3b3b3b',
      'link' => '#0071B3',
    ),
    'theme' => 'bartik',
    'info' => array(
      'fields' => array(
        'top' => 'Header top',
        'bottom' => 'Header bottom',
        'bg' => 'Main background',
        'sidebar' => 'Sidebar background',
        'sidebarborders' => 'Sidebar borders',
        'footer' => 'Footer background',
        'titleslogan' => 'Title and slogan',
        'text' => 'Text color',
        'link' => 'Link color',
      ),
      'schemes' => array(
        'default' => array(
          'title' => 'Blue Lagoon (default)',
          'colors' => array(
            'top' => '#0779bf',
            'bottom' => '#48a9e4',
            'bg' => '#ffffff',
            'sidebar' => '#f6f6f2',
            'sidebarborders' => '#f9f9f9',
            'footer' => '#292929',
            'titleslogan' => '#fffeff',
            'text' => '#3b3b3b',
            'link' => '#0071B3',
          ),
        ),
        'firehouse' => array(
          'title' => 'Firehouse',
          'colors' => array(
            'top' => '#cd2d2d',
            'bottom' => '#cf3535',
            'bg' => '#ffffff',
            'sidebar' => '#f1f4f0',
            'sidebarborders' => '#ededed',
            'footer' => '#1f1d1c',
            'titleslogan' => '#fffeff',
            'text' => '#3b3b3b',
            'link' => '#d6121f',
          ),
        ),
        'ice' => array(
          'title' => 'Ice',
          'colors' => array(
            'top' => '#d0d0d0',
            'bottom' => '#c2c4c5',
            'bg' => '#ffffff',
            'sidebar' => '#ffffff',
            'sidebarborders' => '#cccccc',
            'footer' => '#24272c',
            'titleslogan' => '#000000',
            'text' => '#4a4a4a',
            'link' => '#019dbf',
          ),
        ),
        'plum' => array(
          'title' => 'Plum',
          'colors' => array(
            'top' => '#4c1c58',
            'bottom' => '#593662',
            'bg' => '#fffdf7',
            'sidebar' => '#edede7',
            'sidebarborders' => '#e7e7e7',
            'footer' => '#2c2c28',
            'titleslogan' => '#ffffff',
            'text' => '#301313',
            'link' => '#9d408d',
          ),
        ),
        'slate' => array(
          'title' => 'Slate',
          'colors' => array(
            'top' => '#4a4a4a',
            'bottom' => '#4e4e4e',
            'bg' => '#ffffff',
            'sidebar' => '#ffffff',
            'sidebarborders' => '#d0d0d0',
            'footer' => '#161617',
            'titleslogan' => '#ffffff',
            'text' => '#3b3b3b',
            'link' => '#0073b6',
          ),
        ),
        '' => array(
          'title' => 'Custom',
          'colors' => array(),
        ),
      ),
      'css' => array(
        0 => 'css/colors.css',
      ),
      'copy' => array(
        0 => 'logo.png',
      ),
      'gradients' => array(
        0 => array(
          'dimension' => array(
            0 => 0,
            1 => 0,
            2 => 0,
            3 => 0,
          ),
          'direction' => 'vertical',
          'colors' => array(
            0 => 'top',
            1 => 'bottom',
          ),
        ),
      ),
      'fill' => array(),
      'slices' => array(),
      'blend_target' => '#ffffff',
      'preview_css' => 'color/preview.css',
      'preview_js' => 'color/preview.js',
      'preview_html' => 'color/preview.html',
      'base_image' => 'color/base.png',
    ),
  );
  $export['theme_bartik_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_blueprint_settings';
  $strongarm->value = array(
    'blueprint_block_edit_links' => '1',
    'blueprint_rebuild_registry' => '0',
    'blueprint_showgrid' => '0',
    'blueprint_animated_submit' => '1',
    'toggle_logo' => 0,
    'toggle_name' => 1,
    'toggle_slogan' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_favicon' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
  );
  $export['theme_blueprint_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_BPSTARTER_settings';
  $strongarm->value = array(
    'blueprint_block_edit_links' => '1',
    'blueprint_rebuild_registry' => '0',
    'blueprint_showgrid' => '0',
  );
  $export['theme_BPSTARTER_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_default';
  $strongarm->value = 'bartik1';
  $export['theme_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_rubik_settings';
  $strongarm->value = array(
    'toggle_logo' => 0,
    'toggle_name' => 1,
    'toggle_slogan' => 1,
    'toggle_node_user_picture' => 1,
    'toggle_comment_user_picture' => 1,
    'toggle_comment_user_verification' => 1,
    'toggle_favicon' => 1,
    'toggle_main_menu' => 1,
    'toggle_secondary_menu' => 1,
    'default_logo' => 1,
    'logo_path' => '',
    'logo_upload' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'favicon_upload' => '',
  );
  $export['theme_rubik_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tracking__active_tab';
  $strongarm->value = 'edit-privacy';
  $export['tracking__active_tab'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'update_check_disabled';
  $strongarm->value = 0;
  $export['update_check_disabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'update_check_frequency';
  $strongarm->value = '7';
  $export['update_check_frequency'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'update_last_check';
  $strongarm->value = 1364014910;
  $export['update_last_check'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'update_last_email_notification';
  $strongarm->value = 1363982462;
  $export['update_last_email_notification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'update_notification_threshold';
  $strongarm->value = 'all';
  $export['update_notification_threshold'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'update_notify_emails';
  $strongarm->value = array(
    0 => 'dashohoxha@gmail.com',
  );
  $export['update_notify_emails'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_admin_role';
  $strongarm->value = '3';
  $export['user_admin_role'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_cancel_method';
  $strongarm->value = 'user_cancel_block';
  $export['user_cancel_method'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_dashboard_available_blocks';
  $strongarm->value = array(
    'node_recent' => 'node_recent',
    'search_form' => 'search_form',
    'user_new' => 'user_new',
    'blog_recent' => 'blog_recent',
    'comment_recent' => 'comment_recent',
    'user_online' => 'user_online',
    'disqus_disqus_combination_widget' => 'disqus_disqus_combination_widget',
    'disqus_disqus_comments' => 'disqus_disqus_comments',
    'disqus_disqus_popular_threads' => 'disqus_disqus_popular_threads',
    'disqus_disqus_recent_comments' => 'disqus_disqus_recent_comments',
    'disqus_disqus_top_commenters' => 'disqus_disqus_top_commenters',
    'invite_invite' => 'invite_invite',
    'locale_language' => 'locale_language',
    'node_syndicate' => 'node_syndicate',
    'invite_stats_top_inviters' => 'invite_stats_top_inviters',
    'system_user-menu' => 'system_user-menu',
    'system_main' => 0,
    'user_login' => 0,
    'system_help' => 0,
    'book_navigation' => 0,
    'boost_status' => 0,
    'context_ui_editor' => 0,
    'context_ui_devel' => 0,
    'menu_devel' => 0,
    'devel_execute_php' => 0,
    'menu_features' => 0,
    'homebox_custom' => 0,
    'system_main-menu' => 0,
    'system_management' => 0,
    'system_navigation' => 0,
    'simplenews_2' => 0,
    'simplenews_0' => 0,
    'simplenews_1' => 0,
    'system_powered-by' => 0,
    'devel_switch_user' => 0,
  );
  $export['user_dashboard_available_blocks'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_dashboard_default_blocks';
  $strongarm->value = array(
    0 => (object) array(
      'module' => 'user',
      'delta' => 'new',
      'region' => 'user_dashboard_main',
      'weight' => 0,
      'status' => 1,
      'theme' => 'bartik',
    ),
    1 => (object) array(
      'module' => 'user',
      'delta' => 'online',
      'region' => 'user_dashboard_sidebar',
      'weight' => 0,
      'status' => 1,
      'theme' => 'bartik',
    ),
    2 => (object) array(
      'module' => 'disqus',
      'delta' => NULL,
      'region' => 'user_dashboard_sidebar',
      'weight' => 1,
      'status' => 1,
      'theme' => 'bartik',
    ),
    3 => (object) array(
      'module' => 'node',
      'delta' => 'recent',
      'region' => 'user_dashboard_column1',
      'weight' => 0,
      'status' => 1,
      'theme' => 'bartik',
    ),
    4 => (object) array(
      'module' => 'system',
      'delta' => 'user-menu',
      'region' => 'user_dashboard_column2',
      'weight' => 0,
      'status' => 1,
      'theme' => 'bartik',
    ),
    5 => (object) array(
      'module' => 'invite',
      'delta' => 'invite',
      'region' => 'user_dashboard_column3',
      'weight' => 0,
      'status' => 1,
      'theme' => 'bartik',
    ),
    6 => (object) array(
      'module' => 'node',
      'delta' => 'syndicate',
      'region' => 'user_dashboard_footer',
      'weight' => 0,
      'status' => 1,
      'theme' => 'bartik',
    ),
  );
  $export['user_dashboard_default_blocks'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_default_timezone';
  $strongarm->value = '0';
  $export['user_default_timezone'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_email_verification';
  $strongarm->value = 1;
  $export['user_email_verification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_cancel_confirm_body';
  $strongarm->value = '[user:name],

A request to cancel your account has been made at [site:name].

You may now cancel your account on [site:url-brief] by clicking this link or copying and pasting it into your browser:

[user:cancel-url]

NOTE: The cancellation of your account is not reversible.

This link expires in one day and nothing will happen if it is not used.

--  [site:name] team';
  $export['user_mail_cancel_confirm_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_cancel_confirm_subject';
  $strongarm->value = 'Account cancellation request for [user:name] at [site:name]';
  $export['user_mail_cancel_confirm_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_password_reset_body';
  $strongarm->value = '[user:name],

A request to reset the password for your account has been made at [site:name].

You may now log in by clicking this link or copying and pasting it to your browser:

[user:one-time-login-url]

This link can only be used once to log in and will lead you to a page where you can set your password. It expires after one day and nothing will happen if it\'s not used.

--  [site:name] team';
  $export['user_mail_password_reset_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_password_reset_subject';
  $strongarm->value = 'Replacement login information for [user:name] at [site:name]';
  $export['user_mail_password_reset_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_register_admin_created_body';
  $strongarm->value = '[user:name],

A site administrator at [site:name] has created an account for you. You may now log in by clicking this link or copying and pasting it to your browser:

[user:one-time-login-url]

This link can only be used once to log in and will lead you to a page where you can set your password.

After setting your password, you will be able to log in at [site:login-url] in the future using:

username: [user:name]
password: Your password

--  [site:name] team';
  $export['user_mail_register_admin_created_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_register_admin_created_subject';
  $strongarm->value = 'An administrator created an account for you at [site:name]';
  $export['user_mail_register_admin_created_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_register_no_approval_required_body';
  $strongarm->value = '[user:name],

Thank you for registering at [site:name]. You may now log in by clicking this link or copying and pasting it to your browser:

[user:one-time-login-url]

This link can only be used once to log in and will lead you to a page where you can set your password.

After setting your password, you will be able to log in at [site:login-url] in the future using:

username: [user:name]
password: Your password

--  [site:name] team';
  $export['user_mail_register_no_approval_required_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_register_no_approval_required_subject';
  $strongarm->value = 'Account details for [user:name] at [site:name]';
  $export['user_mail_register_no_approval_required_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_register_pending_approval_body';
  $strongarm->value = '[user:name],

Thank you for registering at [site:name]. Your application for an account is currently pending approval. Once it has been approved, you will receive another e-mail containing information about how to log in, set your password, and other details.


--  [site:name] team';
  $export['user_mail_register_pending_approval_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_register_pending_approval_subject';
  $strongarm->value = 'Account details for [user:name] at [site:name] (pending admin approval)';
  $export['user_mail_register_pending_approval_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_activated_body';
  $strongarm->value = '[user:name],

Your account at [site:name] has been activated.

You may now log in by clicking this link or copying and pasting it into your browser:

[user:one-time-login-url]

This link can only be used once to log in and will lead you to a page where you can set your password.

After setting your password, you will be able to log in at [site:login-url] in the future using:

username: [user:name]
password: Your password

--  [site:name] team';
  $export['user_mail_status_activated_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_activated_notify';
  $strongarm->value = 1;
  $export['user_mail_status_activated_notify'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_activated_subject';
  $strongarm->value = 'Account details for [user:name] at [site:name] (approved)';
  $export['user_mail_status_activated_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_blocked_body';
  $strongarm->value = '[user:name],

Your account on [site:name] has been blocked.

--  [site:name] team';
  $export['user_mail_status_blocked_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_blocked_notify';
  $strongarm->value = 0;
  $export['user_mail_status_blocked_notify'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_blocked_subject';
  $strongarm->value = 'Account details for [user:name] at [site:name] (blocked)';
  $export['user_mail_status_blocked_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_canceled_body';
  $strongarm->value = '[user:name],

Your account on [site:name] has been canceled.

--  [site:name] team';
  $export['user_mail_status_canceled_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_canceled_notify';
  $strongarm->value = 1;
  $export['user_mail_status_canceled_notify'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_mail_status_canceled_subject';
  $strongarm->value = 'Account details for [user:name] at [site:name] (canceled)';
  $export['user_mail_status_canceled_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_pictures';
  $strongarm->value = 1;
  $export['user_pictures'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_default';
  $strongarm->value = '';
  $export['user_picture_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_dimensions';
  $strongarm->value = '1024x1024';
  $export['user_picture_dimensions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_file_size';
  $strongarm->value = '800';
  $export['user_picture_file_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_guidelines';
  $strongarm->value = '';
  $export['user_picture_guidelines'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_path';
  $strongarm->value = 'pictures';
  $export['user_picture_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_style';
  $strongarm->value = 'thumbnail';
  $export['user_picture_style'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_register';
  $strongarm->value = '1';
  $export['user_register'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_signatures';
  $strongarm->value = 1;
  $export['user_signatures'] = $strongarm;

  return $export;
}

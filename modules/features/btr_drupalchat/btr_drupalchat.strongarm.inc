<?php
/**
 * @file
 * btr_drupalchat.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btr_drupalchat_strongarm() {
  $export = array();

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

  return $export;
}

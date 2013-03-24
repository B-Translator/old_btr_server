#!/usr/bin/drush php-script
<?php
$variables = array (
  'additional_settings__active_tab' => 'edit-context',
  'additional_settings__active_tab_article' => 'edit-comment',
  'additional_settings__active_tab_blog' => 'edit-comment',
  'additional_settings__active_tab_book' => 'edit-comment',
  'additional_settings__active_tab_page' => 'edit-comment',
  'additional_settings__active_tab_projects' => 'edit-menu',
  'additional_settings__active_tab_simplenews' => 'edit-rpx-ui',

  'aggregator_category_selector' => 'checkboxes',
  'aggregator_summary_items' => '5',
  'aggregator_teaser_length' => '600',

  'autoloader_mode' => 'apc',
  'block_cache' => 1,
  'book_allowed_types' => 
  array (
    0 => 'book',
  ),

  'book_child_type' => 'book',
  'boost_cacheability_option' => '0',
  'boost_cacheability_pages' => 'translations/*/*',
  'boost_enabled_application/json' => false,
  'boost_enabled_application/rss' => 1,
  'boost_enabled_application/rss+xml' => 1,
  'boost_enabled_application/xml' => 1,
  'boost_enabled_text/html' => 1,
  'boost_enabled_text/javascript' => 1,
  'boost_enabled_text/xml' => 1,
  'boost_expire_cron' => 1,
  'boost_gzip_application/rss' => true,
  'boost_gzip_application/rss+xml' => true,
  'boost_gzip_application/xml' => true,
  'boost_gzip_text/html' => true,
  'boost_gzip_text/javascript' => true,
  'boost_gzip_text/xml' => true,
  'boost_ignore_flush' => 0,
  'boost_lifetime_max_application/rss' => '10800',
  'boost_lifetime_max_application/rss+xml' => '10800',
  'boost_lifetime_max_application/xml' => '10800',
  'boost_lifetime_max_text/html' => '43200',
  'boost_lifetime_max_text/javascript' => '43200',
  'boost_lifetime_max_text/xml' => '43200',
  'boost_lifetime_min_application/rss' => '3600',
  'boost_lifetime_min_application/rss+xml' => '3600',
  'boost_lifetime_min_application/xml' => '3600',
  'boost_lifetime_min_text/html' => '10800',
  'boost_lifetime_min_text/javascript' => '10800',
  'boost_lifetime_min_text/xml' => '10800',

  'cache' => 0,
  'cache_lifetime' => '1800',

  'captcha_add_captcha_description' => 0,
  'captcha_administration_mode' => 0,
  'captcha_allow_on_admin_pages' => 0,
  'captcha_default_challenge' => 'recaptcha/reCAPTCHA',
  'captcha_default_validation' => '1',
  'captcha_description_en' => 'This question is for testing whether you are a human visitor and to prevent automated spam submissions.',
  'captcha_description_sq' => 'This question is for testing whether you are a human visitor and to prevent automated spam submissions.',
  'captcha_log_wrong_responses' => 0,
  'captcha_persistence' => '0',
  'captcha_placement_map_cache' => 
  array (
    'contact_site_form' => 
    array (
      'path' => 
      array (
      ),
      'key' => 'actions',
      'weight' => 99,
    ),
    'user_register_form' => 
    array (
      'path' => 
      array (
      ),
      'key' => 'actions',
      'weight' => 99,
    ),
    'user_pass' => 
    array (
      'path' => 
      array (
      ),
      'key' => 'actions',
      'weight' => 99,
    ),
  ),

  'clean_url' => true,

  'color_bartik1_palette' => 
  array (
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
  'color_bartik_fb_palette' => 
  array (
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
  'color_bartik_palette' => 
  array (
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

  'comment_anonymous_article' => 0,
  'comment_anonymous_blog' => 0,
  'comment_anonymous_book' => 0,
  'comment_anonymous_page' => 0,
  'comment_anonymous_simplenews' => 0,
  'comment_article' => '2',
  'comment_blog' => '2',
  'comment_book' => '2',
  'comment_default_mode_article' => 1,
  'comment_default_mode_blog' => 1,
  'comment_default_mode_book' => 1,
  'comment_default_mode_page' => 1,
  'comment_default_mode_simplenews' => 1,
  'comment_default_per_page_article' => '50',
  'comment_default_per_page_blog' => '50',
  'comment_default_per_page_book' => '50',
  'comment_default_per_page_page' => '50',
  'comment_default_per_page_simplenews' => '50',
  'comment_form_location_article' => 1,
  'comment_form_location_blog' => 1,
  'comment_form_location_book' => 1,
  'comment_form_location_page' => 1,
  'comment_form_location_simplenews' => 1,
  'comment_page' => '2',
  'comment_preview_article' => '1',
  'comment_preview_blog' => '1',
  'comment_preview_book' => '1',
  'comment_preview_page' => '1',
  'comment_preview_simplenews' => '1',
  'comment_simplenews' => '1',
  'comment_subject_field_article' => 1,
  'comment_subject_field_blog' => 1,
  'comment_subject_field_book' => 1,
  'comment_subject_field_page' => 1,
  'comment_subject_field_simplenews' => 1,

  'configurable_timezones' => 1,
  'contact_default_status' => 1,
  'context_block_rebuild_needed' => true,
  'cron_safe_threshold' => 0,
  'default_nodes_main' => '10',

  'disqus_developer' => 0,
  'disqus_inherit_login' => 1,
  'disqus_localization' => 1,
  'disqus_location' => 'content_area',
  'disqus_nodetypes' => 
  array (
    'blog' => 'blog',
    'article' => 'article',
    'book' => 'book',
    'mass_contact' => 'mass_contact',
    'page' => 'page',
    'simplenews' => 'simplenews',
  ),
  'disqus_sso' => 1,
  'disqus_weight' => '100',

  'drupal_http_request_fails' => false,

  'drupalchat_allow_anon_links' => '1',
  'drupalchat_anon_name_set' => 'usa',
  'drupalchat_anon_prefix' => 'Guest',
  'drupalchat_chat_list_header' => 'Chat',
  'drupalchat_chat_topbar_color' => '#222222',
  'drupalchat_chat_topbar_text_color' => '#FFFFFF',
  'drupalchat_enable_chatroom' => '1',
  'drupalchat_enable_smiley' => '1',
  'drupalchat_external_api_key' => '',
  'drupalchat_font_color' => '#222222',
  'drupalchat_load_chat_async' => '1',
  'drupalchat_log_messages' => '1',
  'drupalchat_notification_sound' => '1',
  'drupalchat_path_pages' => '',
  'drupalchat_path_visibility' => '0',
  'drupalchat_polling_method' => '0',
  'drupalchat_public_chatroom_header' => 'Public Chatroom',
  'drupalchat_refresh_rate' => '10',
  'drupalchat_rel' => '0',
  'drupalchat_send_rate' => '3',
  'drupalchat_show_admin_list' => '2',
  'drupalchat_stop_links' => '1',
  'drupalchat_theme' => 'light',
  'drupalchat_ur_name' => '',
  'drupalchat_use_stop_word_list' => '1',
  'drupalchat_user_latency' => '10',
  'drupalchat_user_picture' => '1',

  'email__active_tab' => 'edit-email-admin-created',
  'empty_timezone_message' => 0,
  'enable_revisions_page_article' => 1,
  'enable_revisions_page_blog' => 1,
  'enable_revisions_page_book' => 1,
  'enable_revisions_page_page' => 1,

  'fb_button_text_login' => 'Use Facebook Login',
  'fb_button_text_login_block' => 'Use Facebook Login',
  'fb_button_text_register' => 'Use Facebook Account',
  'fb_canvas_process_absolute_links' => 0,
  'fb_canvas_process_iframe' => 1,
  'fb_connect_theme_username_1' => 1,
  'fb_connect_theme_username_2' => 1,
  'fb_connect_theme_userpic_1' => 1,
  'fb_connect_theme_userpic_2' => 1,
  'fb_format_username' => 'when_not_theming',
  'fb_js_get_login_status' => 0,
  'fb_js_oauth' => true,
  'fb_js_session_token' => 0,
  'fb_js_test_login_status' => false,
  'fb_language_en' => 'en_US',
  'fb_language_override' => 'override',
  'fb_secure_urls' => '1',
  'fb_tab_process_absolute_links' => 1,
  'fb_tab_process_iframe' => 1,
  'fb_tab_process_to_canvas' => 1,
  'fb_use_cookie' => 1,
  'fb_use_session' => 0,
  'fb_user_alter_contact' => 1,
  'fb_user_alter_login' => 1,
  'fb_user_alter_login_block' => 1,
  'fb_user_alter_register' => 1,
  'fb_user_app_track_every_page' => 0,
  'fb_user_app_track_pages' => 1,
  'fb_user_app_track_users' => 1,
  'fb_user_app_users_that_grant_offline' => 0,
  'fb_user_check_session' => 0,
  'fb_user_username_style' => '1',

  'filter_fallback_format' => 'plain_text',

  'googleanalytics_cache' => 1,
  'googleanalytics_domain_mode' => '0',
  'googleanalytics_js_scope' => 'header',
  'googleanalytics_pages' => 'admin
admin/*
batch
node/add*
node/*/*
user/*/*',
  'googleanalytics_privacy_donottrack' => 1,
  'googleanalytics_roles' => 
  array (
    1 => 0,
    2 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    7 => 0,
  ),
  'googleanalytics_site_search' => 0,
  'googleanalytics_trackadsense' => 0,
  'googleanalytics_trackdoubleclick' => 0,
  'googleanalytics_tracker_anonymizeip' => 0,
  'googleanalytics_trackfiles' => 1,
  'googleanalytics_trackmailto' => 1,
  'googleanalytics_trackmessages' => 
  array (
    'status' => 'status',
    'warning' => 'warning',
    'error' => 'error',
  ),
  'googleanalytics_trackoutbound' => 1,
  'googleanalytics_visibility_pages' => '0',
  'googleanalytics_visibility_roles' => '0',

  'honeypot_element_name' => 'email',
  'honeypot_form_article_node_form' => 0,
  'honeypot_form_blog_node_form' => 0,
  'honeypot_form_book_node_form' => 0,
  'honeypot_form_comment_node_article_form' => 0,
  'honeypot_form_comment_node_blog_form' => 0,
  'honeypot_form_comment_node_book_form' => 0,
  'honeypot_form_comment_node_mass_contact_form' => 0,
  'honeypot_form_comment_node_page_form' => 0,
  'honeypot_form_comment_node_simplenews_form' => 0,
  'honeypot_form_contact_personal_form' => 1,
  'honeypot_form_contact_site_form' => 1,
  'honeypot_form_mass_contact_node_form' => 0,
  'honeypot_form_page_node_form' => 0,
  'honeypot_form_simplenews_node_form' => 0,
  'honeypot_form_user_pass' => 1,
  'honeypot_form_user_register_form' => 1,
  'honeypot_log' => 0,
  'honeypot_protect_all_forms' => 0,
  'honeypot_time_limit' => '0',

  'image_toolkit' => 'gd',

  'invite_expiry' => '30',
  'invite_manual_from' => '',
  'invite_manual_reply_to' => '',
  'invite_maxnum_1' => '1000',
  'invite_maxnum_2' => '50',
  'invite_maxnum_3' => '50',
  'invite_page_title' => 'Invite a friend',
  'invite_profile_inviter' => 1,
  'invite_registration_path' => 'user/register',
  'invite_require_approval' => 0,
  'invite_subject_editable' => 1,
  'invite_use_users_email' => '1',
  'invite_use_users_email_replyto' => '1',

  'l10n_client_server' => 'http://localize.drupal.org',
  'l10n_client_use_server' => 1,

  'l10n_feedback_topcontrib_period' => 'week',
  'l10n_feedback_topcontrib_size' => '5',
  'l10n_feedback_voting_mode' => 'single',

  'l10n_update_check_disabled' => 0,
  'l10n_update_check_frequency' => '7',
  'l10n_update_check_mode' => '3',
  'l10n_update_download_store' => 'sites/all/translations',
  'l10n_update_import_mode' => '0',

  'maintenance_mode' => 0,

  'mass_contact_attachment_location' => 'mass_contact_attachments',
  'mass_contact_bcc_d' => 1,
  'mass_contact_category_override' => 0,
  'mass_contact_hourly_threshold' => '3',
  'mass_contact_nodecc_d' => 0,
  'mass_contact_number_of_attachments' => '3',
  'mass_contact_optout_d' => '0',
  'mass_contact_recipient_limit' => '100',

  'mimemail_engine' => 'phpmailer',
  'mimemail_format' => 'full_html',
  'mimemail_incoming' => 0,
  'mimemail_linkonly' => 1,
  'mimemail_preserve_class' => 0,
  'mimemail_simple_address' => 1,
  'mimemail_sitestyle' => 1,
  'mimemail_textonly' => 0,

  'page_cache_maximum_age' => '3600',
  'page_compression' => 1,
  'preprocess_css' => 1,
  'preprocess_js' => 1,

  'recaptcha_ajax_api' => 1,
  'recaptcha_nocookies' => 1,
  'recaptcha_secure_connection' => 1,
  'recaptcha_tabindex' => '',
  'recaptcha_theme' => 'red',

  'reroute_email_enable' => 0,
  'reroute_email_enable_message' => 0,

  'rpx_accounts_string' => 'Linked accounts',
  'rpx_attach_login_form' => 1,
  'rpx_attach_share_link_to_comments_simplenews' => 0,
  'rpx_attach_share_link_to_nodecont_simplenews' => 0,
  'rpx_attach_share_link_to_nodecont_weight_simplenews' => '40',
  'rpx_attach_share_link_to_nodelink_simplenews' => 0,
  'rpx_attach_share_link_to_teasers_simplenews' => 0,
  'rpx_bypass_email_verification' => 0,
  'rpx_comment_popup_social_at_once_simplenews' => 0,
  'rpx_enabled_providers' => 
  array (
    0 => 'google',
    1 => 'facebook',
    2 => 'twitter',
    3 => 'linkedin',
    4 => 'paypal',
  ),
  'rpx_extended_authinfo' => 0,
  'rpx_force_registration_form' => 1,
  'rpx_import_profile_photo' => 1,
  'rpx_javascript_global' => 1,
  'rpx_login_icons_size' => 'medium',
  'rpx_login_links_weight' => '-150',
  'rpx_mapping_api' => 0,
  'rpx_openid_override' => 1,
  'rpx_realm_scheme' => 'https',
  'rpx_signin_string' => 'Sign in with one of these:',
  'rpx_social_enabled' => 1,
  'rpx_social_pub' => '',

  'settings__active_tab' => 'edit-visibility',

  'sharethis_button_option' => 'stbc_button',
  'sharethis_comments' => 0,
  'sharethis_late_load' => 1,
  'sharethis_location' => 'content',
  'sharethis_node_option' => 'blog,article,book,page,simplenews,0',
  'sharethis_option_extras' => 
  array (
    'Google Plus One:plusone' => 'Google Plus One:plusone',
    'Facebook Like:fblike' => 'Facebook Like:fblike',
  ),
  'sharethis_service_option' => '"Google +:googleplus","Facebook:facebook","Tweet:twitter","LinkedIn:linkedin","Email:email","ShareThis:sharethis"',
  'sharethis_teaser_option' => 1,
  'sharethis_weight' => '50',
  'sharethis_widget_option' => 'st_multi',

  'simplenews_content_type_simplenews' => 1,
  'simplenews_debug' => 1,
  'simplenews_format' => 'html',
  'simplenews_priority' => '0',
  'simplenews_receipt' => 0,
  'simplenews_send' => '0',
  'simplenews_source_cache' => 'SimplenewsSourceCacheBuild',
  'simplenews_spool_expire' => '0',
  'simplenews_sync_account' => 1,
  'simplenews_test_address_override' => 1,
  'simplenews_throttle' => '50',
  'simplenews_use_combined' => 'multiple',
  'simplenews_use_cron' => 1,
  'simplenews_vid' => '2',

  'smtp_allowhtml' => 1,
  'smtp_always_replyto' => 1,
  'smtp_debug' => '0',
  'smtp_debugging' => 0,
  'smtp_hide_password' => 1,
  'smtp_host' => 'smtp.googlemail.com',
  'smtp_hostbackup' => '',
  'smtp_keepalive' => 1,
  'smtp_on' => 1,
  'smtp_port' => '465',
  'smtp_protocol' => 'ssl',

  'theme_bartik1_settings' => 
  array (
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
    'palette' => 
    array (
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
    'info' => 
    array (
      'fields' => 
      array (
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
      'schemes' => 
      array (
        'default' => 
        array (
          'title' => 'Blue Lagoon (default)',
          'colors' => 
          array (
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
        'firehouse' => 
        array (
          'title' => 'Firehouse',
          'colors' => 
          array (
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
        'ice' => 
        array (
          'title' => 'Ice',
          'colors' => 
          array (
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
        'plum' => 
        array (
          'title' => 'Plum',
          'colors' => 
          array (
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
        'slate' => 
        array (
          'title' => 'Slate',
          'colors' => 
          array (
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
        '' => 
        array (
          'title' => 'Custom',
          'colors' => 
          array (
          ),
        ),
      ),
      'css' => 
      array (
        0 => 'css/colors.css',
      ),
      'copy' => 
      array (
        0 => 'logo.png',
      ),
      'gradients' => 
      array (
        0 => 
        array (
          'dimension' => 
          array (
            0 => 0,
            1 => 0,
            2 => 0,
            3 => 0,
          ),
          'direction' => 'vertical',
          'colors' => 
          array (
            0 => 'top',
            1 => 'bottom',
          ),
        ),
      ),
      'fill' => 
      array (
      ),
      'slices' => 
      array (
      ),
      'blend_target' => '#ffffff',
      'preview_css' => 'color/preview.css',
      'preview_js' => 'color/preview.js',
      'preview_html' => 'color/preview.html',
      'base_image' => 'color/base.png',
    ),
  ),
  'theme_bartik_fb_settings' => 
  array (
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
    'palette' => 
    array (
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
    'info' => 
    array (
      'fields' => 
      array (
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
      'schemes' => 
      array (
        'default' => 
        array (
          'title' => 'Blue Lagoon (default)',
          'colors' => 
          array (
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
        'facebook' => 
        array (
          'title' => 'Facebook',
          'colors' => 
          array (
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
        'firehouse' => 
        array (
          'title' => 'Firehouse',
          'colors' => 
          array (
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
        'ice' => 
        array (
          'title' => 'Ice',
          'colors' => 
          array (
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
        'plum' => 
        array (
          'title' => 'Plum',
          'colors' => 
          array (
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
        'slate' => 
        array (
          'title' => 'Slate',
          'colors' => 
          array (
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
        '' => 
        array (
          'title' => 'Custom',
          'colors' => 
          array (
          ),
        ),
      ),
      'css' => 
      array (
        0 => 'css/colors.css',
      ),
      'copy' => 
      array (
        0 => 'logo.png',
      ),
      'gradients' => 
      array (
        0 => 
        array (
          'dimension' => 
          array (
            0 => 0,
            1 => 0,
            2 => 0,
            3 => 0,
          ),
          'direction' => 'vertical',
          'colors' => 
          array (
            0 => 'top',
            1 => 'bottom',
          ),
        ),
      ),
      'fill' => 
      array (
      ),
      'slices' => 
      array (
      ),
      'blend_target' => '#ffffff',
      'preview_css' => 'color/preview.css',
      'preview_js' => 'color/preview.js',
      'preview_html' => 'color/preview.html',
      'base_image' => 'color/base.png',
    ),
  ),

  'theme_default' => 'bartik1',

  'tracking__active_tab' => 'edit-privacy',
  'update_check_disabled' => 0,
  'update_check_frequency' => '7',
  'update_notification_threshold' => 'all',

  'user_admin_role' => '3',
  'user_cancel_method' => 'user_cancel_block',
  'user_dashboard_available_blocks' => 
  array (
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
  ),
  'user_dashboard_default_blocks' => 
  array (
    0 => 
    stdClass::__set_state(array(
       'module' => 'user',
       'delta' => 'new',
       'region' => 'user_dashboard_main',
       'weight' => 0,
       'status' => 1,
       'theme' => 'bartik',
    )),
    1 => 
    stdClass::__set_state(array(
       'module' => 'user',
       'delta' => 'online',
       'region' => 'user_dashboard_sidebar',
       'weight' => 0,
       'status' => 1,
       'theme' => 'bartik',
    )),
    2 => 
    stdClass::__set_state(array(
       'module' => 'disqus',
       'delta' => NULL,
       'region' => 'user_dashboard_sidebar',
       'weight' => 1,
       'status' => 1,
       'theme' => 'bartik',
    )),
    3 => 
    stdClass::__set_state(array(
       'module' => 'node',
       'delta' => 'recent',
       'region' => 'user_dashboard_column1',
       'weight' => 0,
       'status' => 1,
       'theme' => 'bartik',
    )),
    4 => 
    stdClass::__set_state(array(
       'module' => 'system',
       'delta' => 'user-menu',
       'region' => 'user_dashboard_column2',
       'weight' => 0,
       'status' => 1,
       'theme' => 'bartik',
    )),
    5 => 
    stdClass::__set_state(array(
       'module' => 'invite',
       'delta' => 'invite',
       'region' => 'user_dashboard_column3',
       'weight' => 0,
       'status' => 1,
       'theme' => 'bartik',
    )),
    6 => 
    stdClass::__set_state(array(
       'module' => 'node',
       'delta' => 'syndicate',
       'region' => 'user_dashboard_footer',
       'weight' => 0,
       'status' => 1,
       'theme' => 'bartik',
    )),
  ),
  'user_default_timezone' => '0',
  'user_email_verification' => 1,
  'user_mail_status_activated_notify' => 1,
  'user_mail_status_blocked_notify' => 0,
  'user_mail_status_canceled_notify' => 1,
  'user_picture_default' => '',
  'user_picture_dimensions' => '1024x1024',
  'user_picture_file_size' => '800',
  'user_picture_path' => 'pictures',
  'user_picture_style' => 'thumbnail',
  'user_pictures' => 1,
  'user_register' => '1',
  'user_signatures' => 1,
);

foreach ($variables as $var_name => $var_value) {
  variable_set($var_name, $var_value);
}


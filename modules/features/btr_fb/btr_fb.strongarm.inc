<?php
/**
 * @file
 * btr_fb.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btr_fb_strongarm() {
  $export = array();

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
  $strongarm->name = 'fb_cache_username';
  $strongarm->value = 'on';
  $export['fb_cache_username'] = $strongarm;

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
  $strongarm->value = 1;
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
  $strongarm->value = 1;
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
  $strongarm->name = 'fb_language_override';
  $strongarm->value = 'override';
  $export['fb_language_override'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_secure_urls';
  $strongarm->value = '1';
  $export['fb_secure_urls'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'fb_tab_process_absolute_links';
  $strongarm->value = 0;
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

  return $export;
}

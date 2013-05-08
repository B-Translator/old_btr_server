<?php
/**
 * @file
 * btranslator_blocks.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function btranslator_blocks_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['aggregator-feed-1'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'feed-1',
    'module' => 'aggregator',
    'node_types' => array(),
    'pages' => '<front>
contact',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-17',
      ),
      'bartik' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-18',
      ),
      'bartik1' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '-18',
      ),
      'bartik_fb' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik_fb',
        'weight' => '-19',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-17',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['block-titleslogan'] = array(
    'cache' => -1,
    'custom' => '0',
    'machine_name' => 'titleslogan',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '<front>
contact
about',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'header',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['blog-recent'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'recent',
    'module' => 'blog',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['book-navigation'] = array(
    'cache' => 5,
    'custom' => '0',
    'delta' => 'navigation',
    'module' => 'book',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['boost-status'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'status',
    'module' => 'boost',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['comment-recent'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'recent',
    'module' => 'comment',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['context_ui-devel'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'devel',
    'module' => 'context_ui',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['context_ui-editor'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'editor',
    'module' => 'context_ui',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['devel-execute_php'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'execute_php',
    'module' => 'devel',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['devel-switch_user'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'switch_user',
    'module' => 'devel',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['disqus-disqus_combination_widget'] = array(
    'cache' => 8,
    'custom' => '0',
    'delta' => 'disqus_combination_widget',
    'module' => 'disqus',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '-15',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '-15',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '-15',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-15',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '-15',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '-15',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['disqus-disqus_comments'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'disqus_comments',
    'module' => 'disqus',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-22',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['disqus-disqus_popular_threads'] = array(
    'cache' => 8,
    'custom' => '0',
    'delta' => 'disqus_popular_threads',
    'module' => 'disqus',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-16',
      ),
      'bartik' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-16',
      ),
      'bartik1' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '-16',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-16',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-16',
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['disqus-disqus_recent_comments'] = array(
    'cache' => 8,
    'custom' => '0',
    'delta' => 'disqus_recent_comments',
    'module' => 'disqus',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-17',
      ),
      'bartik' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-17',
      ),
      'bartik1' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '-17',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-17',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-17',
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['disqus-disqus_top_commenters'] = array(
    'cache' => 8,
    'custom' => '0',
    'delta' => 'disqus_top_commenters',
    'module' => 'disqus',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-15',
      ),
      'bartik' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-15',
      ),
      'bartik1' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '-15',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-15',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-15',
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['fb_connect-login_l10nsq'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'login_l10nsq',
    'module' => 'fb_connect',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['homebox-custom'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'custom',
    'module' => 'homebox',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['invite-invite'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'invite',
    'module' => 'invite',
    'node_types' => array(),
    'pages' => '<front>
contact',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-20',
      ),
      'bartik' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-21',
      ),
      'bartik1' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '-21',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-20',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-20',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['invite_stats-top_inviters'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'top_inviters',
    'module' => 'invite_stats',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['l10n_feedback-latest'] = array(
    'cache' => -2,
    'custom' => '0',
    'delta' => 'latest',
    'module' => 'l10n_feedback',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['l10n_feedback-statistics'] = array(
    'cache' => -2,
    'custom' => '0',
    'delta' => 'statistics',
    'module' => 'l10n_feedback',
    'node_types' => array(),
    'pages' => '<front>
contact',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-19',
      ),
      'bartik' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-20',
      ),
      'bartik1' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '-20',
      ),
      'bartik_fb' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik_fb',
        'weight' => '-22',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-19',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['l10n_feedback-topcontrib'] = array(
    'cache' => -2,
    'custom' => '0',
    'delta' => 'topcontrib',
    'module' => 'l10n_feedback',
    'node_types' => array(),
    'pages' => '<front>
contact',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-18',
      ),
      'bartik' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-19',
      ),
      'bartik1' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '-19',
      ),
      'bartik_fb' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik_fb',
        'weight' => '-21',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-18',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['locale-language'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'language',
    'module' => 'locale',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['menu-devel'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'devel',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'footer',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => 'footer',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => 'footer',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'footer',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['menu-features'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'features',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['menu-menu-left-menu'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'menu-left-menu',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-23',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => 'Navigation',
    'visibility' => '1',
  );

  $export['node-recent'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'recent',
    'module' => 'node',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '10',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['node-syndicate'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'syndicate',
    'module' => 'node',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['search-form'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'form',
    'module' => 'search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '-20',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '-20',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '-20',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-20',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '-20',
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '-18',
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '-10',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['sharethis-sharethis_block'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'sharethis_block',
    'module' => 'sharethis',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['simplenews-0'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => '0',
    'module' => 'simplenews',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['simplenews-1'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => '1',
    'module' => 'simplenews',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['simplenews-2'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => '2',
    'module' => 'simplenews',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['system-help'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'help',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'help',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => 'help',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => 'help',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => 'help',
        'status' => '1',
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'help',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => 'help',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'help',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['system-main'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'main',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-23',
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['system-main-menu'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'main-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '-22',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '<none>',
    'visibility' => '0',
  );

  $export['system-management'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'management',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['system-navigation'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'navigation',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '-17',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '-17',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '-17',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-17',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '-17',
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '-17',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['system-powered-by'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'powered-by',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '10',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '10',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '10',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '10',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '10',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '10',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '10',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['system-user-menu'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'user-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-21',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '<none>',
    'visibility' => '1',
  );

  $export['user-login'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'login',
    'module' => 'user',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'abessive',
        'weight' => '-19',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '-19',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '-19',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '-22',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '-19',
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'rubik',
        'weight' => '-16',
      ),
      'seven' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '10',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['user-new'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'new',
    'module' => 'user',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['user-online'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'online',
    'module' => 'user',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views-archive-block'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'archive-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views-backlinks-block'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'backlinks-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views-comments_recent-block'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'comments_recent-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'abessive' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'abessive',
        'weight' => '0',
      ),
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bartik1' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik1',
        'weight' => '0',
      ),
      'bartik_fb' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik_fb',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  return $export;
}

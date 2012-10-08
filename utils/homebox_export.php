<?php
$homebox = new stdClass;
$homebox->name = 'dashboard';
$homebox->settings = array (
  'regions' => 4,
  'cache' => 1,
  'color' => 1,
  'colors' => 
  array (
    0 => '#8888aa',
    1 => '#E4F0F8',
    2 => '#ffff00',
    3 => '#ff3300',
    4 => '#66cc66',
    5 => '#66aaff',
  ),
  'blocks' => 
  array (
    'disqus_disqus_combination_widget' => 
    array (
      'module' => 'disqus',
      'delta' => 'disqus_combination_widget',
      'region' => 2,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -18,
    ),
    'simplenews_0' => 
    array (
      'module' => 'simplenews',
      'delta' => '0',
      'region' => 3,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -18,
    ),
    'user_online' => 
    array (
      'module' => 'user',
      'delta' => 'online',
      'region' => 1,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -18,
    ),
    'locale_language' => 
    array (
      'module' => 'locale',
      'delta' => 'language',
      'region' => 3,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -17,
    ),
    'user_new' => 
    array (
      'module' => 'user',
      'delta' => 'new',
      'region' => 1,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -17,
    ),
    'invite_invite' => 
    array (
      'module' => 'invite',
      'delta' => 'invite',
      'region' => 1,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -16,
    ),
    'node_recent' => 
    array (
      'module' => 'node',
      'delta' => 'recent',
      'region' => 2,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -16,
    ),
    'system_user-menu' => 
    array (
      'module' => 'system',
      'delta' => 'user-menu',
      'region' => 3,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -16,
    ),
    'invite_stats_top_inviters' => 
    array (
      'module' => 'invite_stats',
      'delta' => 'top_inviters',
      'region' => 1,
      'movable' => 1,
      'status' => 1,
      'open' => 1,
      'closable' => 1,
      'title' => '',
      'weight' => -15,
    ),
  ),
  'widths' => 
  array (
    1 => 25,
    2 => 50,
    3 => 25,
    4 => 100,
  ),
  'title' => 'Check the latest activity on the site',
  'path' => 'dashboard',
  'menu' => 1,
  'enabled' => 1,
  'auto_save' => 1,
  'full' => 1,
  'roles' => 
  array (
    0 => 'authenticated user',
  ),
);
?>

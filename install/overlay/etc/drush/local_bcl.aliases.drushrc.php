<?php
/*
  For more info see:
    drush help site-alias
    drush topic docs-aliases

  See also:
    drush help rsync
    drush help sql-sync
 */

$aliases['bcl'] = array (
  'root' => '/var/www/bcl',
  'uri' => 'http://example.org',
  'path-aliases' => array (
    '%profile' => 'profiles/btr_client',
    '%downloads' => '/var/www/downloads',
  ),
);

// $aliases['bcl_dev'] = array (
//   'parent' => '@bcl',
//   'root' => '/var/www/bcl_dev',
//   'uri' => 'http://dev.example.org',
// );

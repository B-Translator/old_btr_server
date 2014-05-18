<?php
/*
  For more info see:
    drush help site-alias
    drush topic docs-aliases

  See also:
    drush help rsync
    drush help sql-sync
 */

$aliases['btr'] = array (
  'root' => '/var/www/btr',
  'uri' => 'http://btr.example.org',
  'path-aliases' => array (
    '%profile' => 'profiles/btr_server',
    '%data' => '/var/www/data',
    '%po_files' => '/var/www/PO_files',
    '%exports' => '/var/www/exports',
    '%downloads' => '/var/www/downloads',
  ),
);

// $aliases['btr_dev'] = array (
//   'parent' => '@btr',
//   'root' => '/var/www/btr_dev',
//   'uri' => 'http://dev.btr.example.org',
// );

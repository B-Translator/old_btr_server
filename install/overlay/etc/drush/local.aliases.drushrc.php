<?php
/*
  For more info see:
    drush help site-alias
    drush topic docs-aliases

  See also:
    drush help rsync
    drush help sql-sync
 */

$aliases['main'] = array (
  'root' => '/var/www/btr',
  'uri' => 'http://l10n.org.xx',
  'path-aliases' => array (
    '%profile' => 'profiles/btranslator',
    '%data' => '/var/www/data',
    '%po_files' => '/var/www/PO_files',
    '%exports' => '/var/www/exports',
    '%downloads' => '/var/www/downloads',
  ),
);

$aliases['dev'] = array (
  'parent' => '@main',
  'root' => '/var/www/btr_dev',
  'uri' => 'http://dev.l10n.org.xx',
);

<?php

/* uncomment and modify properly

$aliases['live'] = array (
  'root' => '/var/www/btranslator',
  'uri' => 'http://l10n.org.xx',

  'remote-host' => 'l10n.org.xx',
  'remote-user' => 'root',
  'ssh-options' => '-p 2201 -i /root/.ssh/id_rsa',

  'path-aliases' => array (
    '%profile' => 'profiles/btranslator',
    '%data' => '/var/www/btranslator_data',
    '%pofiles' => '/var/www/PO_files',
    '%exports' => '/var/www/exports',
    '%downloads' => '/var/www/downloads',
  ),

  'command-specific' => array (
    'sql-sync' => array (
      'simulate' => '1',
    ),
    'rsync' => array (
      'simulate' => '1',
    ),
  ),
);

$aliases['test'] = array (
  'parent' => '@live',
  'root' => '/var/www/btranslator_test',
  'uri' => 'http://test.l10n.org.xx',

  'command-specific' => array (
    'sql-sync' => array (
      'simulate' => '0',
    ),
    'rsync' => array (
      'simulate' => '0',
    ),
  ),
);

*/
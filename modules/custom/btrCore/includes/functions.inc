<?php
/**
 * @file
 * Functions called from the front-end (UI).
 */

module_load_include('inc', 'btrCore', 'lib/query');
module_load_include('php', 'btrCore', 'lib/btr');

include_once dirname(__FILE__) . '/get_strings.inc';
include_once dirname(__FILE__) . '/hook_user.inc';
include_once dirname(__FILE__) . '/get_sguid.inc';
include_once dirname(__FILE__) . '/search.inc';
include_once dirname(__FILE__) . '/misc.inc';
include_once dirname(__FILE__) . '/languages.inc';

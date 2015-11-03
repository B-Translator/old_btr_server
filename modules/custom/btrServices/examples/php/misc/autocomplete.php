<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// Autocomplete strings.
http_request('https://btranslator.org/auto/string/vocabulary/ICT_sq/a');

// Autocomplete strings with project and origin wildcards.
http_request('https://btranslator.org/auto/string/*/*/b');

// Autocomplete projects.
http_request('https://btranslator.org/auto/project/kd');

// Autocomplete origins of projects.
http_request('https://btranslator.org/auto/origin/G');

// Autocomplete users.
http_request('https://btranslator.org/auto/user/sq/d');

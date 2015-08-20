<?php
$path = dirname(dirname(__FILE__));
include_once($path . '/config.php');
include_once($path . '/http_request.php');

// POST api/translations/search
$url = $base_url . '/api/translations/search';
$options = array(
  'method' => 'POST',
  'data' => array(
    'lng' => 'sq',
    'words' => 'file',
    'page' => 2,
  ),
  'headers' => array(
    'Content-type' => 'application/x-www-form-urlencoded',
  ),
);
$result = http_request($url, $options);


/**
 * Search strings and translations using various filters.
 *
 * @param $params
 *   Associative array of the POST data, which contains
 *   the filter parameters. These parameters can be:
 *   - lng
 *       The language of translations.
 *   - limit
 *       The number of results to be returned (min: 5, max: 50).
 *   - words
 *       Words to be searched for.
 *   - mode
 *       Search mode. Can be one of:
 *       - natural-strings       Natural search on strings (default).
 *       - natural-translations  Natural search on translations.
 *       - boolean-strings       Boolean search on strings.
 *       - boolean-translations  Boolean search on translations.
 *   - page
 *       Page of results to be displayed.
 *   - project
 *       Limit search only to this project
 *   - origin
 *       Limit search only to the projects of this origin.
 *   - only_mine (boolean)
 *       Limit search only to the strings touched (translated or voted)
 *       by the current user.
 *   - translated_by
 *       Limit search by the author of translations
 *       (can be used only by admins).
 *   - voted_by
 *       Limit search by a voter (can be used only by admins).
 *   - date_filter
 *       Which date to filter (used only by admins). Can be one of:
 *       - strings       Filter Strings By Date
 *       - translations  Filter Translations By Date (default)
 *       - votes         Filter Votes By Date
 *   - from_date
 *   - to_date
 *
 * @return
 *   Array containing search results, along with the filters
 *   and the pager info. Each result is a nested structure
 *   containing the string, its translations, votes, etc.
 */

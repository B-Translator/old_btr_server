<?php
/**
 * @file
 * Callback functions for btr_services.
 */

/**
 * Callback function for getting statistics about top contributors.
 * @param $params
 *     Parameters of the report, comming from the POST request.
 *     It contains these fields (variables):
 *       - lng: language of translations
 *       - period: period of report (last day|week|month|year)
 *       - size: number of results (top contributers), between 5 and 20
 * @return
 *     JSON array of users, where each user is an object
 *     with these attributes:
 *         uid, name, umail, score, translations, votes
 * @example
 *     curl -k -i -H "Content-type: application/json"  \
 *          -X POST https://dev.l10n.org.xx/btr/report/topcontrib.json	\
 *          -d '{"lng": "sq", "period": "week", "size": 10}'
 */
function _report_topcontrib($params) {
  // get parameters and validate them
  $lng = $params['lng'];
  $arr_langs = array_keys(btr_get_languages());
  if (!in_array($lng, $arr_langs)) {
    return services_error('Language missing or not supported.', 406);
  }
  $period = $params['period'];
  if (!in_array($period, array('day', 'week', 'month', 'year'))) {
    return services_error('Period missing or not supported.', 406);
  }
  $size = (int) $params['size'];
  if ($size < 5)  $size = 5;
  if ($size > 20) $size = 20;

  return btr_stat_topcontrib($lng, $period, $size);
  //return drupal_json_encode($topcontrib);
}
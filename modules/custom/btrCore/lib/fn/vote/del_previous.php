<?php
namespace BTranslator;
use \btr;

/**
 * Clean any previous vote by this user for this translation.
 *
 * This depends on the voting mode option (set by the admin).
 * If the voting mode is 'single', then the user can select
 * only one translation for a given string (at most one vote
 * per string).
 * If the voting mode is 'multiple', then the user can approve
 * several translations for a string (at most one vote per
 * translation).
 *
 * @param $tguid
 *   ID of the translation.
 *
 * @param $umail
 *   The mail of the user.
 *
 * @param $sguid
 *   ID of the source string.
 *
 * @param $lng
 *   Language code of the translation.
 *
 * @return
 *   Number of previous votes that were deleted.
 *   (Normally should be 0, but can also be 1. If it is >1,
 *   something must be wrong.)
 */
function _vote_del_previous($tguid, $umail, $sguid, $lng) {
  // Get the voting mode.
  $voting_mode = variable_get('btr_voting_mode', 'single');

  $arr_tguid = array();
  if ($voting_mode == 'multiple') {
    $arr_tguid = array($tguid);
  }
  else { // ($voting_mode == 'single')
    // Get the other sibling translations (translations of the same
    // string and the same language) which the user has voted.
    $arr_tguid = btr::db_query(
      'SELECT DISTINCT t.tguid
       FROM {btr_translations} t
       LEFT JOIN {btr_votes} v ON (v.tguid = t.tguid)
       WHERE t.sguid = :sguid
         AND t.lng = :lng
         AND v.umail = :umail
         AND v.ulng = :ulng',
       array(
        ':sguid' => $sguid,
        ':lng' => $lng,
        ':umail' => $umail,
        ':ulng' => $lng,
      ))
      ->fetchCol();
  }

  if (empty($arr_tguid))  return 0;

  // Insert to the trash table the votes that will be removed.
  $query = btr::db_select('btr_votes', 'v')
    ->fields('v', array('vid', 'tguid', 'umail', 'ulng', 'time', 'active'))
    ->condition('umail', $umail)
    ->condition('ulng', $lng)
    ->condition('tguid', $arr_tguid, 'IN');
  $query->addExpression('NOW()', 'd_time');
  btr::db_insert('btr_votes_trash')->from($query)->execute();

  // Remove any votes by the user for each translation in $arr_tguid.
  $num_deleted = btr::db_delete('btr_votes')
    ->condition('umail', $umail)
    ->condition('ulng', $lng)
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  // Decrement the vote count for each translation in $arr_tguid.
  $num_updated = btr::db_update('btr_translations')
    ->expression('count', 'count - 1')
    ->condition('tguid', $arr_tguid, 'IN')
    ->execute();

  return $num_deleted;
}

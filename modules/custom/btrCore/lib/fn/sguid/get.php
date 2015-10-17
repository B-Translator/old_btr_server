<?php
/**
 * @file
 * Get a random sguid.
 */

namespace BTranslator;
use \btr;

/**
 * Returns a sguid for targets: random|translated|untranslated.
 *
 * @param $lng
 *   Useful for 'translated' and 'untranslated' targets.
 *   If not provided, a default language will be used.
 *
 * @param $projects
 *   Array of scope projects, where each project is in the form
 *   'origin/project' or 'origin'. If provided, will be used
 *   to restrict the pool of selection (in addition to the preferred
 *   projects of the user).
 *
 * @return
 *   The sguid of a randomly selected string, according to the
 *   given parameters and to the preferencies of the user.
 */
function sguid_get($target, $lng =NULL, $projects =NULL) {

  switch ($target) {
    default:
    case 'random':
      $sguid = btr::sguid_get_random($uid=NULL, $projects);
      break;
    case 'translated':
      $sguid = btr::sguid_get_translated($lng, $uid=NULL, $projects);
      break;
    case 'untranslated':
      $sguid = btr::sguid_get_untranslated($lng, $uid=NULL, $projects);
      break;
  }

  return $sguid;
}

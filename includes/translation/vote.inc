<?php
/**
 * @file
 *   Functions specific to the menu path: translation/vote .
 */

/**
 * Menu callback: translation/vote
 * Vote the best translation for a string, or suggest a better translation.
 */
function l10n_suggestions_vote($lng =NULL, $sguid =NULL) {
  $page = "lng='$lng' sguid='$sguid'";
  return $page;
}


?>
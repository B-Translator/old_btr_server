<?php
/**
 * @file
 * Menu callbacks for translations/vocabulary.
 */


/**
 * Callback function for the menu translations/vocabulary/export.
 *
 * Return the list of terms in a vocabulary and all the suggested translations.
 *
 * @param $vocabulary
 *   The name of the vocabulary project (which ends in '_lng').
 *
 * @param $format
 *   The output format: json | txt1 | txt2 | org
 *   Default is 'json'
 *
 * Examples:
 *   curl -k https://dev.l10n.org.al/translations/vocabulary/export/ICT_sq
 *   curl -k https://dev.l10n.org.al/translations/vocabulary/export/ICT_sq/txt1
 *   curl -k https://dev.l10n.org.al/translations/vocabulary/export/ICT_sq/org
 */
function btrCore_vocabulary_export($vocabulary, $format =NULL) {
  // Try to avoid concurrent exports because they
  // may affect the performance of the server.
  if (!lock_acquire('export_project')) {
    print t("Error: Server is currently busy. Please try to export again later.");
    drupal_exit();
  }

  // Get the parameters.
  $vocabulary = check_plain($vocabulary);
  if ($format == NULL) {
    $format = 'JSON';
  }
  else {
    $format = strtoupper(check_plain($format));
  }

  // Get the language of the project.
  $lng = preg_replace('/^.*_/', '', $vocabulary);

  // Get the template id (potid) of this vocabulary.
  $query = "SELECT potid FROM {btr_templates} WHERE pguid = :pguid";
  $origin = 'vocabulary';
  $project = $vocabulary;
  $params = array(':pguid' => sha1($origin . $project));
  $potid = btr_query($query, $params)->fetchField();

  // Build the query for getting all the strings of this vocabulary.
  $query = $GLOBALS['btr_db']->select('btr_locations', 'l')
    ->fields('l', array('sguid'))
    ->condition('l.potid', $potid);
  $query->leftJoin('btr_strings', 's', 's.sguid = l.sguid');
  $query->orderBy('s.string');

  // Get the strings and their translations.
  $strings = btr_get_query_strings($query, $lng);
  //print '<xmp>';  print_r($strings);  print '</xmp>';  exit();

  // Simplify the structure of the result.
  $result = array();
  foreach ($strings as $str) {
    $translations = array();
    foreach ($str->translations as $trans) {
      $translations[] = $trans->translation;
    }
    $result[$str->string] = $translations;
  }

  // Output the result.
  switch ($format) {
    default:
    case 'JSON':
      $output = drupal_json_encode($result);
      header('Content-Type: application/json; charset=utf-8');
      print $output;
      break;

    case 'TXT1':
      $output = "Vocabulary: $vocabulary\n\n";
      foreach ($result as $string => $translations) {
        $output .= $string . ' <==> ' . implode(' / ', $translations) . "\n";
      }

      // Send the output.
      header('Content-Type: text/plain; charset=utf-8');
      header('Content-Disposition: attachment; filename="vocabulary-' . $vocabulary . '.txt"');
      header('Content-Transfer-Encoding: binary');
      header("Content-Length: " . sizeof($output));
      print $output;
      break;

    case 'TXT2':
      $output = "Vocabulary: $vocabulary\n\n";
      foreach ($result as $string => $translations) {
        $output .= '  + ' . $string . "\n";
        foreach ($translations as $translation) {
          $output .= '      - ' . $translation . "\n";
        }
        $output .= "\n";
      }

      // Send the output.
      header('Content-Type: text/plain; charset=utf-8');
      header('Content-Disposition: attachment; filename="vocabulary-' . $vocabulary . '.txt"');
      header('Content-Transfer-Encoding: binary');
      header("Content-Length: " . sizeof($output));
      print $output;
      break;

    case 'ORG':
      $output = "* Vocabulary: $vocabulary\n\n";
      foreach ($result as $string => $translations) {
        $output .= '  | *' . $string . '* | -- | ';
        $output .= implode('; ', $translations);
        $output .= " |\n";
      }

      // Send the output.
      header('Content-Type: text/plain; charset=utf-8');
      header('Content-Disposition: attachment; filename="vocabulary-' . $vocabulary . '.org"');
      header('Content-Transfer-Encoding: binary');
      header("Content-Length: " . sizeof($output));
      print $output;
      break;
  }

  // Stop execution.
  lock_release('export_project');
  drupal_exit();
}

<?php
/**
 * @file
 * Menu callback for vocabulary/export.
 */


/**
 * Callback function for the menu vocabulary/export.
 *
 * Return the list of terms in a vocabulary and all the suggested translations.
 *
 * @param $vocabulary
 *   The name of the vocabulary project (which ends in '_lng').
 *
 * @param $format
 *   The output format: json | txt1 | txt2 | org
 *   Default is 'json'.
 *
 * Examples:
 *   curl -s https://btranslator.org/vocabulary/export/ICT_sq | python -m json.tool
 *   curl https://btranslator.org/vocabulary/export/ICT_sq/txt1
 *   curl https://btranslator.org/vocabulary/export/ICT_sq/org
 */
function btrCore_vocabulary_export($vocabulary, $format ='JSON') {
  // Try to avoid concurrent exports because they
  // may affect the performance of the server.
  if (!lock_acquire('export_project')) {
    print t("Error: Server is currently busy. Please try to export again later.");
    drupal_exit();
  }

  // Get the parameters.
  $vocabulary = check_plain($vocabulary);
  $format = strtoupper(check_plain($format));

  // Get the terms and translations.
  $vocab = preg_replace('/_[^_]*$/', '', $vocabulary);
  $lng = preg_replace('/^.*_/', '', $vocabulary);
  $result = btr::vocabulary_get($vocab, $lng);

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

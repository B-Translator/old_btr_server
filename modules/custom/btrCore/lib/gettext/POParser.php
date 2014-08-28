<?php
/**
 * Copyright (C) 2008, Iulian Ilea (http://iulian.net), all rights reserved.
 * Copyright (C) 2011, Dashamir Hoxha (dashohoxha@gmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace BTranslator;
use \Exception;

class POParser {
  private $_filename;

  /**
   * Format of a msgid entry:
   * array(
   *      'translator-comments'   => '',
   *      'extracted-comments'    => '',
   *      'references'            => array(),
   *      'flags'                 => array(
   *          'fuzzy'
   *          ...
   *      ),
   *      'previous-msgctxt'      => '',
   *      'previous-msgid'        => '',
   *      'previous-msgid_plural' => '',
   *      'msgctxt'               => '',
   *      'msgid'                 => '',
   *      'msgid_plural'          => '',
   *
   *      // when no plural forms
   *      'msgstr'                => '',
   *
   *      // when plural forms
   *      'msgstr'                => array(
   *          0   => '',   // singular
   *          1   => '',   // 1st plural form
   *          2   => '',   // 2nd plural form
   *          ...
   *          n   => ''    // nth plural form
   *      )
   * )
   *
   * @see http://www.gnu.org/software/gettext/manual/gettext.html#PO-Files
   */

  protected function decode($str) {
    return json_decode($str);
  }

  /**
   * Return the string between the quotes, after the first space.
   * For example: msgid "...value_of_msgid..."
   */
  protected function get_string($line) {
    return $this->decode(substr($line, strpos($line, ' ') + 1));
  }

  public function parse($filename) {
    // basic file verification
    if (!is_file($filename)) {
      throw new Exception('The specified file does not exist.');
    }
    $ext = substr($filename, strrpos($filename, '.'));
    if ($ext != '.po' and $ext != '.pot') {
      throw new Exception('The specified file is not a PO/POT file.');
    }

    // read file as an array of lines
    $lines = file($filename, FILE_IGNORE_NEW_LINES);

    // $block can be: msgctxt, msgid, msgid_plural, msgstr,
    // previous-msgctxt, previous-msgid, previous-msgid_plural
    // it is used to keep track of multi-line blocks
    $block = '';

    $entries = array();
    $entry = array(
      'translator-comments' => NULL,
      'extracted-comments' => NULL,
      'references' => array(),
      'flags' => array(),
      'previous-msgctxt' => NULL,
      'previous-msgid' => NULL,
      'previous-msgid_plural' => NULL,
      'msgctxt' => NULL,
      'msgid' => NULL,
      'msgid_plural' => NULL,
      'msgstr' => NULL,
    );
    for ($i=0, $n = count($lines); $i < $n; $i++) {
      $line = $lines[$i];

      // empty line
      if (trim($line) == '') {
        if ($block == 'msgstr') {
          $entries[] = $entry;
          $entry = array(
            'translator-comments' => NULL,
            'extracted-comments' => NULL,
            'references' => array(),
            'flags' => array(),
            'previous-msgctxt' => NULL,
            'previous-msgid' => NULL,
            'previous-msgid_plural' => NULL,
            'msgctxt' => NULL,
            'msgid' => NULL,
            'msgid_plural' => NULL,
            'msgstr' => NULL,
          );
          $block = '';
        }
        continue;
      }

      // translator comments
      if (strpos($line, '# ') === 0) {
        if (empty($entry['translator-comments'])) {
          $entry['translator-comments'] = substr($line, 2);
        }
        else {
          $entry['translator-comments'] .= "\n" . substr($line, 2);
        }
        continue;
      }

      // extracted comments
      if (strpos($line, '#. ') === 0) {
        if (empty($entry['extracted-comments'])) {
          $entry['extracted-comments'] = substr($line, 3);
        }
        else {
          $entry['extracted-comments'] .= "\n" . substr($line, 3);
        }
        continue;
      }

      // references
      if (strpos($line, '#: ') === 0) {
        if (empty($entry['references'])) {
          $entry['references'] = array();
        }
        $entry['references'][] = substr($line, 3);
        continue;
      }

      // flags
      if (strpos($line, '#, ') === 0) {
        if (empty($entry['flags'])) {
          $entry['flags'] = array();
        }
        $entry['flags'][] = substr($line, 3);
        continue;
      }

      // previous msgid, msgid_plural, msgctxt
      if (strpos($line, '#| ') === 0) {
        $comment = substr($line, 3);

        // previous msgctxt
        if (strpos($comment, 'msgctxt ') === 0) {
          $entry['previous-msgctxt'] = $this->get_string($comment);
          $block = 'previous-msgctxt';
          continue;
        }

        // previous msgid
        if (strpos($comment, 'msgid ') === 0) {
          $entry['previous-msgid'] = $this->get_string($comment);
          $block = 'previous-msgid';
          continue;
        }

        // previous msgid_plural
        if (strpos($comment, 'msgid_plural ') === 0) {
          $entry['previous-msgid_plural'] = $this->get_string($comment);
          $block = 'previous-msgid_plural';
          continue;
        }

        // multi-line previous-msgctxt or previous-msgid or previous-msgid_plural
        if ($comment[0] == '"') {
          $entry[$block] .= $this->decode($comment);
          continue;
        }

        continue;
      }

      // msgctxt
      if (strpos($line, 'msgctxt ') === 0) {
        $entry['msgctxt'] = $this->get_string($line);
        $block = 'msgctxt';
        continue;
      }

      // msgid
      if (strpos($line, 'msgid ') === 0) {
        $entry['msgid'] = $this->get_string($line);
        $block = 'msgid';
        continue;
      }

      // msgid_plural
      if (strpos($line, 'msgid_plural ') === 0) {
        $entry['msgid_plural'] = $this->get_string($line);
        $block = 'msgid_plural';
        continue;
      }

      // msgstr (no plural forms)
      if (strpos($line, 'msgstr ') === 0) {
        $entry['msgstr'] = $this->get_string($line);
        $block = 'msgstr';
        continue;
      }

      // msgstr (plural forms)
      if (strpos($line, 'msgstr[') === 0) {
        if (empty($entry['msgstr'])) {
          $entry['msgstr'] = array();
        }
        $entry['msgstr'][] = $this->get_string($line);
        $block = 'msgstr';
        continue;
      }

      // multi-line msgid, msgid_plural or msgstr
      if ($line[0] === '"') {
        // multi-line msgid or msgid_plural
        if ($block == 'msgctxt' or $block == 'msgid' or $block == 'msgid_plural') {
          $entry[$block] .= $this->decode($line);
          continue;
        }

        // multi-line msgstr
        if ($block == 'msgstr') {
          if (!is_array($entry['msgstr'])) {
            $entry['msgstr'] .= $this->decode($line);
            continue;
          }
          else {
            $last = count($entry['msgstr']) - 1;
            $entry['msgstr'][$last] .= $this->decode($line);
            continue;
          }
        }
      }
    }

    // append the last entry
    if ($block == 'msgstr')  $entries[] = $entry;

    return $entries;
  }
}

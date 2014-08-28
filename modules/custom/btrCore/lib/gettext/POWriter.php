<?php
/**
 * Copyright (C) 2011,2014, Dashamir Hoxha (dashohoxha@gmail.com).
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

class POWriter {
  /** Array of lines. */
  private $_output = array();

  protected function w_line($line) {
    $this->_output[] = $line;
  }

  public function write($headers, $comments, $entries, $filename =NULL) {
    $this->write_headers($headers, $comments);
    foreach ($entries as $entry) {
      $this->write_entry($entry);
    }

    if ($filename === NULL) {
      return $this->_output;
    }
    else {
      file_put_contents($filename, implode("\n", $this->_output));
    }
  }

  protected function write_headers($headers, $comments) {
    if (!empty($comments)) {
      $comment_lines = preg_split('~\R~', $comments);
      foreach ($comment_lines as $comment) {
        $this->w_line('# ' . $comment);
      }
    }

    $this->w_line('msgid ""');
    $this->w_line('msgstr ""');
    $arr_headers = preg_split('~\R~', $headers);
    foreach ($arr_headers as $header) {
      if ($header=='')  continue;
      $this->w_line($this->encode($header . "\n"));
    }
  }

  protected function write_entry($entry) {
    $this->w_line('');   //add an empty line as separator

    if (isset($entry->translator_comments)) {
      $this->write_comments('# ', $entry->translator_comments);
    }

    if (isset($entry->extracted_comments)) {
      $this->write_comments('#. ', $entry->extracted_comments);
    }

    if (isset($entry->line_references)) {
      $this->write_comments('#: ', $entry->line_references);
    }

    if (isset($entry->flags)) {
      $flags = explode(' ', $entry->flags);
      foreach ($flags as $flag) {
	if (empty($flag))  continue;
        $this->w_line('#, ' . $flag);
      }
    }

    if (isset($entry->previous_msgctxt)) {
      $this->write_msgx('#| ', 'msgctxt', $entry->previous_msgctxt);
    }

    if (isset($entry->previous_msgid)) {
      $this->write_msgx('#| ', 'msgid', $entry->previous_msgid);
    }

    if (isset($entry->previous_msgid_plural)) {
      $this->write_msgx('#| ', 'msgid_plural', $entry->previous_msgid_plural);
    }

    if (isset($entry->context) && $entry->context != '') {
      $this->write_msgx('', 'msgctxt', $entry->context);
    }

    // msgid and msgid_plural
    $arr_string = explode("\0", $entry->string);
    $this->write_msgx('', 'msgid', $arr_string[0]);
    if (isset($arr_string[1])) {
      $this->write_msgx('', 'msgid_plural', $arr_string[1]);
    }

    // msgstr (or msgstr[])
    $arr_translation = explode("\0", $entry->translation);
    if (count($arr_translation) == 1) {
      $this->write_msgx('', 'msgstr', $arr_translation[0]);
    }
    else {
      foreach ($arr_translation as $i => $translation) {
        $this->write_msgx('', "msgstr[$i]", $translation);
      }
    }
  }

  protected function write_comments($prefix, $comments) {
    $comment_lines = explode("\n", $comments);
    foreach ($comment_lines as $comment) {
      $this->w_line($prefix . $comment);
    }
  }

  protected function write_msgx($prefix, $type, $content) {
    $lines = preg_split('~\R~', $content);
    if (count($lines) == 1) {
      $this->w_line($prefix . $type . ' ' . $this->encode($lines[0]));
    }
    else {
      $this->w_line($prefix . $type . ' ""');
      $last = count($lines) - 1;
      for ($i=0; $i < $last; $i++) {
        $this->w_line($prefix . $this->encode($lines[$i] . "\n"));
      }
      if (!empty($lines[$last])) {
        $this->w_line($prefix . $this->encode($lines[$last]));
      }
    }
  }

  /**
   * Escape the special chars on the given string
   * and surround it by double quotes.
   */
  private function encode($str) {
    return json_encode($str, JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES);
  }
}

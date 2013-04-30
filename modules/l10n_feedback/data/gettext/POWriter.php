<?php

/**
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

class POWriter
{
  /** Array of lines. */
  private $_output = array();

  protected function w_line($line)
  {
    $this->_output[] = $line;
  }

  protected function w_quoted($prefix, $value)
  {
    $value = str_replace('"', '\\"', $value);
    $this->w_line($prefix . '"' . $value . '\n"');
  }

  public function write($headers, $comments, $entries, $filename =NULL)
  {
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

  protected function write_headers($headers, $comments)
  {
    if (!empty($comments)) {
      $comment_lines = explode("\n", $comments);
      foreach ($comment_lines as $comment) {
	$this->w_line('# ' . $comment);
      }
    }

    $this->w_line('msgid ""');
    $this->w_line('msgstr ""');
    $arr_headers = explode('\n', $headers);
    foreach ($arr_headers as $header) {
      if ($header=='')  continue;
      $this->w_quoted('', $header);
    }
  }

  protected function write_entry($entry)
  {
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
    if (count($arr_translation) == 1)
      {
	$this->write_msgx('', 'msgstr', $arr_translation[0]);
      }
    else
      {
	foreach ($arr_translation as $i => $translation) {
	  $this->write_msgx('', "msgstr[$i]", $translation);
	}
      }
  }

  protected function write_comments($prefix, $comments)
  {
    $comment_lines = explode("\n", $comments);
    foreach ($comment_lines as $comment) {
      $this->w_line($prefix . $comment);
    }
  }

  protected function write_msgx($prefix, $type, $content)
  {
    $lines = preg_split('~(*BSR_ANYCRLF)\R|\\\\n~', $content);
    if (count($lines) == 1)
      {
	$str = str_replace('"', '\\"', $lines[0]);
	$this->w_line($prefix . $type . ' "' . $str . '"');
      }
    else
      {
	$this->w_line($prefix . $type . ' ""');
	$last = count($lines) - 1;
	for ($i=0; $i < $last; $i++) {
	  $this->w_quoted($prefix, $lines[$i]);
	}
	if (!empty($lines[$last])) {
	  $str = str_replace('"', '\\"', $lines[$last]);
	  $this->w_line($prefix . '"' . $str . '"');
	}
      }
  }
}
?>
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

class POParser
{
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

  protected function _dequote($str)
  {
    return substr($str, 1, -1);
  }

  /**
   * Return the string between the quotes, after the first space.
   * For example: msgid "...value_of_msgid..."
   */
  protected function _get_value($line)
  {
    return $this->_dequote(substr($line, strpos($line, ' ') + 1));
  }

  /**
   * Get the headers of the PO file (from the msgstr of the first (empty) entry)
   * and return them as an array.
   */
  public function parse_headers($str_headers)
  {
    $headers = array(
		     'Project-Id-Version'            => '',
		     'Report-Msgid-Bugs-To'          => '',
		     'POT-Creation-Date'             => '',
		     'PO-Revision-Date'              => '',
		     'Last-Translator'               => '',
		     'Language-Team'                 => '',
		     'Content-Type'                  => '',
		     'Content-Transfer-Encoding'     => '',
		     'Plural-Forms'                  => '',
		     );

    $lines = explode('\n', $str_headers);
    $i = 0;
    for ($i=0, $n=count($lines); $i < $n; $i++)
      {
	$line = $lines[$i];

	$colonIndex = strpos($line, ':');
	if ($colonIndex === false)  continue;

	$headerName = substr($line, 0, $colonIndex);
	if (!isset($headers[$headerName]))  continue;

	// skip the white space after the colon
	$headers[$headerName] = substr($line, $colonIndex + 1);
      }

    return $headers;
  }

  public function parse($filename)
  {
    // basic file verification
    if (!is_file($filename))
      {
	throw new Exception('The specified file does not exist.');
      }
    $ext = substr($filename, strrpos($filename, '.'));
    if ($ext != '.po' and $ext != '.pot')
      {
	throw new Exception('The specified file is not a PO/POT file.');
      }

    // read file as an array of lines
    $lines = file($filename, FILE_IGNORE_NEW_LINES);

    // $block can be: msgctxt, msgid, msgid_plural, msgstr,
    // previous-msgctxt, previous-msgid, previous-msgid_plural
    // it is used to keep track of multi-line blocks
    $block = '';

    $entries = array();
    $entry = array();
    for ($i=0, $n = count($lines); $i < $n; $i++)
      {
	$line = $lines[$i];

	// empty line
	if (trim($line) == '')
	  {
	    if ($block == 'msgstr')
	      {
		$entries[] = $entry;
		$entry = array();
		$block = '';
	      }
	    continue;
	  }

	// translator comments
	if (strpos($line, '# ') === 0)
	  {
	    if (!isset($entry['translator-comments']))
	      {
		$entry['translator-comments'] = substr($line, 2);
	      }
	    else
	      {
		$entry['translator-comments'] .= "\n" . substr($line, 2);
	      }
	    continue;
	  }

	// extracted comments
	if (strpos($line, '#. ') === 0)
	  {
	    if (!isset($entry['extracted-comments']))
	      {
		$entry['extracted-comments'] = substr($line, 3);
	      }
	    else
	      {
		$entry['extracted-comments'] .= "\n" . substr($line, 3);
	      }
	    continue;
	  }

	// references
	if (strpos($line, '#: ') === 0)
	  {
	    if (!isset($entry['references']))
	      {
		$entry['references'] = array();
	      }
	    $entry['references'][] = substr($line, 3);
	    continue;
	  }

	// flags
	if (strpos($line, '#, ') === 0)
	  {
	    if (!isset($entry['flags']))
	      {
		$entry['flags'] = array();
	      }
	    $entry['flags'][] = substr($line, 3);
	    continue;
	  }

	// previous msgid, msgid_plural, msgctxt
	if (strpos($line, '#| ') === 0)
	  {
	    $comment = substr($line, 3);

	    // previous msgctxt
	    if (strpos($comment, 'msgctxt ') === 0)
	      {
		$entry['previous-msgctxt'] = $this->_get_value($comment);
		$block = 'previous-msgctxt';
		continue;
	      }

	    // previous msgid
	    if (strpos($comment, 'msgid ') === 0)
	      {
		$entry['previous-msgid'] = $this->_get_value($comment);
		$block = 'previous-msgid';
		continue;
	      }

	    // previous msgid_plural
	    if (strpos($comment, 'msgid_plural ') === 0)
	      {
		$entry['previous-msgid_plural'] = $this->_get_value($comment);
		$block = 'previous-msgid_plural';
		continue;
	      }

	    // multi-line previous-msgctxt or previous-msgid or previous-msgid_plural
	    if ($comment[0] == '"')
	      {
		$entry[$block] .= $this->_dequote($comment);
		continue;
	      }

	    continue;
	  }

	// msgctxt
	if (strpos($line, 'msgctxt ') === 0)
	  {
	    $entry['msgctxt'] = $this->_get_value($line);
	    $block = 'msgctxt';
	    continue;
	  }

	// msgid
	if (strpos($line, 'msgid ') === 0)
	  {
	    $entry['msgid'] = $this->_get_value($line);
	    $block = 'msgid';
	    continue;
	  }

	// msgid_plural
	if (strpos($line, 'msgid_plural ') === 0)
	  {
	    $entry['msgid_plural'] = $this->_get_value($line);
	    $block = 'msgid_plural';
	    continue;
	  }

	// msgstr (no plural forms)
	if (strpos($line, 'msgstr ') === 0)
	  {
	    $entry['msgstr'] = $this->_get_value($line);
	    $block = 'msgstr';
	    continue;
	  }

	// msgstr (plural forms)
	if (strpos($line, 'msgstr[') === 0)
	  {
	    if (!isset($entry['msgstr']))
	      {
		$entry['msgstr'] = array();
	      }
	    $entry['msgstr'][] = $this->_get_value($line);
	    $block = 'msgstr';
	    continue;
	  }

	// multi-line msgid, msgid_plural or msgstr
	if ($line[0] === '"')
	  {
	    // multi-line msgid or msgid_plural
	    if ($block == 'msgctxt' or $block == 'msgid' or $block == 'msgid_plural')
	      {
		$entry[$block] .= $this->_dequote($line);
		continue;
	      }

	    // multi-line msgstr
	    if ($block == 'msgstr')
	      {
		if (!is_array($entry['msgstr']))
		  {
		    $entry['msgstr'] .= $this->_dequote($line);
		    continue;
		  }
		else
		  {
		    $last = count($entry['msgstr']) - 1;
		    $entry['msgstr'][$last] .= $this->_dequote($line);
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
?>
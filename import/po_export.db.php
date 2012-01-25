<?php

include(dirname(__FILE__) . '/db.php');

class DB_PO_Export extends DB
{
  /**
   * Get and return a list of template ids for the given project.
   */
  public function get_potid_list($origin, $project)
  {
    $get_potid = $this->dbh->prepare("
      SELECT potid FROM l10n_suggestions_templates WHERE pguid = :pguid
    ");
    $params = array(':pguid' => sha1($origin . $project));
    $get_potid->execute($params);

    $arr_potid = array();
    while ($potid = $get_potid->fetchColumn()) {
      $arr_potid[] = $potid;
    }

    return $arr_potid;
  }

  /**
   * Get and return the filename, headers and comments of a file.
   */
  public function get_file_data($potid, $lng)
  {
    $get_file_headers = $this->dbh->prepare("
      SELECT filename, headers, comments FROM l10n_suggestions_files
      WHERE potid = :potid AND lng = :lng
    ");
    $params = array(':potid' => $potid, ':lng' => $lng);
    $get_file_headers->execute($params);

    $row = $get_file_headers->fetch();
    $filename = isset($row['filename']) ? $row['filename'] : null;
    $headers = isset($row['headers']) ? $row['headers'] : null;
    $comments = isset($row['comments']) ? $row['comments'] : null;

    return array($filename, $headers, $comments);
  }

  /**
   * Get and return an array of strings, indexed by sguid.
   */
  public function get_strings($potid)
  {
    $get_strings = $this->dbh->prepare("
      SELECT l.sguid, s.string, s.context,
	     translator_comments, extracted_comments, line_references, flags,
	     previous_msgctxt, previous_msgid, previous_msgid_plural
      FROM l10n_suggestions_locations l
      LEFT JOIN l10n_suggestions_strings s ON (s.sguid = l.sguid)
      WHERE l.potid = :potid
    ");
    $params = array(':potid' => $potid);
    $get_strings->execute($params);

    $arr_strings = array();
    while ($string = $get_strings->fetchObject()) {
      $sguid = $string->sguid;
      $arr_strings[$sguid] = $string;
    }

    return $arr_strings;
  }

  /**
   * Get and return an array of translations, indexed by sguid.
   */
  public function get_best_translations($potid, $lng)
  {
    $get_best_translations = $this->dbh->prepare("
      SELECT t2.sguid, t2.translation
      FROM (SELECT t1.sguid, t1.translation, MAX(t1.count) AS max_count
	      FROM l10n_suggestions_locations AS l1
	      LEFT JOIN l10n_suggestions_translations AS t1
		    ON (t1.sguid = l1.sguid AND t1.lng = :lng)
	      WHERE l1.potid = :potid
	      GROUP BY t1.sguid
	   ) AS m
      LEFT JOIN l10n_suggestions_translations AS t2
	    ON (t2.sguid = m.sguid AND t2.lng = :lng AND t2.count = m.max_count)
      GROUP BY t2.sguid
    ");
    $params = array(':potid' => $potid, ':lng' => $lng);
    $get_best_translations->execute($params);

    $arr_translations = array();
    while ($translation = $get_best_translations->fetchObject()) {
      $sguid = $translation->sguid;
      $arr_translations[$sguid] = $translation;
    }

    return $arr_translations;
  }
}
?>
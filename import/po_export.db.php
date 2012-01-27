<?php

include(dirname(__FILE__) . '/db.php');

class DB_PO_Export extends DB
{
  /**
   * Get and return the id of a template.
   */
  public function get_template_potid($origin, $project, $tplname)
  {
    $get_template_potid = $this->dbh->prepare("
      SELECT potid FROM l10n_suggestions_templates
      WHERE pguid = :pguid AND tplname = :tplname
    ");
    $pguid = sha1($origin . $project);
    $params = array(':pguid' => $pguid, ':tplname' => $tplname);
    $get_template_potid->execute($params);

    $row = $get_template_potid->fetch();
    $potid = isset($row['potid']) ? $row['potid'] : null;

    return $potid;
  }

  /**
   * Get and return the headers of a file.
   */
  public function get_file_headers($potid, $lng)
  {
    $get_file_headers = $this->dbh->prepare("
      SELECT headers, comments FROM l10n_suggestions_files
      WHERE potid = :potid AND lng = :lng
    ");
    $params = array(':potid' => $potid, ':lng' => $lng);
    $get_file_headers->execute($params);

    $row = $get_file_headers->fetch();
    $headers = isset($row['headers']) ? $row['headers'] : null;
    $comments = isset($row['comments']) ? $row['comments'] : null;

    return array($headers, $comments);
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
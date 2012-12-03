<?php

include(dirname(dirname(__FILE__)) . '/db/class.DB.php');

class DB_PO_Export extends DB
{
  /**
   * Get and return the id of a template.
   */
  public function get_template_potid($origin, $project, $tplname)
  {
    $get_template_potid = $this->dbh->prepare("
      SELECT potid FROM l10n_feedback_templates
      WHERE pguid = :pguid AND tplname = :tplname
    ");
    $pguid = sha1($origin . $project);
    $params = array(':pguid' => $pguid, ':tplname' => $tplname);
    $get_template_potid->execute($params);

    $row = $get_template_potid->fetch();
    $potid = isset($row['potid']) ? $row['potid'] : NULL;

    return $potid;
  }

  /**
   * Get and return the headers of a file.
   */
  public function get_file_headers($potid, $lng)
  {
    $get_file_headers = $this->dbh->prepare("
      SELECT headers, comments FROM l10n_feedback_files
      WHERE potid = :potid AND lng = :lng
    ");
    $params = array(':potid' => $potid, ':lng' => $lng);
    $get_file_headers->execute($params);

    $row = $get_file_headers->fetch();
    $headers = isset($row['headers']) ? $row['headers'] : NULL;
    $comments = isset($row['comments']) ? $row['comments'] : NULL;

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
      FROM l10n_feedback_locations l
      LEFT JOIN l10n_feedback_strings s ON (s.sguid = l.sguid)
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
   * Get and return an associative array of the most voted translations,
   * indexed by sguid. Translations which have no votes at all are skipped.
   */
  public function get_most_voted_translations($potid, $lng)
  {
    $translations_max_count = $this->dbh->prepare("
      CREATE TEMPORARY TABLE translations_max_count
          SELECT t.sguid, t.translation, MAX(t.count) AS max_count
	  FROM l10n_feedback_locations AS l
	  LEFT JOIN l10n_feedback_translations AS t
                    ON (t.sguid = l.sguid AND t.lng = :lng)
	  WHERE l.potid = :potid AND t.count > 0
	  GROUP BY t.sguid
    ");
    $params = array(':potid' => $potid, ':lng' => $lng);
    $translations_max_count->execute($params);

    $get_most_voted_translations = $this->dbh->prepare("
      SELECT t.sguid, t.translation
      FROM translations_max_count AS m
      LEFT JOIN l10n_feedback_translations AS t
	    ON (t.sguid = m.sguid AND t.lng = :lng AND t.count = m.max_count)
      GROUP BY t.sguid
    ");
    $params = array(':lng' => $lng);
    $get_most_voted_translations->execute($params);

    $arr_translations = array();
    while ($row = $get_most_voted_translations->fetch()) {
      $sguid = $row['sguid'];
      $arr_translations[$sguid] = $row['translation'];
    }

    return $arr_translations;
  }

  /**
   * Export from DB the content of the original file that was imported,
   * save it into a temp file, and return its filename.
   */
  public function get_original_file($potid, $lng)
  {
    $get_file_content = $this->dbh->prepare("
      SELECT content FROM l10n_feedback_files
      WHERE potid = :potid AND lng = :lng
    ");
    $params = array(':potid' => $potid, ':lng' => $lng);
    $get_file_content->execute($params);

    $row = $get_file_content->fetch();
    $file_content = isset($row['content']) ? $row['content'] : '';

    $tmpfname = tempnam('/tmp', 'l10n_feedback_export_');
    shell_exec("rm $tmpfname");
    $tmpfname .= '.po';
    file_put_contents($tmpfname, $file_content);

    return $tmpfname;
  }

  /**
   * Get and return an associative array of the translations that are voted
   * by any of the people in the array of voters, indexed by sguid.
   * Translations which have no votes from these users are skipped.
   * Voters are identified by their emails.
   */
  public function get_preferred_translations($potid, $lng, $arr_voters)
  {
    if (empty($arr_voters)) {
      return array();
    }

    list($voters, $params) = $this->get_query_placeholder_params($arr_voters);
    $params[':potid'] = $potid;
    $params[':lng'] = $lng;
    $preferred_translations = $this->dbh->prepare("
      CREATE TEMPORARY TABLE preferred_translations
          SELECT t.sguid, t.tguid, t.translation, COUNT(*) AS v_count
          FROM l10n_feedback_locations AS l
          LEFT JOIN l10n_feedback_translations AS t ON (t.sguid = l.sguid AND t.lng = :lng)
          LEFT JOIN l10n_feedback_votes AS v ON (v.tguid = t.tguid)
          WHERE l.potid = :potid AND v.umail IN ($voters)
          GROUP BY t.tguid
          HAVING COUNT(*) > 0
    ");
    $preferred_translations->execute($params);

    $preferred_translations_max_count = $this->dbh->prepare("
      CREATE TEMPORARY TABLE preferred_translations_max_count
          SELECT sguid, translation, MAX(v_count) AS max_count
	  FROM preferred_translations
	  GROUP BY sguid
    ");
    $preferred_translations_max_count->execute();

    $get_preferred_translations = $this->dbh->prepare("
      SELECT p.sguid, p.translation
      FROM preferred_translations_max_count AS m
      LEFT JOIN preferred_translations AS p
	    ON (p.sguid = m.sguid AND p.v_count = m.max_count)
      GROUP BY p.sguid
    ");
    $get_preferred_translations->execute();

    $arr_translations = array();
    while ($row = $get_preferred_translations->fetch()) {
      $sguid = $row['sguid'];
      $arr_translations[$sguid] = $row['translation'];
    }

    return $arr_translations;
  }

  /**
   * Convert the given array of voters into a string of placeholders
   * and an array of parameters (to be used on the WHERE condition
   * of get_preferred_translations()).
   * Return them as an array of two elements: array($placeholders, $params)
   */
  private function get_query_placeholder_params($arr_voters) {
    $placeh = ':voter00';
    $placeholders = array();
    $params = array();
    foreach ($arr_voters as $voter) {
      $placeh++;
      $placeholders[] = $placeh;
      $params[$placeh] = $voter;
    }
    $placeholders = implode(', ', $placeholders);
    return array($placeholders, $params);
  }
}
?>
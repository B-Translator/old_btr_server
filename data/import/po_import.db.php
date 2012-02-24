<?php

include(dirname(dirname(__FILE__)) . '/db/class.DB.php');

class DB_PO_Import extends DB
{
  /** Prepare the queries that will be used and store them in $this->queries[] . */
  protected function prepare_queries()
  {
    // check_string_sguid
    $this->queries['check_string_sguid'] = $this->dbh->prepare("
      SELECT sguid FROM l10n_suggestions_strings WHERE sguid = :sguid
    ");

    // insert_translation
    $this->queries['insert_translation'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_translations
	 (sguid, lng, translation, tguid, count, uid, time)
      VALUES
	 (:sguid, :lng, :translation, :tguid, :count, :uid, :time)
    ");
  }

  /**
   * Get and return the id of a template.
   */
  public function get_template_potid($origin, $project, $tplname)
  {
    $pguid = sha1($origin . $project);
    $stmt = $this->dbh->prepare("
      SELECT potid FROM l10n_suggestions_templates
      WHERE pguid = :pguid AND tplname = :tplname
    ");
    $params = array(
		    ':pguid' => $pguid,
		    ':tplname' => $tplname,
		    );
    $stmt->execute($params);
    $row = $stmt->fetch();
    $potid = isset($row['potid']) ? $row['potid'] : null;

    return $potid;
  }

  /** Insert a new file and return its id. */
  public function insert_file($filename, $relative_filename, $hash, $potid, $lng, $headers, $comments)
  {
    $stmt = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_files
	 (filename, content, hash, potid, lng, headers, comments, uid, time)
      VALUES
	 (:filename, :content, :hash, :potid, :lng, :headers, :comments, :uid, :time)
    ");
    $params = array(
		    ':filename' => $relative_filename,
		    ':content' => file_get_contents($filename),
		    ':hash' => $hash,
		    ':potid' => $potid,
		    ':lng' => $lng,
		    ':headers' => $headers,
		    ':comments' => $comments,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $stmt->execute($params);
    $fid = $this->dbh->lastInsertId();

    return $fid;
  }

  /**
   * Get and return the string id.
   */
  public function check_string_sguid($sguid)
  {
    $params = array(':sguid' => $sguid);
    $this->queries['check_string_sguid']->execute($params);
    $row = $this->queries['check_string_sguid']->fetch();
    $found = isset($row['sguid']) ? true : false;

    return $found;
  }

  /** Insert a translation into DB. */
  public function insert_translation($sguid, $lng, $translation)
  {
    $tguid = sha1($translation . $lng . $sguid);
    $params = array(
		    ':sguid' => $sguid,
		    ':lng' => $lng,
		    ':translation' => $translation,
		    ':tguid' => $tguid,
		    ':count' => 0,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_translation']->execute($params);

    return $tguid;
  }
}
?>
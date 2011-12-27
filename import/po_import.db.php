<?php

include(dirname(__FILE__) . '/db.php');

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
   * Get and return the id of a project.
   */
  public function get_project_id($project, $origin)
  {
    $stmt = $this->dbh->prepare("
      SELECT pid FROM l10n_suggestions_projects
      WHERE project = :project AND origin = :origin
    ");
    $params = array(
		    ':project' => $project,
		    ':origin' => $origin,
		    );
    $stmt->execute($params);
    $row = $stmt->fetch();
    $pid = isset($row['pid']) ? $row['pid'] : null;

    return $pid;
  }

  /** Insert a new file and return its id. */
  public function insert_file($hash, $pid, $lng, $headers)
  {
    $stmt = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_files
	 (hash, pid, lng, headers, uid, time)
      VALUES
	 (:hash, :pid, :lng, :headers, :uid, :time)
    ");
    $params = array(
		    ':hash' => $hash,
		    ':pid' => $pid,
		    ':lng' => $lng,
		    ':headers' => $headers,
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
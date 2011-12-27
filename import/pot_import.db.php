<?php

include(dirname(__FILE__) . '/db.php');

class DB_POT_Import extends DB
{
  /** Prepare the queries that will be used and store them in $this->queries[] . */
  protected function prepare_queries()
  {
    // get_project_id
    $this->queries['get_project_id'] = $this->dbh->prepare("
      SELECT pid FROM l10n_suggestions_projects
      WHERE project = :project AND origin = :origin
    ");

    // insert_project
    $this->queries['insert_project'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_projects
	 (project, origin, uid, time)
      VALUES
	 (:project, :origin, :uid, :time)
    ");

    // insert_string
    $this->queries['insert_string'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_strings
	 (string, context, sguid, uid, time, count)
      VALUES
	 (:string, :context, :sguid, :uid, :time, :count)
    ");

    // insert_location
    $this->queries['insert_location'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_locations
	 (sguid, pid,
          translator_comments, extracted_comments, referencies, flags,
          previous_msgctxt, previous_msgid, previous_msgid_plural)
      VALUES
	 (:sguid, :pid,
          :translator_comments, :extracted_comments, :referencies, :flags,
          :previous_msgctxt, :previous_msgid, :previous_msgid_plural)
    ");
  }

  /**
   * Get and return the id of a project.
   */
  public function get_project_id($project, $origin)
  {
    $params = array(
		    ':project' => $project,
		    ':origin' => $origin,
		    );
    $this->queries['get_project_id']->execute($params);
    $row = $this->queries['get_project_id']->fetch();
    $pid = isset($row['pid']) ? $row['pid'] : null;

    return $pid;
  }

  /**
   * Insert a new project and return its id.
   */
  public function insert_project($project, $origin)
  {
    $params = array(
		    ':project' => $project,
		    ':origin' => $origin,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_project']->execute($params);
    $pid = $this->dbh->lastInsertId();

    return $pid;
  }

  /**
   * Insert a new string.
   */
  public function insert_string($string, $context)
  {
    $params = array(
		    ':string' => $string,
		    ':context' => $context,
		    ':sguid' => sha1($string . $context),
		    ':uid' => 1,   //admin
		    ':time' => $this->time,
		    ':count' => 1,
		    );
    $this->queries['insert_string']->execute($params);
  }

  /** Insert a location into DB. */
  public function insert_location($pid, $sguid, $entry)
  {
    $translator_comments = isset($entry['translator-comments']) ? $entry['translator-comments'] : null;
    $extracted_comments = isset($entry['extracted-comments']) ? $entry['extracted-comments'] : null;
    $referencies = isset($entry['referencies']) ? implode(' ', $entry['referencies']) : null;
    $flags = isset($entry['flags']) ? implode(' ', $entry['flags']) : null;
    $previous_msgctxt = isset($entry['previous-msgctxt']) ? $entry['previous-msgctxt'] : null;
    $previous_msgid = isset($entry['previous-msgid']) ? $entry['previous-msgid'] : null;
    $previous_msgid_plural = isset($entry['previous-msgid_plural']) ? $entry['previous-msgid_plural'] : null;
    $params = array(
		    ':pid' => $pid,
		    ':sguid' => $sguid,
		    ':translator_comments' => $translator_comments,
		    ':extracted_comments' => $extracted_comments,
		    ':referencies' => $referencies,
		    ':flags' => $flags,
		    ':previous_msgctxt' => $previous_msgctxt,
		    ':previous_msgid' => $previous_msgid,
		    ':previous_msgid_plural' => $previous_msgid_plural,
		    );
    $this->queries['insert_location']->execute($params);
    $lid = $this->dbh->lastInsertId();

    return $lid;
  }
}
?>
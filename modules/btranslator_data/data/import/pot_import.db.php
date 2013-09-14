<?php

include(dirname(dirname(__FILE__)) . '/db/class.DB.php');

class DB_POT_Import extends DB
{
  /** Prepare the queries that will be used and store them in $this->queries[] . */
  protected function prepare_queries()
  {
    // get_project_pguid
    $this->queries['get_project_pguid'] = $this->dbh->prepare("
      SELECT pguid FROM btr_projects WHERE pguid = :pguid
    ");

    // insert_project
    $this->queries['insert_project'] = $this->dbh->prepare("
      INSERT INTO btr_projects
	 (pguid, project, origin, uid, time)
      VALUES
	 (:pguid, :project, :origin, :uid, :time)
    ");

    // get_template_potid
    $this->queries['get_template_potid'] = $this->dbh->prepare("
      SELECT potid FROM btr_templates
      WHERE pguid = :pguid AND tplname = :tplname
    ");

    // insert_template
    $this->queries['insert_template'] = $this->dbh->prepare("
      INSERT INTO btr_templates
	 (tplname, filename, pguid, uid, time)
      VALUES
	 (:tplname, :filename, :pguid, :uid, :time)
    ");

    // insert_string
    $this->queries['insert_string'] = $this->dbh->prepare("
      INSERT INTO btr_strings
	 (string, context, sguid, uid, time, count)
      VALUES
	 (:string, :context, :sguid, :uid, :time, :count)
    ");

    // insert_location
    $this->queries['insert_location'] = $this->dbh->prepare("
      INSERT INTO btr_locations
	 (sguid, potid,
          translator_comments, extracted_comments, line_references, flags,
          previous_msgctxt, previous_msgid, previous_msgid_plural)
      VALUES
	 (:sguid, :potid,
          :translator_comments, :extracted_comments, :line_references, :flags,
          :previous_msgctxt, :previous_msgid, :previous_msgid_plural)
    ");
  }

  /**
   * Get and return the pguid of a project.
   */
  public function get_project_pguid($project, $origin)
  {
    $params = array(':pguid' => sha1($origin . $project));
    $this->queries['get_project_pguid']->execute($params);
    $row = $this->queries['get_project_pguid']->fetch();
    $pguid = isset($row['pguid']) ? $row['pguid'] : NULL;

    return $pguid;
  }

  /**
   * Insert a new project and return its id.
   */
  public function insert_project($project, $origin)
  {
    $pguid = sha1($origin . $project);
    $params = array(
		    ':pguid' => $pguid,
		    ':project' => $project,
		    ':origin' => $origin,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_project']->execute($params);

    return $pguid;
  }

  /**
   * Get and return the potid of a template.
   */
  public function get_template_potid($pguid, $tplname)
  {
    $params = array(
		    ':pguid' => $pguid,
		    ':tplname' => $tplname,
		    );
    $this->queries['get_template_potid']->execute($params);
    $row = $this->queries['get_template_potid']->fetch();
    $potid = isset($row['potid']) ? $row['potid'] : NULL;

    return $potid;
  }

  /**
   * Insert a new template and return its id.
   */
  public function insert_template($pguid, $tplname, $filename)
  {
    $params = array(
		    ':tplname' => $tplname,
		    ':filename' => $filename,
		    ':pguid' => $pguid,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_template']->execute($params);
    $potid = $this->dbh->lastInsertId();

    return $potid;
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
  public function insert_location($potid, $sguid, $entry)
  {
    $translator_comments = isset($entry['translator-comments']) ? $entry['translator-comments'] : NULL;
    $extracted_comments = isset($entry['extracted-comments']) ? $entry['extracted-comments'] : NULL;
    $line_references = isset($entry['references']) ? implode(' ', $entry['references']) : NULL;
    $flags = isset($entry['flags']) ? implode(' ', $entry['flags']) : NULL;
    $previous_msgctxt = isset($entry['previous-msgctxt']) ? $entry['previous-msgctxt'] : NULL;
    $previous_msgid = isset($entry['previous-msgid']) ? $entry['previous-msgid'] : NULL;
    $previous_msgid_plural = isset($entry['previous-msgid_plural']) ? $entry['previous-msgid_plural'] : NULL;
    $params = array(
		    ':sguid' => $sguid,
		    ':potid' => $potid,
		    ':translator_comments' => $translator_comments,
		    ':extracted_comments' => $extracted_comments,
		    ':line_references' => $line_references,
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
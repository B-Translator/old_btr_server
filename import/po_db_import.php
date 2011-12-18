<?php
class PODB_Import
{
  /** Keeps the DB handler/connection. */
  private $dbh;

  /** Keeps an associated array of prepared queries. */
  private $queries = array();

  /** Timestamp of inserting data. */
  private $time;

  public function __construct()
  {
    $this->connect();
    $this->prepare_queries();
    $this->time = date('Y-m-d H:i:s');
  }

  /** Create a DB connection. */
  protected function connect()
  {
    // Get the DB parameters.
    @include_once(dirname(__FILE__).'/db_params.php');

    // Create a DB connection.
    $DSN = "$dbdriver:host=$dbhost;dbname=$dbname";
    //print "$DSN\n";  exit(0);  //debug
    $this->dbh = new PDO($DSN, $dbuser, $dbpass,
			 array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8"));
  }

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

    // get_file_id
    $this->queries['get_file_id'] = $this->dbh->prepare("
      SELECT fid FROM l10n_suggestions_files
      WHERE file = :file AND pid = :pid AND lng = :lng
    ");

    // insert_file
    $this->queries['insert_file'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_files
	 (pid, lng, file, headers, uid, time)
      VALUES
	 (:pid, :lng, :file, :headers, :uid, :time)
    ");

    // update_file
    $this->queries['update_file'] = $this->dbh->prepare("
      UPDATE l10n_suggestions_files
      SET  file = :file, headers = :headers, uid = :uid, time = :time
      WHERE pid = :pid AND lng = :lng
    ");

    // get_string_id
    $this->queries['get_string_id'] = $this->dbh->prepare("
      SELECT sguid FROM l10n_suggestions_strings WHERE sguid = :sguid
    ");

    // insert_string
    $this->queries['insert_string'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_strings
	 (string, context, sguid, uid, time)
      VALUES
	 (:string, :context, :sguid, :uid, :time)
    ");

    // get_location_id
    $this->queries['get_location_id'] = $this->dbh->prepare("
      SELECT lid FROM l10n_suggestions_locations
      WHERE pid = :pid AND sguid = :sguid
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

    // get_translation_id
    $this->queries['get_translation_id'] = $this->dbh->prepare("
      SELECT tguid FROM l10n_suggestions_translations
      WHERE tguid = :tguid
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
   * Get and return the id of a file.
   * A file is uniquely identified by the project id and the language.
   */
  public function get_file_id($pid, $lng, $file)
  {
    $params = array(
		    ':file' => $file,
		    ':pid' => $pid,
		    ':lng' => $lng,
		    );
    $this->queries['get_file_id']->execute($params);
    $row = $this->queries['get_file_id']->fetch();
    $fid = isset($row['fid']) ? $row['fid'] : null;

    return $fid;
  }

  /** Insert a new file and return its id. */
  public function insert_file($pid, $lng, $file, $headers)
  {
    $params = array(
		    ':pid' => $pid,
		    ':lng' => $lng,
		    ':file' => $file,
		    ':headers' => $headers,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_file']->execute($params);
    $fid = $this->dbh->lastInsertId();

    return $fid;
  }

  /** Update a file. */
  public function update_file($pid, $lng, $file, $headers)
  {
    $params = array(
		    ':pid' => $pid,
		    ':lng' => $lng,
		    ':file' => $file,
		    ':headers' => $headers,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['update_file']->execute($params);
  }

  /** Return true if the file is already imported. */
  public function file_is_imported($fid)
  {
    $sql = "SELECT imported FROM l10n_suggestions_files WHERE fid = $fid";
    $row = $this->dbh->query($sql)->fetch();
    $imported = isset($row['imported']) ? $row['imported'] : 0;
    return ($imported != 0);
  }

  /** Set to true the imported field of the file. */
  public function set_file_imported($fid)
  {
    $sql = "UPDATE  l10n_suggestions_files SET imported = 1 WHERE fid = $fid";
    return $this->dbh->exec($sql);
  }

  /**
   * Get and return the string id.
   */
  public function get_string_id($string, $context)
  {
    $params = array(':sguid' => sha1($string . $context));
    $this->queries['get_string_id']->execute($params);
    $row = $this->queries['get_string_id']->fetch();
    $sguid = isset($row['sguid']) ? $row['sguid'] : null;

    return $sguid;
  }

  /**
   * Insert a new string and return its id.
   */
  public function insert_string($string, $context)
  {
    $sguid = sha1($string . $context);
    $params = array(
		    ':string' => $string,
		    ':context' => $context,
		    ':sguid' => $sguid,
		    ':uid' => 1,   //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_string']->execute($params);

    return $sguid;
  }

  /** Return the id of a location. */
  public function get_location_id($pid, $sguid)
  {
    $params = array(
		    ':pid' => $pid,
		    ':sguid' => $sguid,
		    );
    $this->queries['get_location_id']->execute($params);
    $row = $this->queries['get_location_id']->fetch();
    $lid = isset($row['lid']) ? $row['lid'] : null;

    return $lid;
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

  /** Get and return the id of a translation. */
  public function get_translation_id($sguid, $lng, $translation)
  {
    $params = array(':tguid' => sha1($translation . $lng . $sguid));
    $this->queries['get_translation_id']->execute($params);
    $row = $this->queries['get_translation_id']->fetch();
    $tguid = isset($row['tguid']) ? $row['tguid'] : null;

    return $tguid;
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
<?php
class PODB
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
    @include_once(dirname(__FILE__).'/settings.php');
    $db = $databases['default']['default'];
    $dbdriver = $db['driver'];
    $dbhost = $db['host'];
    $dbname = $db['database'];  $dbname = 'l10nsq_test';  //debug
    $dbuser = $db['username'];
    $dbpass = $db['password'];

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
      SELECT sid FROM l10n_suggestions_strings WHERE hash = :hash
    ");

    // insert_string
    $this->queries['insert_string'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_strings
	 (string, context, hash, uid, time)
      VALUES
	 (:string, :context, :hash, :uid, :time)
    ");

    // get_location_id
    $this->queries['get_location_id'] = $this->dbh->prepare("
      SELECT lid FROM l10n_suggestions_locations
      WHERE pid = :pid AND sid = :sid
    ");

    // insert_location
    $this->queries['insert_location'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_locations
	 (sid, pid,
          translator_comments, extracted_comments, referencies, flags, 
          previous_msgctxt, previous_msgid, previous_msgid_plural)
      VALUES
	 (:sid, :pid,
          :translator_comments, :extracted_comments, :referencies, :flags, 
          :previous_msgctxt, :previous_msgid, :previous_msgid_plural)
    ");

    // get_translation_id
    $this->queries['get_translation_id'] = $this->dbh->prepare("
      SELECT tid FROM l10n_suggestions_translations
      WHERE sid = :sid AND hash = :hash
    ");

    // insert_translation
    $this->queries['insert_translation'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_translations
	 (sid, lng, translation, hash, count, uid, time)
      VALUES
	 (:sid, :lng, :translation, :hash, :count, :uid, :time)
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
    $pid = $this->queries['insert_project']->execute($params);

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
    $fid = $this->queries['insert_file']->execute($params);

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
    $params = array(':hash' => sha1(trim($string)));
    $this->queries['get_string_id']->execute($params);
    $row = $this->queries['get_string_id']->fetch();
    $sid = isset($row['sid']) ? $row['sid'] : null;

    return $sid;
  }

  /**
   * Insert a new string and return its id.
   */
  public function insert_string($string, $context)
  {
    $params = array(
		    ':string' => $string,
		    ':context' => $context,
		    ':hash' => sha1(trim($string)),
		    ':uid' => 1,   //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_string']->execute($params);
    $sid = $this->dbh->lastInsertId();

    return $sid;
  }

  /** Return the id of a location. */
  public function get_location_id($pid, $sid)
  {
    $params = array(
		    ':pid' => $pid,
		    ':sid' => $sid,
		    );
    $this->queries['get_location_id']->execute($params);
    $row = $this->queries['get_location_id']->fetch();
    $lid = isset($row['lid']) ? $row['lid'] : null;

    return $lid;
  }

  /** Insert a location into DB. */
  public function insert_location($pid, $sid, $entry)
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
		    ':sid' => $sid,
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
  public function get_translation_id($sid, $translation)
  {
    $params = array(
		    ':sid' => $sid,
		    ':hash' => sha1(trim($translation)),
		    );
    $this->queries['get_translation_id']->execute($params);
    $row = $this->queries['get_translation_id']->fetch();
    $tid = isset($row['tid']) ? $row['tid'] : null;

    return $tid;
  }

  /** Insert a translation into DB. */
  public function insert_translation($sid, $lng, $translation)
  {
    $params = array(
		    ':sid' => $sid,
		    ':lng' => $lng,
		    ':translation' => $translation,
		    ':hash' => sha1(trim($translation)),
		    ':count' => 0,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_translation']->execute($params);
    $tid = $this->dbh->lastInsertId();

    return $tid;
  }

  public function exec($query)
  {
    return $this->dbh->exec($query);
  }
}
?>
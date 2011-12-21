<?php
class DB_PO_Export
{
  /** Keeps the DB handler/connection. */
  private $dbh;

  public function __construct()
  {
    $this->connect();
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

  /**
   * Get and return the id of a project.
   */
  public function get_project_id($project, $origin)
  {
    $get_project_id = $this->dbh->prepare("
      SELECT pid FROM l10n_suggestions_projects
      WHERE project = :project AND origin = :origin
    ");
    $params = array(':project' => $project, ':origin' => $origin);
    $get_project_id->execute($params);

    $row = $get_project_id->fetch();
    $pid = isset($row['pid']) ? $row['pid'] : null;

    return $pid;
  }

  /**
   * Get and return the headers of a file.
   */
  public function get_file_headers($pid, $lng)
  {
    $get_file_headers = $this->dbh->prepare("
      SELECT headers FROM l10n_suggestions_files
      WHERE pid = :pid AND lng = :lng
    ");
    $params = array(':pid' => $pid, ':lng' => $lng);
    $get_file_headers->execute($params);

    $row = $get_file_headers->fetch();
    $headers = isset($row['headers']) ? $row['headers'] : null;

    return $headers;
  }

  /**
   * Get and return an array of strings, indexed by sguid.
   */
  public function get_strings($pid)
  {
    $get_strings = $this->dbh->prepare("
      SELECT l.sguid, s.string, s.context,
	     translator_comments, extracted_comments, referencies, flags,
	     previous_msgctxt, previous_msgid, previous_msgid_plural
      FROM l10n_suggestions_locations l
      LEFT JOIN l10n_suggestions_strings s ON (s.sguid = l.sguid)
      WHERE l.pid = :pid
    ");
    $params = array(':pid' => $pid);
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
  public function get_best_translations($pid, $lng)
  {
    $get_best_translations = $this->dbh->prepare("
      SELECT t2.sguid, t2.translation
      FROM (SELECT t1.sguid, t1.translation, MAX(t1.count) AS max_count
	      FROM l10n_suggestions_locations AS l1
	      LEFT JOIN l10n_suggestions_translations AS t1
		    ON (t1.sguid = l1.sguid AND t1.lng = :lng)
	      WHERE l1.pid = :pid
	      GROUP BY t1.sguid
	   ) AS m
      LEFT JOIN l10n_suggestions_translations AS t2
	    ON (t2.sguid = m.sguid AND t2.lng = :lng AND t2.count = m.max_count)
      GROUP BY t2.sguid
    ");
    $params = array(':pid' => $pid, ':lng' => $lng);
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
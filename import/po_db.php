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
    // get_string_id
    $this->queries['get_string_id'] = $this->dbh->prepare("
      SELECT sid FROM l10n_suggestions_strings WHERE hash = :hash
    ");

    // insert_string
    $this->queries['insert_string'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_strings
	 (string, hash, uid_entered, time_entered)
      VALUES
	 (:string, :hash, :uid, :time)
    ");

    // insert_location
    $this->queries['insert_location'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_locations
	 (sid, projectname)
      VALUES
	 (:sid, :project)
    ");

    // insert_translation
    $this->queries['insert_translation'] = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_translations
	 (sid, lng, translation, hash, vcount, uid_entered, time_entered)
      VALUES
	 (:sid, :lng, :translation, :hash, :vcount, :uid, :time)
    ");
  }

  /**
   * Run the query get_string_id and return
   * the id of the string (NULL if not found).
   */
  public function get_string_id($string)
  {
    $params = array(':hash' => sha1(trim($string)));
    $this->queries['get_string_id']->execute($params);
    $row = $this->queries['get_string_id']->fetch();
    $sid = isset($row['sid']) ? $row['sid'] : null;
    return $sid;
  }

  /**
   * Insert a string into DB.
   * Return the id of the new record.
   */
  public function insert_string($string)
  {
    $params = array(
		    ':string' => $string,
		    ':hash' => sha1(trim($string)),
		    ':uid' => 1,   //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_string']->execute($params);
    return $this->dbh->lastInsertId();
  }

  /**
   * Insert a location into DB.
   * Return the id of the new record.
   */
  public function insert_location($sid, $project)
  {
    $params = array(
		    ':sid' => $sid,
		    ':project' => $project,
		    );
    $this->queries['insert_location']->execute($params);
    return $this->dbh->lastInsertId();
  }

  /**
   * Insert a translation into DB.
   * Return the id of the new record.
   */
  public function insert_translation($sid, $lng, $translation)
  {
    $params = array(
		    ':sid' => $sid,
		    ':lng' => $lng,
		    ':translation' => $translation,
		    ':hash' => sha1(trim($translation)),
		    ':vcount' => 0,
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $this->queries['insert_translation']->execute($params);
    return $this->dbh->lastInsertId();
  }
}

?>
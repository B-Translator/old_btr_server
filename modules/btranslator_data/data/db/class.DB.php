<?php
class DB
{
  /** Keeps the DB handler/connection. */
  protected $dbh;

  /** Keeps an associated array of prepared queries. */
  protected $queries = array();

  /** Timestamp of inserting data. */
  protected $time;

  public function __construct()
  {
    $this->connect();
    $this->prepare_queries();
    $this->time = date('Y-m-d H:i:s');
  }

  /** Create a DB connection. */
  protected function connect()
  {
    // Get the DB connection parameters.
    @include_once(dirname(__FILE__).'/settings.php');

    // Create a DB connection.
    $DSN = "$dbdriver:host=$dbhost;dbname=$dbname";
    //print "$DSN\n";  exit(0);  //debug

    $options = array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8");
    if (defined('PDO::MYSQL_ATTR_MAX_BUFFER_SIZE'))
      {
	// Set buffer limit to 15M.
	// (Check also MySQL max_allowed_packet setting.
	//  http://dev.mysql.com/doc/refman/5.0/en/program-variables.html )
	$options[PDO::MYSQL_ATTR_MAX_BUFFER_SIZE] = 15*1024*1024;
      }
    $this->dbh = new PDO($DSN, $dbuser, $dbpass, $options);
  }

  /**
   * Prepare the queries that will be used and store them in $this->queries[] .
   */
  protected function prepare_queries()
  {
  }

  /**
   * Execute the given SQL command and return the number of the
   * affected rows.
   */
  public function exec($sql)
  {
    return $this->dbh->exec($sql);
  }

  /**
   * Execute the given query with the given params
   * and return the result.
   */
  public function query($query, $params)
  {
    $stmt = $this->dbh->prepare($query);
    $stmt->execute($params);
    return $stmt;
  }
}
?>
<?php

include(dirname(dirname(__FILE__)) . '/db/class.DB.php');

class DB_Snapshot extends DB
{
  private function delete_snapshot($origin, $project, $lng)
  {
    $delete_snapshot = $this->dbh->prepare("
      DELETE FROM l10n_suggestions_snapshots
      WHERE pguid = :pguid AND lng = :lng
    ");
    $params = array(
		    ':pguid' => sha1($origin . $project),
		    ':lng' => $lng,
		    );
    $delete_snapshot->execute($params);
  }

  public function insert_snapshot($origin, $project, $lng, $file)
  {
    // Delete it first (in case that it exists).
    $this->delete_snapshot($origin, $project, $lng);

    $insert_snapshot = $this->dbh->prepare("
      INSERT INTO l10n_suggestions_snapshots
	 (pguid, lng, snapshot, uid, time)
      VALUES
	 (:pguid, :lng, :snapshot, :uid, :time)
    ");
    $params = array(
		    ':pguid' => sha1($origin . $project),
		    ':lng' => $lng,
		    ':snapshot' => file_get_contents($file),
		    ':uid' => 1, //admin
		    ':time' => $this->time,
		    );
    $insert_snapshot->execute($params);
  }

  /**
   * Update the snapshot with the content of the file.
   */
  public function update_snapshot($origin, $project, $lng, $file)
  {
    $update_snapshot = $this->dbh->prepare("
      UPDATE l10n_suggestions_snapshots
      SET snapshot = :snapshot, uid = :uid, time = :time
      WHERE pguid = :pguid AND lng = :lng
    ");
    $params = array(
		    ':pguid' => sha1($origin . $project),
		    ':lng' => $lng,
		    ':snapshot' => file_get_contents($file),
		    ':uid' => 1,  //admin
		    ':time' => $this->time,
		    );
    $update_snapshot->execute($params);
  }

  /**
   * Get the snapshot and save it on the given file.
   */
  public function get_snapshot($origin, $project, $lng, $file)
  {
    $get_snapshot = $this->dbh->prepare("
      SELECT snapshot FROM l10n_suggestions_snapshots
      WHERE pguid = :pguid AND lng = :lng
    ");
    $pguid = sha1($origin . $project);
    $params = array(':pguid' => $pguid, ':lng' => $lng);
    $get_snapshot->execute($params);

    $row = $get_snapshot->fetch();
    if (isset($row['snapshot'])) {
      file_put_contents($file, $row['snapshot']);
    }
  }
}
?>
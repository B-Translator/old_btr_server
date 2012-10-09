<?php

include(dirname(dirname(__FILE__)) . '/db/class.DB.php');

class DB_PO_Diff extends DB
{
  /**
   * Return the latest revision number for a project-language.
   */
  private function get_max_nr($origin, $project, $lng)
  {
    $get_max_nr = $this->dbh->prepare("
      SELECT MAX(nr) AS max_nr FROM l10n_feedback_diffs
      WHERE pguid = :pguid AND lng = :lng
    ");
    $pguid = sha1($origin . $project);
    $params = array(':pguid' => $pguid, ':lng' => $lng);
    $get_max_nr->execute($params);

    $row = $get_max_nr->fetch();
    $max_nr = isset($row['max_nr']) ? $row['max_nr'] : 0;

    return $max_nr;
  }

  public function insert_diff($origin, $project, $lng, $file_diff, $file_ediff, $comment =NULL, $uid =NULL)
  {
    // get the revision number
    $nr = $this->get_max_nr($origin, $project, $lng);
    $nr++;

    $insert_diff = $this->dbh->prepare("
      INSERT INTO l10n_feedback_diffs
	 (pguid, lng, nr, diff, ediff, comment, uid, time)
      VALUES
	 (:pguid, :lng, :nr, :diff, :ediff, :comment, :uid, :time)
    ");
    $params = array(
		    ':pguid' => sha1($origin . $project),
		    ':lng' => $lng,
		    ':nr' => $nr,
		    ':diff' => file_get_contents($file_diff),
		    ':ediff' => file_get_contents($file_ediff),
		    ':comment' => $comment,
		    ':uid' => $uid,
		    ':time' => $this->time,
		    );
    $insert_diff->execute($params);
  }

  /**
   * Return a list of diffs for the given project-language,
   * as an array of arrays.
   */
  public function get_diff_list($origin, $project, $lng)
  {
    $get_diff_list = $this->dbh->prepare("
      SELECT nr, time, comment FROM l10n_feedback_diffs
      WHERE pguid = :pguid AND lng = :lng
      ORDER BY time ASC
    ");
    $pguid = sha1($origin . $project);
    $params = array(':pguid' => $pguid, ':lng' => $lng);
    $get_diff_list->execute($params);

    $diff_list = $get_diff_list->fetchAll(PDO::FETCH_NUM);

    return $diff_list;
  }

  /**
   * Get and return the content of the specified diff.
   */
  public function get_diff($origin, $project, $lng, $nr, $format)
  {
    $diff_field = ($format=='ediff' ? 'ediff' : 'diff');
    $get_diff = $this->dbh->prepare("
      SELECT $diff_field FROM l10n_feedback_diffs
      WHERE pguid = :pguid AND lng = :lng AND nr = :nr
      ORDER BY time ASC
    ");
    $pguid = sha1($origin . $project);
    $params = array(':pguid' => $pguid, ':lng' => $lng, ':nr' => $nr);
    $get_diff->execute($params);

    $row = $get_diff->fetch();
    $diff = isset($row[$diff_field]) ? $row[$diff_field] : NULL;

    return $diff;
  }
}
?>
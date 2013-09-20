<?php

/**
 * It is called when a new user account is created.
 */
function btr_user_insert($umail, $ulng, $uid, $name, $status) {

  $db = $GLOBALS['btr_db'];

  $args = array(
    ':umail' => $umail,
    ':ulng' => $ulng,
  );
  $select_user = "
    SELECT * FROM {btr_users}
    WHERE umail = :umail AND ulng = :ulng
  ";
  $result = $db->query($select_user, $args);

  $args[':uid'] = $uid;
  $args[':name'] = $name;

  if ($result->rowCount() > 0) {
    btr_user_update($ulng, $uid, $name, $status);
    $update_user = "
      UPDATE {btr_users}
      SET uid = :uid, name = :name, status = 1
      WHERE umail = :umail AND ulng = :ulng
    ";
    $db->query($update_user, $args);
  }
  else {
    $insert_user = "
      INSERT INTO {btr_users} (umail, ulng, uid, name, status)
      VALUES (:umail, :ulng, :uid, :name, 1)
    ";
    $db->query($insert_user, $args);
  }
}


/**
 * It is called after a user account has been updated.
 */
function btr_user_update($ulng, $uid, $name, $status) {
  $args = array(
    ':ulng' => $ulng,
    ':uid' => $uid,
    ':name' => $name,
    ':status' => $status,
  );
  $update_user = "
    UPDATE {btr_users}
    SET name = :name, status = :status
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['btr_db']->query($update_user, $args);
}

/**
 * It is called when a user is cancelled or deleted.
 */
function btr_user_disable($ulng, $uid) {
  $args = array(':ulng' => $ulng, ':uid' => $uid);
  $update_user = "
    UPDATE {btr_users}
    SET status = 0
    WHERE uid = :uid AND :ulng = ulng
  ";
  $GLOBALS['btr_db']->query($update_user, $args);
}

/**
 * It is used while cleaning fake (spam) users.
 */
function btr_user_delete($ulng, $uid) {
  $db = $GLOBALS['btr_db'];
  $db->delete('btr_users')
    ->condition('ulng', $ulng)
    ->condition('uid', $uid)
    ->execute();
}

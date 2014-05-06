<?php
/**
 * Used for debug.
 */

/**
 * Implements hook_boot().
 *
 * Outputs debug information to the file: /tmp/btr.log
 */
function btrCore_boot() {
  function _btrCore_log($var, $comment ='') {
    $file = '/tmp/btr.log';
    $content = "\n==> $comment: " . print_r($var, true);
    file_put_contents($file, $content, FILE_APPEND);
  }

  _btrCore_log('= = = = = = = = = = = = = = = = = = = = = = =');
  _btrCore_log($_GET, '$_GET');
  _btrCore_log($_POST, '$_POST');
  //_btrCore_log($_COOKIE, '$_COOKIE');

  if (isset($_SESSION['oauth2_client'])) {
    _btrCore_log($_SESSION['oauth2_client'], '$_SESSION[oauth2_client]');
  }
  /*
  if (isset($_SESSION['btrCore'])) {
    _btrCore_log($_SESSION['btrCore'], '$_SESSION[btrCore]');
  }
  if (isset($_SESSION['btrServices'])) {
    _btrCore_log($_SESSION['btrServices'], '$_SESSION[btrServices]');
  }
  if (isset($_SESSION['btr'])) {
    _btrCore_log($_SESSION['btr'], '$_SESSION[btr]');
  }
  */
}

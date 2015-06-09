<?php
/**
 * @file
 */

/**
 * A class that is used to autoload library functions.
 *
 * If the function btr::some_function_name() is called, this class
 * will convert it into a call to the function
 * 'BTranslator\some_function_name()'. If such a function is not
 * declared then it will try to load these files (in this order):
 *   - fn/some_function_name.php
 *   - fn/some_function.php
 *   - fn/some.php
 *   - fn/some/function_name.php
 *   - fn/some/function.php
 *   - fn/some/function/name.php
 * The first file that is found will be loaded (with require_once()).
 *
 * For the big functions it makes more sense to declare each one of them in a
 * separate file, and for the small functions it makes more sense to declare
 * several of them in the same file (which is named as the common prefix of
 * these functions). If there is a big number of functions, it can be more
 * suitable to organize them in subdirectories.
 *
 * See: http://stackoverflow.com/questions/4737199/autoloader-for-functions
 */
class btr {
  /**
   * Make it TRUE to output debug info on '/tmp/btr.log'.
   */
  const DEBUG = FALSE;

  /**
   * The namespace of the functions.
   */
  const NS = 'BTranslator';

  /**
   * Relative directory where the functions are located.
   */
  const FN = 'fn';

  private function __construct() {}
  private function __wakeup() {}
  private function __clone() {}

  /**
   * Return the full name (with namespace) of the function to be called.
   */
  protected static function function_name($function) {
    return self::NS . '\\' . $function;
  }

  /**
   * Return the full path of the file to be loaded (with require_once).
   */
  protected static function file($fname) {
    return dirname(__FILE__) . '/' . self::FN . '/' . $fname . '.php';
  }

  /**
   * If a function does not exist, try to load it from the proper file.
   */
  public static function __callStatic($function, $args) {
    $btr_function = self::function_name($function);
    if (!function_exists($btr_function)) {
      self::log_var($btr_function, 'Autoload');
      // Try to load the file that contains the function.
      if (!self::load_search_dirs($function) or !function_exists($btr_function)) {
        $dir = dirname(self::file($fname));
        $dir = str_replace(DRUPAL_ROOT, '', $dir);
        self::log_var("Raising an exception.\n", 'Not found');
        throw new Exception("Function $btr_function could not be found on $dir");
      }
    }
    return call_user_func_array($btr_function, $args);
  }

  /**
   * Try to load files from subdirectories
   * (by replacing '_' with '/' in the function name).
   */
  protected static function load_search_dirs($fname) {
    do {
      self::log_file($fname);
      if (file_exists(self::file($fname))) {
        self::log_var("Loading.\n", 'Found');
        require_once(self::file($fname));
        return TRUE;
      }
      if (self::load_search_files($fname)) {
        return TRUE;
      }
      $fname1 = $fname;
      $fname = preg_replace('#_#', '/', $fname, 1);
    } while ($fname != $fname1);

    return FALSE;
  }

  /**
   * Try to load files from different file names
   * (by removing the part after the last undescore in the function name).
   */
  protected static function load_search_files($fname) {
    $fname1 = $fname;
    $fname = preg_replace('/_[^_]*$/', '', $fname);
    while ($fname != $fname1) {
      self::log_file($fname);
      if (file_exists(self::file($fname))) {
        self::log_var("Loading.\n", 'Found');
        require_once(self::file($fname));
        return TRUE;
      }
      $fname1 = $fname;
      $fname = preg_replace('/_[^_]*$/', '', $fname);
    }

    return FALSE;
  }

  /**
   * Output the given parameter to a log file (useful for debugging).
   */
  public static function log($var, $comment ='') {
    $file = '/tmp/btr.log';
    $content = "\n==> $comment: " . print_r($var, true);
    file_put_contents($file, $content, FILE_APPEND);
  }

  /**
   * Output the given parameter to a log file (useful for debugging).
   */
  protected static function log_var($var, $comment ='') {
    if (!self::DEBUG)  return;
    self::log($var, $comment);
  }

  /**
   * Debug the order in which the files are tried to be loaded.
   */
  protected static function log_file($fname, $comment = 'Trying') {
    if (!self::DEBUG)  return;
    $file = self::file($fname);
    $file = str_replace(DRUPAL_ROOT, '', $file);
    self::log($file, $comment);
  }
}

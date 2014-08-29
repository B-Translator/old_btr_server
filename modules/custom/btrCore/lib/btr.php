<?php
/**
 * A class that is used to autoload library functions.
 *
 * If the function btr::some_function_name() is called, this class
 * will convert it into a call to the function
 * 'BTranslator\some_function_name()'. If such a function is not
 * declared then it will try to load first the file
 * 'fn/some_function_name.php' and then call it. But if such a file
 * does not exist, then the files 'fn/some_function.php' and
 * 'fn/some.php' will be tried.
 *
 * For the big functions it makes more sense to declare each one of
 * them in a separate file,and for the small functions it makes more
 * sense to declare several of them in the same file (which is named
 * as the common prefix of these files).
 *
 * See: http://stackoverflow.com/questions/4737199/autoloader-for-functions
 */
class btr {
  private function __construct() {}
  private function __wakeup() {}
  private function __clone() {}

  protected static function function_name($function) {
    return 'BTranslator\\' . $function;
  }

  protected static function file($fname) {
    return dirname(__FILE__) . '/fn/' . $fname . '.php';
  }

  /**
   * If a function does not exist, try to load it.
   */
  public static function __callStatic($function, $args) {
    $btr_function = self::function_name($function);
    if (!function_exists($btr_function)) {
      $fname = $function;
      while (!file_exists(self::file($fname))) {
	$fname = preg_replace('/_[^_]*$/', '', $fname);
      }
      if (file_exists(self::file($fname))) {
	require_once(self::file($fname));
      }
      else {
	// Output an error message.
      }
    }
    return call_user_func_array($btr_function, $args);
  }
}
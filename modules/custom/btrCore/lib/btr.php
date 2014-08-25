<?php
/**
 * A class that is used to autoload library functions.
 *
 * See: http://stackoverflow.com/questions/4737199/autoloader-for-functions
 */
class btr {
  private function __construct() {}
  private function __wakeup() {}
  private function __clone() {}

  /**
   * If a function does not exist, try to load it.
   */
  public static function __callStatic($fn, $args) {
    if (!function_exists("BTranslator\\$fn")) {
      module_load_include('php', 'btrCore', "lib/fn/$fn");
    }
    return call_user_func_array("BTranslator\\$fn", $args);
  }
}
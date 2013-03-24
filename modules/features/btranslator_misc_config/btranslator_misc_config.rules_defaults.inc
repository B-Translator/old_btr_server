<?php
/**
 * @file
 * btranslator_misc_config.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function btranslator_misc_config_default_rules_configuration() {
  $items = array();
  $items['rules_redirect_user_to_the_dashboard_on_login'] = entity_import('rules_config', '{ "rules_redirect_user_to_the_dashboard_on_login" : {
      "LABEL" : "Redirect user to the Dashboard on Login",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_login" ],
      "DO" : [ { "redirect" : { "url" : "user\\/login?destination=dashboard" } } ]
    }
  }');
  return $items;
}

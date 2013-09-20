<?php
/**
 * @file
 * btr_btr.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function btr_btr_default_rules_configuration() {
  $items = array();
  $items['rules_assign_contributor_role'] = entity_import('rules_config', '{ "rules_assign_contributor_role" : {
      "LABEL" : "Assign contributor role",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "role", "user" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_insert" ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "4" : "4" } } } }
      ]
    }
  }');
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

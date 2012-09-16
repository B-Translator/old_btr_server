<?php
/**
 * Implements hook_default_rules_configuration().
 *
 * http://drupal.org/node/884584
 * http://drupalcontrib.org/api/drupal/contributions%21rules%21rules.api.php/function/hook_default_rules_configuration/7
 * http://drupalcontrib.org/api/drupal/contributions%21rules%21rules.module/function/rules_import/7
 */
function l10n_feedback_default_rules_configuration() {
  // When a new user is registered, the role contributor is assigned
  // to him automatically. Without this role the user will not be able
  // to vote or make suggestions, so for the time being we assign it
  // automatically to each registered user.
  // The rule configuration is exported from the Rules UI.
  $role = user_role_load_by_name('contributor');
  $rid = $role->rid;
  $rules_assign_contributor_role = '{ "rules_assign_contributor_role" : {
    "LABEL" : "Assign contributor role",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "role", "user" ],
    "REQUIRES" : [ "rules" ],
    "ON" : [ "user_insert" ],
    "DO" : [
      { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "' . $rid . '" : "' . $rid . '" } } } }
    ]
  }
}';
  $configs['rules_assign_contributor_role'] = rules_import($rules_assign_contributor_role);

  return $configs;
}
?>
<?php
/**
 * @file
 * btr_btrServices.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function btr_btrServices_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_default_oauth2_server().
 */
function btr_btrServices_default_oauth2_server() {
  $items = array();
  $items['oauth2_btr'] = entity_import('oauth2_server', '{
    "name" : "oauth2_btr",
    "label" : "OAuth2 B-Translator",
    "settings" : {
      "enforce_state" : true,
      "default_scope" : "basic",
      "allow_implicit" : 1,
      "grant_types" : {
        "authorization_code" : "authorization_code",
        "client_credentials" : "client_credentials",
        "refresh_token" : "refresh_token",
        "password" : "password"
      },
      "always_issue_new_refresh_token" : 0,
      "access_lifetime" : "3600",
      "refresh_token_lifetime" : "1209600",
      "require_exact_redirect_uri" : 1
    },
    "rdf_mapping" : [],
    "scopes" : [ { "name" : "basic", "description" : "Basic", "rdf_mapping" : [] } ]
  }');
  return $items;
}

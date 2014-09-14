<?php
   /**
    * Modifies the configuration of a B-Translator site
    * that is installed for development. Not required,
    * but sometimes can be useful.
    *
    * Call it like this:
    *     drush [@alias] php-script config.php [tag]
    */

$tag = drush_shift();
if ($tag == '')  $tag = 'dev';

// append ($tag) to site_name
variable_set('site_name', "B-Translator ($tag)");

$site_mail = variable_get('site_mail');

function update_emails() {
  // make site email something like 'user+tag@gmail.com'
  global $site_mail, $tag;
  if (preg_match('/@gmail.com/', $site_mail)) {
    $email = preg_replace('/@gmail.com/', "+$tag@gmail.com", $site_mail);
    variable_set('site_mail', $email);
    variable_set('smtp_from', $email);
    variable_set('mimemail_mail', $email);
    variable_set('simplenews_from_address', $email);
    variable_set('simplenews_test_address', $email);
    variable_set('mass_contact_default_sender_email', $email);
    variable_set('reroute_email_address', $email);
    variable_set('update_notify_emails', array($email));
  }
}

function enable_email_rerouting() {
  variable_set('reroute_email_enable', 1);
  variable_set('reroute_email_enable_message', 1);
}

function create_test_users() {
  $new_user = array(
    'name' => 'user0',
    'mail' => preg_replace('/@gmail.com/', '+user0@gmail.com', $site_mail),
    'pass' => 'user0',
    'status' => 1,
    'init' => 'email address',
    'roles' => array(
      DRUPAL_AUTHENTICATED_RID => 'authenticated user',
    ),
  );
  user_save(null, $new_user);

  $new_user['name'] = 'user2';
  $new_user['pass'] = 'user2';
  $new_user['mail'] = preg_replace('/@gmail.com/', '+user2@gmail.com', $site_mail);
  user_save(null, $new_user);
}

function show_devel_menu_on_footer() {
  $blocks = array(
    array(
      'module' => 'menu',
      'delta'  => 'devel',
      'region' => 'footer',
      'status' => 1,
      'weight' => -15,
      'cache'  => DRUPAL_NO_CACHE,
    ),
  );
  $default_theme = variable_get('theme_default', 'bartik');

  foreach ($blocks as $block) {
    extract($block);
    db_update('block')
      ->fields(array(
          'status' => $status,
          'region' => $region,
          'weight' => $weight,
          'cache'  => $cache,
        ))
      ->condition('module', $module)
      ->condition('delta', $delta)
      ->condition('theme', $default_theme)
      ->execute();
  }
}

function create_oauth2_clients() {
  $client = entity_create('oauth2_server_client', array());
  $client->server = 'oauth2_btr';
  $client->label = 'Test 1';
  $client->client_key = 'test1';
  $client->client_secret = 'test1';
  $client->redirect_uri = url('oauth2/authorized', array('absolute' => TRUE));
  $client->automatic_authorization = TRUE;
  $client->save();

  $client = entity_create('oauth2_server_client', array());
  $client->server = 'oauth2_btr';
  $client->label = 'Test 2';
  $client->client_key = 'test2';
  $client->client_secret = 'test2';
  $client->redirect_uri = url('oauth2/authorized', array('absolute' => TRUE));
  $client->automatic_authorization = FALSE;
  $client->save();
}

function create_oauth2_scopes() {
    $scopes = array(
      'scope1' => 'Scope 1',
      'scope2' => 'Scope 2',
      'scope3' => 'Scope 3',
    );
    foreach ($scopes as $scope_name => $scope_label) {
      $scope = entity_create('oauth2_server_scope', array());
      $scope->server = 'oauth2_btr';
      $scope->name = $scope_name;
      $scope->description = '';
      $scope->save();
    }
}


switch ($tag) {
  default:
  case 'dev':
    update_emails();
    enable_email_rerouting();
    create_test_users();
    show_devel_menu_on_footer();
    create_oauth2_clients();
    create_oauth2_scopes();
    break;

  case 'test':
    update_emails();
    enable_email_rerouting();
    // disable sending review emails
    include dirname(__FILE__).'/disable_email_option.php';
    break;
}

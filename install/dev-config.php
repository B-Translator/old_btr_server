<?php
// add DEV before site_name and site_slogan
$site_name = variable_get('site_name');
$site_name = preg_replace('#^DEV / #', '', $site_name);
variable_set('site_name', "DEV / $site_name");

// enable email re-routing (for development/testing)
$site_mail = variable_get('site_mail');
variable_set('reroute_email_enable', 1);
variable_set('reroute_email_address', $site_mail);

// add a few test users
if (preg_match('/@gmail.com/', $site_mail))
  {
    $new_user = array(
      'name' => 'user1',
      'mail' => preg_replace('/@gmail.com/', '+user1@gmail.com', $site_mail),
      'pass' => 'user1',
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

// disable logo and favicon of the theme bartik
$theme_bartik_settings = variable_get('theme_bartik_settings');
$theme_bartik_settings['toggle_logo'] = 0;
$theme_bartik_settings['toggle_favicon'] = 0;
variable_set('theme_bartik_settings', $theme_bartik_settings);

// smtp
variable_set('smtp_on', true);
variable_set('smtp_allowhtml', true);
variable_set('smtp_library', 'profiles/btranslator/modules/smtp/smtp.module');
variable_set('smtp_fromname', $site_name);
variable_set('smtp_from', $site_mail);
variable_set('smtp_host', 'smtp.googlemail.com');
variable_set('smtp_protocol', 'ssl');
variable_set('smtp_port', '465');

// get the gmail password of site_mail, to be used for smtp
print("Enter the Gmail password for $site_mail: ");
system('stty -echo');
$password = trim(fgets(STDIN));
system('stty echo');
// add a new line since the users CR didn't echo
echo "\n";

variable_set('smtp_username', $site_mail);
variable_set('smtp_password', $password);

// date and time
variable_set('configurable_timezones', true);
variable_set('contact_default_status', 1);
variable_set('date_default_timezone', 'Europe/Tirane');
variable_set('date_first_day', 1);
//variable_set('site_default_country', 'AL');

// disqus
variable_set('disqus_developer', true);
variable_set('disqus_domain', 'btranslator-dev');
variable_set('disqus_inherit_login', true);
variable_set('disqus_location', 'content_area');
variable_set('disqus_nodetypes',
  array(
    'blog' => 'blog',
    'article' => 'article',
    'book' => 'book',
  ));
variable_set('disqus_userapikey', 'jY36xKWOn1MibB0RiZ2zonErZfEx0q6h0SF9Ht5zwsAP0dSFpSBKNSufLfiTsI6x');
variable_set('disqus_weight', 100);

// blocks
$blocks = array(
  // disable 'Powered by Drupal'
  array(
    'module' => 'system',
    'delta'  => 'powered-by',
    'region' => '-1',
    'status' => 0,
    'weight' => 0,
    'cache'  => DRUPAL_CACHE_GLOBAL,
  ),

  // show the devel menu on the footer
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

// cron
variable_set('cron_safe_threshold', 0);   //disable internal cron
$cron_key = variable_get('cron_key');
drush_print("cron_key='$cron_key'");

?>
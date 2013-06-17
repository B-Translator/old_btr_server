#!/bin/bash -x

# Protect Drupal settings from prying eyes
drupal_settings=/var/www/btranslator/sites/default/settings.php
chown root:www-data $drupal_settings
chmod 640 $drupal_settings

# Modify Drupal settings
cat >> $drupal_settings << EOF
/**
 * Disable Poor Man's Cron:
 *
 * Drupal 7 enables the built-in Poor Man's Cron by default.
 * Poor Man's Cron relies on site activity to trigger Drupal's cron,
 * and is not well suited for low activity websites.
 *
 * We will use the Linux system cron and override Poor Man's Cron
 * by setting the cron_safe_threshold to 0.
 *
 * To re-enable Poor Man's Cron:
 *    Comment out (add a leading hash sign) the line below,
 *    and the system cron in /etc/cron.d/drupal7.
 */
\$conf['cron_safe_threshold'] = 0;

\$base_url = "https://l10n.org.xx";

/*
\$conf['fb_api_file'] = 'profiles/btranslator/libraries/facebook-php-sdk/src/facebook.php';
include "profiles/btranslator/modules/contrib/fb/fb_url_rewrite.inc";
include "profiles/btranslator/modules/contrib/fb/fb_settings.inc";
if (!headers_sent()) {
  header('P3P: CP="We do not have a P3P policy."');
}
*/

// Adds memcache as a cache backend
\$conf['cache_backends'][] = 'profiles/btranslator/modules/contrib/memcache/memcache.inc';
// Makes it so that memcache is the default caching backend
\$conf['cache_default_class'] = 'MemCacheDrupal';
// Keep forms in persistent storage, as per discussed at the beginning
\$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
// I don't see any point in keeping the module update information in Memcached
\$conf['cache_class_cache_update'] = 'DrupalDatabaseCache';

// Specify the memcache servers you wish to use and assign them to a cluster
// Cluster = group of memcache servers, in our case, it's probably just one server per cluster.
\$conf['memcache_servers'] = array('unix:///var/run/memcached/memcached.sock' => 'default');
// This assigns all cache bins to the 'default' cluster from above
\$conf['memcache_bins'] = array('cache' => 'default');

// If you wanted multiple Drupal installations to share one Memcache instance use the prefix like so:
\$conf['memcache_key_prefix'] = 'btranslator';

EOF

### update to the latest version of core and modules
drush --yes pm-update

### install features modules
drush --yes pm-enable btranslator_l10n_feedback
drush --yes pm-enable btranslator_btranslator
drush --yes pm-enable btranslator_misc
drush --yes pm-enable btranslator_layout
drush --yes pm-enable btranslator_content
drush --yes pm-enable btranslator_disqus
drush --yes pm-enable btranslator_sharethis
drush --yes pm-enable btranslator_captcha
drush --yes pm-enable btranslator_invite
drush --yes pm-enable btranslator_permissions
#drush --yes pm-enable btranslator_simplenews
#drush --yes pm-enable btranslator_mass_contact
#drush --yes pm-enable btranslator_googleanalytics
#drush --yes pm-enable btranslator_drupalchat
#drush --yes pm-enable btranslator_fb
#drush --yes pm-enable btranslator_janrain

### install also multi-language support
#drush --yes pm-enable l10n_client l10n_update
#mkdir -p sites/all/translations
#chown -R www-data: sites/all/translations


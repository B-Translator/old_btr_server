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

# disable powered-by Drupal block on all themes
mysql -e "USE btranslator; UPDATE block SET status = '0' WHERE ( module = 'system' AND delta = 'powered-by' );"

# aggregate and compress CSS and JS files (for performance)
drush vset preprocess_css 1
drush vset preprocess_js 1

# set some other drupal vars
drush vset l10n_feedback_export_path '/var/www/exports'
drush vset l10n_feedback_preferred_projects 'test'


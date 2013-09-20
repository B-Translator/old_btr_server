#!/bin/bash -x

# Protect Drupal settings from prying eyes
drupal_settings=/var/www/btr/sites/default/settings.php
chown root:www-data $drupal_settings
chmod 640 $drupal_settings

### Modify Drupal settings

# diable poor man's cron
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

EOF

# set base_url
cat >> $drupal_settings << EOF
\$base_url = "https://l10n.org.xx";

EOF

# set the memcache configuration
cat >> $drupal_settings << EOF
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
drush --yes pm-enable btr_btr_ui
drush --yes features-revert btr_btr_ui

drush --yes pm-enable btr_btr
drush --yes features-revert btr_btr

drush --yes pm-enable btr_misc
drush --yes features-revert btr_misc

drush --yes pm-enable btr_layout
drush --yes features-revert btr_layout

drush --yes pm-enable btr_disqus
drush --yes pm-enable btr_content
drush --yes pm-enable btr_sharethis

drush --yes pm-enable btr_captcha
drush --yes features-revert btr_captcha
drush vset recaptcha_private_key 6LenROISAAAAAM-bbCjtdRMbNN02w368ScK3ShK0
drush vset recaptcha_public_key 6LenROISAAAAAH9roYsyHLzGaDQr76lhDZcm92gG

drush --yes pm-enable btr_invite
drush --yes pm-enable btr_permissions

#drush --yes pm-enable btr_simplenews
#drush --yes pm-enable btr_mass_contact
#drush --yes pm-enable btr_googleanalytics
#drush --yes pm-enable btr_drupalchat
#drush --yes pm-enable btr_janrain

### install FB integration
#drush --yes pm-enable btr_fb

# enable FB config
cat >> $drupal_settings << EOF
/* fb config
\$conf['fb_api_file'] = 'profiles/btranslator/libraries/facebook-php-sdk/src/facebook.php';
include "profiles/btranslator/modules/contrib/fb/fb_url_rewrite.inc";
include "profiles/btranslator/modules/contrib/fb/fb_settings.inc";
if (!headers_sent()) {
  header('P3P: CP="We do not have a P3P policy."');
}
fb config */

EOF
#sed -i $drupal_settings \
#    -e '#^/*fb config# c // /* fb config' \
#    -e '#^fb config */# c // fb config */'

### install also multi-language support
drush --yes pm-enable l10n_client l10n_update
mkdir -p /var/www/btr/sites/all/translations
chown -R www-data: /var/www/btr/sites/all/translations
drush --yes l10n-update
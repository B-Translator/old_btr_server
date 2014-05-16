#!/bin/bash -x

### prevent robots from crawling translations
sed -i $drupal_dir/robots.txt \
    -e '/# B-Translator/,$ d'
cat <<EOF >> $drupal_dir/robots.txt
# B-Translator
Disallow: /translations/
Disallow: /?q=translations/
Disallow: /fb_cb/
Disallow: /?q=fb_cb/
Disallow: /downloads/
EOF

# Protect Drupal settings from prying eyes
drupal_settings=$drupal_dir/sites/default/settings.php
chown root:www-data $drupal_settings
chmod 640 $drupal_settings

### Modify Drupal settings

# disable poor man's cron
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
\$base_url = "https://btr.example.org";

EOF

# set the memcache configuration
cat >> $drupal_settings << EOF
// Adds memcache as a cache backend
/* comment memcache config
\$conf['cache_backends'][] = 'profiles/btr_server/modules/contrib/memcache/memcache.inc';
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
\$conf['memcache_key_prefix'] = 'btr_server';
comment memcache config */

EOF

### set the directory for uploads
### $drush is an alias for 'drush --root=/var/www/btr'
mkdir -p /var/www/uploads/
chown www-data: /var/www/uploads/
$drush variable-set file_private_path '/var/www/uploads/' --exact --yes

### install multi-language support
$drush --yes pm-enable l10n_update
mkdir -p $drupal_dir/sites/all/translations
chown -R www-data: $drupal_dir/sites/all/translations

### set the list of languages for import
sed -i /var/www/data/config.sh \
    -e "/^languages=/c languages=\"$languages\""

### add these languages to drupal and import their translations
for lng in $languages
do
    $drush language-add $lng
done
$drush --yes l10n-update

### update to the latest version of core and modules
#$drush --yes pm-update

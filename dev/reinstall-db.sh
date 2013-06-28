#!/bin/bash
### Reinstall the Drupal profile 'btranslator' and its features.
### This script touches only the database of Drupal (btranslator)
### and nothing else. Useful for testing the features.
###
### Usually, when features are un-installed, things are not undone
### properly. To leave out a feature, it should not be installed
### since the beginning. So, it is important to test them.

### start mysqld manually, if it is not running
if test -z "$(ps ax | grep [m]ysqld)"
then
    nohup mysqld --user mysql >/dev/null 2>/dev/null &
    sleep 5  # give time mysqld to start
fi

### settings for the database and the drupal site
appdir="/var/www/btranslator"
db_name=btranslator
db_user=btranslator
db_pass=btranslator
site_name="B-Translator"
site_mail="admin@example.com"
account_name=admin
account_pass=admin
account_mail="admin@example.com"

### create the database and user
mysql='mysql --defaults-file=/etc/mysql/debian.cnf'
$mysql -e "
    DROP DATABASE IF EXISTS $db_name;
    CREATE DATABASE $db_name;
    GRANT ALL ON $db_name.* TO $db_user@localhost IDENTIFIED BY '$db_pass';
"

### start site installation
sed -e '/memory_limit/ c memory_limit = -1' -i /etc/php5/cli/php.ini
cd $appdir
drush site-install --verbose --yes btranslator \
      --db-url="mysql://$db_user:$db_pass@localhost/$db_name" \
      --site-name="$site_name" --site-mail="$site_mail" \
      --account-name="$account_name" --account-pass="$account_pass" --account-mail="$account_mail"

### install features modules
drush --yes pm-enable btranslator_l10n_feedback
drush --yes features-revert btranslator_l10n_feedback

drush --yes pm-enable btranslator_btranslator
drush --yes features-revert btranslator_btranslator

drush --yes pm-enable btranslator_misc
drush --yes features-revert btranslator_misc

drush --yes pm-enable btranslator_layout
drush --yes features-revert btranslator_layout

drush --yes pm-enable btranslator_disqus
drush --yes pm-enable btranslator_content
drush --yes pm-enable btranslator_sharethis

drush --yes pm-enable btranslator_captcha
drush --yes features-revert btranslator_captcha
drush vset recaptcha_private_key 6LenROISAAAAAM-bbCjtdRMbNN02w368ScK3ShK0
drush vset recaptcha_public_key 6LenROISAAAAAH9roYsyHLzGaDQr76lhDZcm92gG

drush --yes pm-enable btranslator_invite
drush --yes pm-enable btranslator_permissions

#drush --yes pm-enable btranslator_simplenews
#drush --yes pm-enable btranslator_mass_contact
#drush --yes pm-enable btranslator_googleanalytics
#drush --yes pm-enable btranslator_drupalchat
#drush --yes pm-enable btranslator_janrain

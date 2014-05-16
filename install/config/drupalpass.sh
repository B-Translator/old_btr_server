#!/bin/bash
### Set the admin password of Drupal.

### get a password for the Drupal user 'admin'
if [ -z "${btr_admin_passwd+xxx}" -o "$btr_admin_passwd" = '' ]
then
    base_url=$(drush @bcl eval 'print $GLOBALS["base_url"]')
    echo
    echo "===> Password for Drupal 'admin' on $base_url."
    echo
    stty -echo
    read -p "Enter the password: " btr_admin_passwd
    stty echo
    echo
fi

### set the password
$(dirname $0)/mysqld.sh start
drush @btr user-password admin --password="$btr_admin_passwd"

### drush may create css/js files with wrong(root) permissions
rm -rf /var/www/btr/sites/default/files/css/
rm -rf /var/www/btr/sites/default/files/js/

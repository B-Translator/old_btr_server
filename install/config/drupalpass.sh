#!/bin/bash
### Set the admin password of Drupal.

### get a password for the Drupal user 'admin'
if [ -z "${btr_admin_passwd+xxx}" -o "$btr_admin_passwd" = '' ]
then
    base_url=$(drush @btr eval 'print $GLOBALS["base_url"]')
    echo
    echo "===> Password for Drupal 'admin' on $base_url."
    echo
    stty -echo
    read -p "Enter the password: " btr_admin_passwd
    stty echo
    echo
fi

### set the password
drush @btr user-password admin --password="$btr_admin_passwd"

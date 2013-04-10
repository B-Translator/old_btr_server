#!/bin/bash
### Set the admin password of Drupal.

echo "
===> Please enter new password for the Drupal 'admin' account.
"
stty -echo
read -p "Enter the password: " passwd
stty echo
echo

service mysql start
drush user-password admin --password="$passwd"

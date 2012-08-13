#!/bin/bash
### This script is sourced from other install scripts.
### It assumes that $app_dir, $db_name, $db_user, $db_pass
### etc. are already defined and have the correct values
### that are to be saved.

cat <<EOF > btranslator-config.sh
### directory where application is installed
app_dir=$app_dir

### DB parameters
db_name=$db_name
db_user=$db_user
db_pass=$db_pass

### application settings
site_name="$site_name"
site_mail="$site_mail"
account_name="$account_name"
account_pass="$account_pass"
account_mail="$account_mail"
EOF
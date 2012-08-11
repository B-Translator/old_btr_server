#!/bin/bash
### install the profile btranslator

### get the directory of the installation scripts
scripts=$(dirname $0)

### get the site cofiguration settings
. $scripts/config.sh

### confirm/modify the settings
echo "Give site-name, site-email, account-name, account-pass and account-mail."
read -p "site-name [$site_name]: " sitename
sitename=${sitename:-$site_name}
read -p "site-mail [$site_mail]: " sitemail
sitemail=${sitemail:-$site_mail}
read -p "account-name [$account_name]: " accountname
accountname=${accountname:-$account_name}
read -p "account-pass [$account_pass]: " accountpass
accountpass=${accountpass:-$account_pass}
read -p "account-mail [$account_mail]: " accountmail
accountmail=${accountmail:-$account_mail}

### save application settings to the configuration file
site_name="$sitename"
site_mail="$sitemail"
account_name="$accountname"
account_pass="$accountpass"
account_mail="$accountmail"
. $scripts/save.sh

### go to the application directory
cd $app_dir
set -x  ### switch on debugging

### start site installation
drush site-install btranslator  \
      --db-url="mysql://$db_user:$db_pass@localhost/$db_name" \
      --site-name="$site_name" --site-mail="$site_mail" \
      --account-name="$account_name" --account-pass="$account_pass" --account-mail="$account_mail"

### set propper directory permissions
mkdir -p sites/default/files/
sudo chown -R www-data: sites/default/files/
mkdir -p cache/
sudo chown -R www-data: cache/

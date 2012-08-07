#!/bin/bash

### check the parameter
if [ "$1" = '' ]
then
  echo "Usage: $0 output_dir"
  echo "Example: $0 test1"
  exit 1
fi

### get the directory name
output_dir=$1
if [ -d $output_dir ]
then
  echo "Directory $output_dir already exists..."
  exit 1
fi

set -x  ## start debugging

### make sure that all needed packages are installed
sudo apt-get install aptitude tasksel
sudo tasksel install lamp-server
sudo aptitude install phpmyadmin php5-curl php-apc
sudo aptitude install drush php-pear gawk git mercurial subversion translate-toolkit

### make sure that we have drush-4 (drush-5 still has some problems with 'make')
sudo pear channel-discover pear.drush.org
sudo pear upgrade drush/drush-4.6.0

### install drush_make
if [ ! -d ~/.drush/drush_make ]
then
   mkdir -p ~/.drush
   cd ~/.drush/
   wget http://ftp.drupal.org/files/projects/drush_make-6.x-2.3.tar.gz
   tar xfz drush_make-6.x-2.3.tar.gz
fi

### get pology (used for making embedded diffs)
if [ ! -d /usr/local/lib/pology ]
then
   svn checkout svn://anonsvn.kde.org/home/kde/trunk/l10n-support/pology /usr/local/lib/pology
fi

### get all the required files and modules
drush make --working-copy "https://raw.github.com/dashohoxha/B-Translator/master/distro.make" $output_dir
### for developing make files, comment the line above and use the following one
#drush make --working-copy /var/www/B-Translator/distro.make $output_dir

set +x  ## stop debugging

### create a test database
echo
echo "===> Creating the database."
echo
echo "Give dbname, dbuser and dbpass."
read -p "dbname [test1]: " dbname
dbname=${dbname:-test1}
read -p "dbuser [test1]: " dbuser
dbuser=${dbuser:-test1}
read -p "dbpass [test1]: " dbpass
dbpass=${dbpass:-test1}

mysql_commands="
    DROP DATABASE IF EXISTS $dbname;
    CREATE DATABASE $dbname;
    GRANT ALL ON $dbname.* TO $dbuser@localhost IDENTIFIED BY '$dbpass';
"
echo "$mysql_commands"
echo "Enter the mysql root password below."
echo "$mysql_commands" | mysql -u root -p


### install the profile btranslator
echo
echo "===> Installing the profile btranslator."
echo

echo "Give site-name, site-email, account-name, account-pass and account-mail."
read -p "site-name [B-Translator]: " site_name
site_name=${site_name:-"B-Translator"}
read -p "site-mail [admin@example.com]: " site_mail
site_mail=${site_mail:-"admin@example.com"}
read -p "account-name [admin]: " account_name
account_name=${account_name:-"admin"}
read -p "account-pass [admin]: " account_pass
account_pass=${account_pass:-"admin"}
read -p "account-mail [$site_mail]: " account_mail
account_mail=${account_mail:-$site_mail}


cd $output_dir

### start site installation
drush site-install btranslator  \
      --db-url="mysql://$dbuser:$dbpass@localhost/$dbname" \
      --site-name="$site_name" --site-mail="$site_mail" \
      --account-name="$account_name" --account-pass="$account_pass" --account-mail="$account_mail"

### set propper directory permissions
mkdir -p sites/default/files/
sudo chown -R www-data: sites/default/files/
mkdir -p cache/
sudo chown -R www-data: cache/

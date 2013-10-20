#!/bin/bash -x

function install
{
    apt-get -y \
	-o DPkg::Options::=--force-confdef \
	-o DPkg::Options::=--force-confold \
	install $@
}

### set a temporary hostname
sed -i /etc/hosts \
    -e "/^127.0.0.1/c 127.0.0.1 localhost l10n.org.xx"
hostname l10n.org.xx

### install and upgrade packages
apt-get update
apt-get -y upgrade

### install other needed packages
install aptitude tasksel vim nano psmisc language-pack-en
install mysql-server ssmtp memcached php5-memcached \
        php5-mysql php5-gd php-db php5-dev make php-pear php5-curl php-apc \
        ssl-cert gawk unzip wget diff curl phpmyadmin \
        git mercurial subversion translate-toolkit
install screen logwatch

### phpmyadmin will install apache2 and start it
### so we should stop and disable it
service apache2 stop
update-rc.d apache2 disable

### install nginx and php5-fpm
install nginx nginx-common nginx-full php5-fpm

# install uploadprogress bar (from PECL) (requested by Drupal 7)
pecl install uploadprogress
echo "extension = uploadprogress.so" > /etc/php5/conf.d/uploadprogress.ini

### install drush
pear channel-discover pear.drush.org
pear install pear.drush.org/drush-5.8.0

### get pology (used for making embedded diffs)
rm -rf /usr/local/lib/pology
svn checkout svn://anonsvn.kde.org/home/kde/trunk/l10n-support/pology /usr/local/lib/pology

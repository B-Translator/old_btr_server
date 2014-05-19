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
    -e "/^127.0.0.1/c 127.0.0.1 example.org localhost"
hostname example.org

### install and upgrade packages
apt-get update
apt-get -y upgrade

### install other needed packages
install aptitude tasksel vim nano psmisc language-pack-en
install mysql-server ssmtp memcached php5-memcached \
        php5-mysql php5-gd php-db php5-dev make php-pear php5-curl php-apc \
        ssl-cert gawk unzip wget diff curl phpmyadmin \
        git mercurial subversion translate-toolkit ruby dtrx
install screen logwatch

### install hub: http://hub.github.com/
curl http://hub.github.com/standalone -sLo /bin/hub
chmod +x /bin/hub

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
pear install pear.drush.org/drush-6.2.0.0

### get pology (used for making embedded diffs)
rm -rf /usr/local/lib/pology
svn checkout svn://anonsvn.kde.org/home/kde/trunk/l10n-support/pology /usr/local/lib/pology

### get a local copy of btr_client
### code_dir=/var/www/code and install.sh
### has placed a copy of btr_server there
git clone $bcl_git_repo $code_dir/btr_client
cd $code_dir/btr_client
git checkout $bcl_version

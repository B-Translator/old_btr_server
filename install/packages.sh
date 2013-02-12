#!/bin/bash -x

### make sure that all needed packages are installed
apt-get install aptitude tasksel
tasksel install lamp-server
aptitude install phpmyadmin php5-curl php-apc php5-memcached
aptitude install gawk git mercurial subversion translate-toolkit

### make sure that we have drush-4 (drush-5 still has some problems with 'make')
aptitude install php-pear
pear channel-discover pear.drush.org
pear install pear.drush.org/drush-4.6.0

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

### install additional apache2 modules
a2enmod ssl headers rewrite


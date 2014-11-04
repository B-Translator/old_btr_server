#!/bin/bash -x

### make a clone of /var/www/btr to /var/www/btr_dev
/usr/local/src/btr_server/dev/clone.sh btr btr_dev

### comment out the configuration of the database 'btr_db' so that
### the internal test database can be used instead for translations
sed -i /var/www/btr_dev/sites/default/settings.php \
    -e '/$databases..btr_db/,+8 s#^/*#//#'

### modify sites.inc
btr_server=/var/www/btr/profiles/btr_server
sed -i $btr_server/modules/custom/btrCore/includes/sites.inc \
    -e "/^function btr_get_sites()/,/^}/ s/$bcl_domain/dev.$bcl_domain/"

### add a test user
drush @btr_dev user-create user1 --password=user1 \
      --mail='user1@example.org' > /dev/null 2>&1

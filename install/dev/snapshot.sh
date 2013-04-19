#!/bin/bash
### Make a backup of the current state of the
### application (filesystem, database, etc.)
### Restore a previous backup/snapshot.
###
### Can be useful when trying new things on Drupal
### that can possibly break the application.
### Sometimes this can be better/faster than installing
### the application from scratch.

function usage {
    echo "
 * Usage: $(basename $0) [ make | restore snapshot_file.tgz ]

   Make a backup of the current state of the
   application (filesystem, database, etc.)
   Restore a previous backup/snapshot.

   Can be useful when trying new things on Drupal
   that can possibly break the application.
   Sometimes this can be better/faster than installing
   the application from scratch.
"
    exit 0
}

case $1 in 
    make)
	# create the snapshot dir
	snapshot="snapshot-$(date +%Y%m%d)"
	rm -rf $snapshot
	rm -f $snapshot.tgz
	mkdir $snapshot

	# clear all drupal cache
	drush cache-clear all

	# copy to the snapshot dir the files and the database dump
	cp -a /var/www/btranslator $snapshot/
	mysqldump --defaults-file=/etc/mysql/debian.cnf \
                  --opt --add-drop-database \
                  --databases btranslator > $snapshot/btranslator.sql

	# create an archive
	tar cfz $snapshot.tgz $snapshot
	rm -rf $snapshot/
	;;

    restore)
	# check the validity of the second argument
	test "$2" = '' && usage
	test -f $2 || usage

	# extract the archive
	tar xfz $2
	snapshot=${2%.tgz}

	# restore the database
	mysql --defaults-file=/etc/mysql/debian.cnf < $snapshot/btranslator.sql
	
	# restore drupal files
	# however make sure that the files
	# that are managed by git are not replaced

	umount /var/www/btranslator/cache
	mv /var/www/btranslator{,-del}
	mv $snapshot/btranslator /var/www/
	mount -a

	mv /var/www/btranslator/profiles/btranslator{,-old}
	cp -a /var/www/btranslator{-del,}/profiles/btranslator

	profile_dir=/var/www/btranslator/profiles/btranslator
	for subdir in libraries modules/{contrib,libraries} themes/contrib
	do
	    rm -rf $profile_dir/$subdir
	    cp -a $profile_dir{-old,}/$subdir
	done

	# clean up
	rm -rf $snapshot
	rm -rf /var/www/btranslator-del
	rm -rf /var/www/btranslator/profiles/btranslator-old
	;;

    *)
	usage
	;;
esac




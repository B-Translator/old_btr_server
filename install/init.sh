#!/bin/bash

CHROOT=/var/chroot/btranslator

HOST_SERVICES="mysql apache2"
CHROOT_SERVICES="php5-fpm memcached mysql nginx"
MOUNT_POINTS="proc dev sys dev/pts"

### reverse a list of words given as parameter
function reverse {
    list_of_words=$1
    reversed_list=''
    for word in $list_of_words
    do
	reversed_list="$word $reversed_list"
    done
    echo $reversed_list
}

case "$1" in
    start)
	# stop the services on the host
	for SRV in $(reverse "$HOST_SERVICES")
	do
	    service $SRV stop
	done

	# mount /proc etc. to the CHROOT
	for DIR in $MOUNT_POINTS
	do
	    mount -o bind /$DIR $CHROOT/$DIR
	done

	# start the services inside the CHROOT
	for SRV in $CHROOT_SERVICES
	do
	    chroot $CHROOT/ service $SRV start
	done
	;;

    stop)
	# stop the services inside the CHROOT
	for SRV in $(reverse "$CHROOT_SERVICES")
	do
	    chroot $CHROOT/ service $SRV stop
	done

	# umount /proc etc. from the CHROOT
	for DIR in $(reverse "$MOUNT_POINTS")
	do
	    umount $CHROOT/$DIR
	done

	# start the services on the host
	for SRV in $HOST_SERVICES
	do
	    service $SRV start
	done
	;;
    *)
	echo " * Usage: $0 {start|stop}"
esac

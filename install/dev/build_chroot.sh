#!/bin/bash -x
### build a chroot environment for testing

CHROOT=/var/chroot/btranslator
archive=http://archive.ubuntu.com/ubuntu/
distro=precise

### install debootstrap dchroot
apt-get install -y debootstrap dchroot

### modify the config file
file_conf=/etc/schroot/schroot.conf
if ! grep -q -e "^\[$distro\]" $file_conf
then
    echo " 
[$distro]
description=Ubuntu Precise LTS
location=$CHROOT
priority=3
users=ubuntu
groups=sbuild
root-groups=root
" >> $file_conf
fi

### bootstrap a minimal system
debootstrap --variant=minbase $distro $CHROOT $archive

### setup resolv.conf and sources.list
cp /etc/resolv.conf $CHROOT/etc/resolv.conf
cat <<EOF > $CHROOT/etc/apt/sources.list
deb http://archive.ubuntu.com/ubuntu precise main
deb http://archive.ubuntu.com/ubuntu precise-updates main
deb http://security.ubuntu.com/ubuntu precise-security main
deb http://archive.ubuntu.com/ubuntu precise universe
deb http://archive.ubuntu.com/ubuntu precise-updates universe
EOF

### install a minimal ubuntu
mount -o bind /proc $CHROOT/proc
chroot $CHROOT apt-get install ubuntu-minimal -y
chroot $CHROOT apt-get update
chroot $CHROOT apt-get upgrade -y

### install additinal packages and LAMP
chroot $CHROOT apt-get install -y language-pack-en-base vim
chroot $CHROOT apt-get install -y aptitude tasksel
service apache2 stop
servive mysql stop
chroot $CHROOT tasksel install lamp-server

### make a startup script
echo "
CHROOT=$CHROOT
" > /etc/init.d/chroot-btranslator
cat <<EOF >>/etc/init.d/chroot-btranslator
case "$1" in
    start)
	service apache2 stop
	service mysql stop

	mount -o bind /proc $CHROOT/proc
	mount -o bind /dev $CHROOT/dev
	mount -o bind /sys $CHROOT/sys
	mount -o bind /dev/pts $CHROOT/dev/pts

	chroot $CHROOT/  service mysql start
	chroot $CHROOT/  service apache2 start
	;;

    stop)
	chroot $CHROOT/  service apache2 stop
	chroot $CHROOT/  service mysql stop

	umount $CHROOT/dev/pts
	umount $CHROOT/sys
	umount $CHROOT/dev
	umount $CHROOT/proc

	service mysql start
	service apache2 start
	;;
esac
EOF

### make it executable and start it at boot
chmod +x /etc/init.d/chroot-btranslator
update-rc.d chroot-btranslator defaults

### stop the services inside the CHROOT
chroot $CHROOT service apache2 stop
chroot $CHROOT service mysql stop
umount $CHROOT/proc
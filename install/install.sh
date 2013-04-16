#!/bin/bash
### Install a new chrooted B-Translator server
### from scratch, with debootstrap.

target_dir=${1:-btranslator}

arch=i386
suite=precise
apt_mirror=http://archive.ubuntu.com/ubuntu

### install debootstrap dchroot
apt-get install -y debootstrap dchroot

### install a minimal system
export DEBIAN_FRONTEND=noninteractive
debootstrap --variant=minbase --arch=$arch $suite $target_dir $apt_mirror

cat <<EOF > $target_dir/etc/apt/sources.list
deb http://archive.ubuntu.com/ubuntu precise main restricted universe multiverse
deb http://archive.ubuntu.com/ubuntu precise-updates main restricted universe multiverse
deb http://security.ubuntu.com/ubuntu precise-security main restricted universe multiverse
EOF

cp /etc/resolv.conf $target_dir/etc/resolv.conf
mount -o bind /proc $target_dir/proc
chroot $target_dir apt-get update
chroot $target_dir apt-get -y install ubuntu-minimal


### apply to chroot the scripts and the overlay
cwd=$(dirname $0)
chroot $target_dir mkdir -p /tmp/install
cp -a $cwd/* $target_dir/tmp/install/
chroot $target_dir /tmp/install/install-scripts/00-config.sh
chroot $target_dir /tmp/install/config.sh
chroot $target_dir rm -rf /tmp/install

### shutdown services
services="php5-fpm memcached mysql nginx"
for srv in $services
do
    chroot $target_dir service $srv stop
done

umount $target_dir/proc

### make an init script and start it at boot
cd $target_dir
chroot_dir=$(pwd)
cd $cwd
init_script="/etc/init.d/chroot-$(basename $target_dir)"
sed -e "/^CHROOT=/c CHROOT='$chroot_dir'" $cwd/init.sh > $init_script
chmod +x $init_script
update-rc.d $(basename $init_script) defaults

#!/bin/bash
### Install a new chrooted B-Translator server
### from scratch, with debootstrap.

target_dir=${1:-btranslator}

arch=i386
suite=precise
apt_mirror=http://archive.ubuntu.com/ubuntu

### install a minimal system
export DEBIAN_FRONTEND=noninteractive
debootstrap --variant=minbase --arch=$arch $suite $target_dir $apt_mirror

cat <<EOF > $target_dir/etc/apt/sources.list
deb http://archive.ubuntu.com/ubuntu precise main restricted universe multiverse
deb http://security.ubuntu.com/ubuntu precise-security main restricted universe multiverse
EOF

cp /etc/resolv.conf $target_dir/etc/resolv.conf
mount -o bind /proc $target_dir/proc
chroot $target_dir apt-get update
chroot $target_dir apt-get -y install ubuntu-minimal


### apply to chroot the scripts and the overlay
cwd=$(dirname $0)
chroot $target_dir mkdir -p /tmp/server-patch
cp -a $cwd/* $target_dir/tmp/server-patch/
chroot $target_dir /tmp/server-patch/scripts/00-config.sh
chroot $target_dir rm -rf /tmp/server-patch

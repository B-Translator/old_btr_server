#!/bin/bash
### Install a new chrooted B-Translator server
### from scratch, with debootstrap and tklpatch.

function usage
{
  echo "Usage: $0 [suite]
where 'suite' can be: precise (default), squeeze, etc."
}

suite=${1:-precise}
arch=i386

case $suite in
    precise )
        apt_mirror=http://archive.ubuntu.com/ubuntu
        ;;
    squeeze )
        apt_mirror=http://ftp.debian.org/debian
        ;;
    * )
        usage
        ;;
esac

target_dir=$suite

### install a minimal system
export DEBIAN_FRONTEND=noninteractive
debootstrap --variant=minbase --arch=$arch $suite $target_dir $apt_mirror
cp /etc/resolv.conf $target_dir/etc/resolv.conf
mount -o bind /proc $target_dir/proc
chroot $target_dir apt-get update
if [ $suite = 'precise' ]
then
    chroot $target_dir apt-get -y install ubuntu-minimal
fi

### install tklpatch
# #wget http://archive.turnkeylinux.org/debian/pool/squeeze/main/t/tklpatch/tklpatch_0.93%2b10%2bg4c48672_all.deb deb/
# tklpatch_deb=deb/tklpatch_0.93+10+g4c48672_all.deb
# cp $tklpatch_deb $target_dir/
# chroot $target_dir/ apt-get install -y tar gzip squashfs-tools genisoimage
# chroot $target_dir/ dpkg -i $tklpatch_deb
# rm $target_dir/$tklpatch_deb
######## tklpatch can also be installed manually on the host system

### apply the core patch
cwd=$(dirname $0)
tklpatch_dir="$cwd/patch-tklcore-$suite"
cp -TdR $tklpatch_dir/overlay/etc/apt/ $target_dir/etc/apt/
tklpatch-apply $target_dir $tklpatch_dir


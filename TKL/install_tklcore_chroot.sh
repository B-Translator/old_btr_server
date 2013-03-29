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

case $suite:
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

target_dir=/var/chroot/$suite

### install a minimal system
debootstrap --variant=minbase --arch=$arch $suite $target_dir $apt_mirror
cp /etc/resolv.conf $target_dir/etc/resolv.conf
mount -o bind /proc $target_dir/proc
chroot $target_dir apt-get update
if [ $suite = 'precise' ]
then
    chroot $target_dir apt-get install ubuntu-minimal
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
tklpatch_dir=patch_tklcore_$suite
tklpatch-apply $target_dir $tklpatch_dir


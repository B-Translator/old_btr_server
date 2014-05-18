#!/bin/bash
### Install a new chrooted server from scratch, with debootstrap.

function usage {
    echo "
Usage: $0 [OPTIONS] <settings> [options]
Install B-Translator inside a chroot in the target directory.

    <settings>    file of installation/configuration settings
    --target=D    target dir where the system will be installed
    --arch=A      set the architecture to install (default i386)
    --suite=S     system to be installed (default precise)
    --mirror=M    source of the apt packages
                  (default http://archive.ubuntu.com/ubuntu)
    --opt_name=V  override any settings in the config file
"
    exit 0
}

### get the options
for opt in "$@"
do
    case $opt in
	--target=*)    target_dir=${opt#*=} ;;
	--arch=*)      arch=${opt#*=} ;;
	--suite=*)     suite=${opt#*=} ;;
	--mirror=*)    apt_mirror=${opt#*=} ;;
	-h|--help)     usage ;;
        --*=*)
	    optvalue=${opt#*=}
	    optname=${opt%%=*}
	    optname=${optname:2}
	    eval export $optname="$optvalue"
	    ;;
	*)
	    if [ ${opt:0:1} = '-' ]; then usage; fi

	    settings=$opt
	    if ! test -f "$settings"
            then
		echo "File '$settings' does not exist."
		exit 1
	    fi
	    set -a;  source $settings;  set +a
	    ;;
    esac
done

### check that there was at least one settings file
if [ "$settings" = '' ]
then
    echo
    echo "Error: No settings file was given."
    usage
fi

### install debootstrap dchroot
apt-get install -y debootstrap dchroot

### install a minimal system
export DEBIAN_FRONTEND=noninteractive
debootstrap --variant=minbase --arch=$arch $suite $target_dir $apt_mirror

cat <<EOF > $target_dir/etc/apt/sources.list
deb $apt_mirror $suite main restricted universe multiverse
deb $apt_mirror $suite-updates main restricted universe multiverse
deb http://security.ubuntu.com/ubuntu $suite-security main restricted universe multiverse
EOF

cp /etc/resolv.conf $target_dir/etc/resolv.conf
mount -o bind /proc $target_dir/proc
chroot $target_dir apt-get update
chroot $target_dir apt-get -y install ubuntu-minimal

### stop any services that may get into the way
### of installing services inside the chroot
for SRV in apache2 nginx mysql
do service $SRV stop; done

### apply to chroot the scripts and the overlay
install_dir=$(dirname $0)
chroot $target_dir mkdir -p /tmp/install
cp -a $install_dir/* $target_dir/tmp/install/
cp -f $settings $target_dir/tmp/install/settings.sh
chroot $target_dir /tmp/install/install-scripts/00-install.sh

### create an init script
current_dir=$(pwd)
cd $target_dir
chroot_dir=$(pwd)
cd $current_dir
init_script="/etc/init.d/chroot-$(basename $chroot_dir)"
sed -e "/^CHROOT=/c CHROOT='$chroot_dir'" $install_dir/init.sh > $init_script
chmod +x $init_script

### start the chroot system on boot
service=$(basename $init_script)
update-rc.d $service defaults
if [ "$start_on_boot" = 'true' ]
then
    update-rc.d $service enable
else
    update-rc.d $service disable
fi

### display the name of the chroot on the prompt
echo $(basename $chroot_dir) > $target_dir/etc/debian_chroot

### customize the configuration of the chroot system
chroot $target_dir /tmp/install/config.sh
#chroot $target_dir rm -rf /tmp/install

### stop the services inside chroot
$init_script stop

### reboot
test "$reboot" = 'true' && reboot

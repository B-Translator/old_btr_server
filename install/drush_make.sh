#!/bin/bash
### get all the required files and modules

### get the directory of the installation scripts
scripts=$(dirname $0)

### get the app_dir from the config file
. btranslator-config.sh

### get the application directory
while true
do
    read -p "Enter the application directory [$app_dir]: " appdir
    appdir=${appdir:-$app_dir}
    if [ -d $appdir ]; then echo "Directory '$appdir' already exists..."; else break; fi
done

### save app_dir to the configuration file
app_dir=$appdir
. $scripts/save.sh

### get the git repo path and the current working directory
current_dir=$(pwd)
cd $(dirname $scripts)
gitpath=$(pwd)

### create the branch 'dev' on the local git repo
cd $gitpath
git checkout -b dev
git checkout dev

### create a customized distro.make, which gets the project from the local repository
cd $current_dir
cat <<EOF > btranslator-distro.make
; Include Build Kit distro makefile via URL
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/distro.make
projects[buildkit] = FALSE

projects[btranslator][type] = profile
projects[btranslator][download][type] = git
projects[btranslator][download][url] = $gitpath
projects[btranslator][download][branch] = dev
EOF

### retrieve all the projects/modules and build the application directory
drush make --working-copy --prepare-install --force-complete btranslator-distro.make $appdir

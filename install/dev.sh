#!/bin/bash
### setup the configuration for development/testing

### get the directory of the installation scripts
current_dir=$(pwd)
cd $(dirname $0)
scripts=$(pwd)
cd $current_dir

### get app_dir from the cofiguration settings
. config-btranslator.sh

### go to the application directory
cd $app_dir

### apply the configurations for development
drush php-script $scripts/dev-config.php
#drush php-script $scripts/content-sq.php

#!/bin/bash
$(dirname $0)/mysqld.sh start
drush @btr php-script $(dirname $0)/oauth2_login.php

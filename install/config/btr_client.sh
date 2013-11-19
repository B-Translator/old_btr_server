#!/bin/bash
$(dirname $0)/mysqld.sh start
drush @btr php-script $(dirname $0)/btr_client.php "$(mcookie)"
drush @btr cc all

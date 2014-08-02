#!/bin/bash
### Update all projects at once.

projects="
    /var/www/bcl*/profiles/btr_client
    /var/www/btr*/profiles/btr_server
"
for project in $projects
do
    echo
    echo "===> $project"
    cd $project
    drush vset update_check_disabled 1 -y
    drush up -y
done

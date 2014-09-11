#!/bin/bash
### Useful for updating or checking the status of all git repositories.
### For example:
###    dev/git.sh status --short
###    dev/git.sh pull

options=${@:-status --short}
gitrepos="
    /var/www/bcl*/profiles/btr_client
    /var/www/btr*/profiles/btr_server
    /usr/local/src/btr_*
"
for repo in $gitrepos
do
    echo
    echo "===> $repo"
    cd $repo
    git $options
done

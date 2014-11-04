#!/bin/bash -x
### Removes the btr_server container for a language.

### get the language code
if [ "$1" = '' ]
then
    echo "Usage: $0 lng
The parameter 'lng' is the language code (fr/de/it etc.)
"
    exit 1
fi
lng=$1
container="btr-$lng"

### update the configuration of wsproxy and restart it
rm /data/wsproxy/config/etc/apache2/sites-{available,enabled}/{$lng,btr-$lng}*.conf
sed -i /data/wsproxy/hosts.txt -e "/^$container:/d"
/data/wsproxy/restart.sh

### stop and remove the container
docker stop $container
docker rm $container
rm -rf /data/containers/$container

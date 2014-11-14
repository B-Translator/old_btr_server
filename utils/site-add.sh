#!/bin/bash -x
### Installs a btr_server container for a language
### (which contains both btr_server and btr_client).

### get the language code and the ssh port
if [ "$1" = '' ]
then
    echo "Usage: $0 lng ssh_port

The parameter 'lng' is the language code (fr/de/it etc.)
The 'ssh_port' is the port that should be used to ssh into
the container (something like 22XY, a port not in use by
any other containers).

"
    exit 1
fi
lng=$1
ssh_port=${2:-2201}

### set some variables
container="btr-$lng"
bcl_domain="$lng.btranslator.org"
btr_domain="btr-$lng.btranslator.org"
admin_passwd=$(mcookie | head -c 10)
gmail_account="$lng@btranslator.org"
gmail_passwd=$(mcookie)
languages=$(echo $lng fr de it es | tr ' ' "\n" | sort -u | tr "\n" ' ')


###################### create a new container #######################

### create a directory for sharing data with the host
mkdir -p /data/containers/$container

### create a new container
docker create --name=$container \
    --hostname=$lng.btranslator.org \
    -v /data/containers/$container:/data \
    -v /data/PO_files:/data/PO_files:ro \
    -p $ssh_port:2201 \
    btranslator/btr_server:v2.3
docker start $container

### update drupal and the code of the application
docker exec $container dev/git.sh pull
docker exec $container dev/drush_up.sh


######### customize settings and reconfigure the container ##########

docker exec $container \
    sed -i /usr/local/src/btr_server/install/settings.sh \
        -e "/^domain=/ c domain='$btr_domain'" \
        -e "/^bcl_domain=/ c bcl_domain='$bcl_domain'" \
        -e "/^admin_passwd=/ c admin_passwd='$admin_passwd'" \
        -e "/^bcl_admin_passwd=/ c bcl_admin_passwd='$admin_passwd'" \
        -e "/^gmail_account=/ c gmail_account='$gmail_account'" \
        -e "/^gmail_passwd=/ c gmail_passwd='$gmail_passwd'" \
        -e "/^languages=/ c languages='$languages'" \
        -e "/^translation_lng=/ c translation_lng='$lng'"
docker exec $container dev/clone_rm.sh btr_dev
docker exec $container ../btr_client/dev/clone_rm.sh bcl_dev
docker exec $container install/{config.sh,settings.sh}


############### get the ssh key of the container ####################

docker cp $container:/root/.ssh/id_rsa .
file_rsa=$container.rsa
mv id_rsa $file_rsa
chmod 600 $file_rsa
#gdrive upload -f $file_rsa


################### clean up and restart ############################

docker exec $container \
    killall mysqld
docker exec $container \
    drush @local_btr --yes cc all
docker exec $container \
    drush @local_bcl --yes cc all

docker restart $container


######## update the configuration of wsproxy and restart it #########

### add on wsproxy apache2 config files for the new site
cd /data/wsproxy/config/etc/apache2/sites-available/
for file in $(ls xmp*.conf)
do
    file1=${file/#xmp/$lng}
    file2=${file/#xmp/btr-$lng}
    cp $file $file1
    cp $file $file2
    sed -i $file1 -e "s/example\.org/$lng.btranslator.org/g"
    sed -i $file2 -e "s/example\.org/btr-$lng.btranslator.org/g"
done
cd ../sites-enabled/
ln -s ../sites-available/$lng*.conf .
ln -s ../sites-available/btr-$lng*.conf .
cd /data/

### modify the configuration of wsproxy/hosts.txt
sed -i /data/wsproxy/hosts.txt -e "/^$container:/d"
cat << EOF >> /data/wsproxy/hosts.txt
$container: $lng.btranslator.org dev.$lng.btranslator.org test.$lng.btranslator.org
$container: btr-$lng.btranslator.org dev.btr-$lng.btranslator.org test.btr-$lng.btranslator.org
EOF

### restart wsproxy
/data/wsproxy/restart.sh


####################### import translations #########################

# docker exec $container \
#     /var/www/data/import.sh

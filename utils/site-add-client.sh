#!/bin/bash -x
### Add a new language site.

### get the language code
if [ "$1" = '' ]
then
    echo "Usage: $0 lng ssh_port

The parameter 'lng' is the language code (fr/de/it etc.)
The 'ssh_port' is the port that should be used to ssh into
the container (something like 22XY, a port not in use by
any other containers).

"
    exit (1)
fi
lng=$1
ssh_port=${2:-2201}

### set some variables
container="bcl-$lng"
domain="$lng.btranslator.org"
admin_passwd=$(mcookie | head -c 10)
gmail_account="$lng@btranslator.org"
gmail_passwd=$(mcookie)


###################### create a new container #######################

### create a directory for sharing data with the host
mkdir -p /data/containers/$container

### create a new container
docker create --name=$container --hostname=$domain \
    -v /data/containers/$container:/data -p $ssh_port:2201 \
    btranslator/btr_client:v2.2
docker start $container

### update drupal and the code of the application
docker exec $container dev/git.sh pull
docker exec $container dev/drush_up.sh


################## make configurations for oauth2 ###################

### configuration variables
server_url='https://btranslator.org'
client_id="$domain"
client_secret=$(mcookie)
redirect_url="https://$domain/oauth2/authorized"
skip_ssl=0

### register an oauth2 client on btr_server
docker exec btr \
    drush --yes @btr \
      php-script --script-path=/usr/local/src/btr_server/install/config \
      register_oauth2_client.php "$client_id" "$client_secret" "$redirect_url"
docker exec btr \
    drush @btr cc all

# ### setup oauth2 login on btr_client
# docker exec -it $container \
#     drush --yes @bcl \
#       php-script --script-path=/usr/local/src/btr_client/install/config \
#       oauth2_login.php "$server_url" "$client_id" "$client_secret" "$skip_ssl"
# docker exec -it $container \
#     drush @bcl cc all

### save oauth2 variables on settings.sh
docker exec $container \
    sed -i /usr/local/src/btr_client/install/settings.sh \
        -e "/^oauth2_server_url=/ c oauth2_server_url='$server_url'" \
        -e "/^oauth2_client_id=/ c oauth2_client_id='$client_id'" \
        -e "/^oauth2_client_secret=/ c oauth2_client_secret='$client_secret'"


######### customize settings and reconfigure the container ##########

docker exec $container \
    sed -i /usr/local/src/btr_client/install/settings.sh \
        -e "/^domain=/ c domain='$domain'" \
        -e "/^admin_passwd=/ c admin_passwd='$admin_passwd'" \
        -e "/^gmail_account=/ c gmail_account='$gmail_account'" \
        -e "/^gmail_passwd=/ c gmail_passwd='$gmail_passwd'" \
        -e "/^translation_lng=/ c translation_lng='$lng'"
docker exec $container dev/clone_rm.sh bcl_dev
docker exec $container install/{config.sh,settings.sh}


############### get the ssh key of the container ####################

docker cp $container:/root/.ssh/id_rsa .
file_rsa=$container.rsa
mv id_rsa $file_rsa
chmod 600 $file_rsa
#gdrive upload -f $file_rsa


######## update the configuration of wsproxy and restart it #########

### add on wsproxy apache2 config files for the new site
cd /data/wsproxy/config/etc/apache2/sites-available/
for file in $(ls xmp*.conf)
do
    file1=${file/#xmp/$lng}
    cp $file $file1
    sed -i $file1 -e "s/example\.org/$lng.btranslator.org/g"
done 
cd ../sites-enabled/
ln -s ../sites-available/$lng*.conf .
cd /data/

### modify the configuration of wsproxy/hosts.txt
sed -i /data/wsproxy/hosts.txt -e "/^$container:/d"
cat << EOF >> /data/wsproxy/hosts.txt
$container: $lng.btranslator.org dev.$lng.btranslator.org test.$lng.btranslator.org
EOF

### restart wsproxy
/data/wsproxy/restart.sh


############### modify the configuration of btr #####################

# ### update languages and sites
# docker exec -it btr \
#     vim /var/www/data/config.sh 
# docker exec -it btr \
#     vim /var/www/btr/profiles/btr_server/modules/custom/btrCore/includes/languages.inc 
# docker exec -it btr \
#     vim /var/www/btr/profiles/btr_server/modules/custom/btrCore/includes/sites.inc 
# docker exec -it btr \
#     drush @btr cc all

# ### get and import the translations of the new language
# docker-enter $container
# cd /var/www/data/
# cp config.sh config.sh.bak
# sed -i config.sh -e "/^languages=/ c languages='$lng'"  
# ./get.sh
# ./import.sh
# rm config.sh
# mv config.sh.bak config.sh


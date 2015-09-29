#!/bin/bash -x

source ./config
ssh=${ssh:-2201}

docker stop $container
docker rm $container

if [ "$dev" = 'false' ]
then
    ### create a container for production
    docker create --name=$container --hostname=$hostname \
        -p 80:80 -p 443:443 -p $ssh:$ssh $image
else
    ### create a container for development
    docker create --name=$container $image
    docker start $container
    rm -rf btr_server/ btr_client/
    docker cp $container:/var/www/btr/profiles/btr_server $(pwd)/
    docker cp $container:/var/www/bcl/profiles/btr_client $(pwd)/
    docker stop $container
    docker rm $container

    let ssh1=ssh+1
    docker create --name=$container --hostname=$hostname \
        -v $(pwd)/btr_server:/var/www/btr/profiles/btr_server \
        -v $(pwd)/btr_client:/var/www/bcl/profiles/btr_client \
        -p 81:80 -p 444:443 -p $ssh1:$ssh \
        $image
fi

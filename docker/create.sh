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
    ### remove the directory btr_client/ if it exists
    if test -d btr_client/
    then
        cd btr_client/
        if test -n "$(git status --porcelain)"
        then
            echo "Directory btr_client/ cannot be removed because it has uncommited changes."
            exit 1
        fi
        cd ..
        rm -rf btr_client/
    fi

    ### remove the directory btr_server/ if it exists
    if test -d btr_server/
    then
        cd btr_server/
        if test -n "$(git status --porcelain)"
        then
            echo "Directory btr_server/ cannot be removed because it has uncommited changes."
            exit 1
        fi
        cd ..
        rm -rf btr_server/
    fi

    ### create a container for development
    docker create --name=$container $image
    docker start $container
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

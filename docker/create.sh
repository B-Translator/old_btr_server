#!/bin/bash -x

source ./config

docker stop $container
docker rm $container

### Remove the given directory if it exists.
function remove_dir() {
    local dir=$1
    if test -d $dir/
    then
        cd $dir/
        if test -n "$(git status --porcelain)"
        then
            echo "Directory $dir/ cannot be removed because it has uncommited changes."
            exit 1
        fi
        cd ..
        rm -rf $dir/
    fi
}

if [ "$dev" = 'false' ]
then
    ### create a container for production
    mkdir -p downloads uploads exports
    docker create --name=$container --hostname=$hostname \
        -v /data/PO_files:/var/www/data \
        -v $(pwd)/downloads:/var/www/downloads \
        -v $(pwd)/uploads:/var/www/uploads \
        -v $(pwd)/exports:/var/www/exports \
        $ports $image
else
    ### remove the directories btr_client/ and btr_server/ if they exist
    remove_dir btr_client
    remove_dir btr_server

    ### copy directories btr_client/ and btr_server/ from the image to the host
    docker create --name=$container $image
    docker start $container
    docker cp $container:/var/www/btr/profiles/btr_server $(pwd)/
    docker cp $container:/var/www/bcl/profiles/btr_client $(pwd)/
    docker stop $container
    docker rm $container

    ### create a container for development, sharing diectories
    ### btr_client/ and btr_server/ between the container and the host
    docker create --name=$container --hostname=$hostname \
        -v $(pwd)/btr_server:/var/www/btr/profiles/btr_server \
        -v $(pwd)/btr_client:/var/www/bcl/profiles/btr_client \
        -v /data/PO_files:/var/www/data \
        $ports $image
fi

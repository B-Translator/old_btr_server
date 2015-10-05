#!/bin/bash

source ./config

docker exec -it $container install/config.sh $1

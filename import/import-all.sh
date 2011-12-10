#!/bin/bash

./import.php init

./import-ubuntu.sh
./import-gnome.sh
./import-kde.sh

./import.php done

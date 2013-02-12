#!/bin/bash

### get the directory of the installation scripts
scripts=$(dirname $0)

### get a copy of config.sh on the current directory
if [ ! -f btranslator-config.sh ]
then
    cp $scripts/config.sh config-btranslator.sh
fi

### install the required packages and tools
read -p "Install packages? (Y/n): " answer
if [ "$answer" != 'n' ]
then
    $scripts/packages.sh
fi

### get all the required projects/modules and build the application directory
echo -e "\n--------------------\n"
read -p "Build the application directory? (Y/n): " answer
if [ "$answer" != 'n' ]
then
    $scripts/drush_make.sh
fi

### create the database and the user that will be used by the application
echo -e "\n--------------------\n"
read -p "Create the database? (Y/n): " answer
if [ "$answer" != 'n' ]
then
    $scripts/db.sh
fi

### install the profile btranslator
echo -e "\n--------------------\n"
read -p "Install the profile btranslator? (Y/n): " answer
if [ "$answer" != 'n' ]
then
    $scripts/btranslator.sh
fi

### setup dev configuration
echo -e "\n--------------------\n"
read -p "Setup dev/testing configuration? (Y/n): " answer
if [ "$answer" != 'n' ]
then
    $scripts/dev.sh
fi


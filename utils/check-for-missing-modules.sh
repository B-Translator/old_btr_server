#!/bin/bash
### see: http://timonweb.com/advice-may-help-you-if-your-drupal-7-has-started-run-slowly
### see also this: http://drupal.org/project/clean_missing_modules

site="default"
#site="dev.btranslator.org"
query="SELECT filename FROM system WHERE status = 1"
active_modules=$(drush -l "$site" --extra=--skip-column-names sql-query "$query")

cd $(drush -l "$site" drupal-directory)
for module in $active_modules
do
    ##echo $module;  continue;  # debug
    if [ ! -f $module ]
    then
        echo "Missing $module"
    fi 
done

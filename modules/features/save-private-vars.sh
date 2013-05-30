#!/bin/bash
### Save sensitive/private variables that should not be made public.

echo "Usage: $0 [@drush_alias]"

drush_alias=$1
drush="drush $drush_alias"

cat <<EOF > restore-private-vars.php
<?php
/**
 * Backup of sensitive/private variables, that are specific
 * only for this instance of B-Translator. This file should
 * never be made public.
 */

// define variables
EOF

while read var_name
do
    $drush vget "$var_name" --exact --pipe >> restore-private-vars.php
done < $(dirname $0)/private-vars.txt

cat <<EOF >> restore-private-vars.php

// set variables
foreach (\$variables as \$var_name => \$var_value) {
  variable_set(\$var_name, \$var_value);
}
EOF

echo "
Restore variables with the command:
$drush php-script restore-private-vars.php
"

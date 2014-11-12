#!/bin/bash
### Update the base_url for the given language.

### get the parameters lng and base_url
if [ $# -ne 2 ]
then
    echo "Usage: $0 lng base_url
For example:
    $0 sq https://l10n.org.al
"
    exit 1
fi
lng=$1
base_url=$2

### modify sites.inc
btr_server=/var/www/btr/profiles/btr_server
sed -i $btr_server/modules/custom/btrCore/includes/sites.inc \
    -e '/return array/,/}/ d'
cat << EOF >> $btr_server/modules/custom/btrCore/includes/sites.inc
  return array(
    '$lng' => array(
      'base_url' => '$base_url',
    ),
  );
}
EOF

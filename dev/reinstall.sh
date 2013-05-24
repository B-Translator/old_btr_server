#!/bin/bash
### reinstall btranslator from scratch

mv /var/www/btranslator /var/www/btranslator-bak

cd $(dirname $0)
cd ../install/install-scripts/

./20-make-and-install-btranslator.sh
./25-git-clone-btranslator.sh
./30-separate-translation-data.sh
./40-configure-btranslator.sh

../config.sh


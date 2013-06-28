#!/bin/bash
### Reinstall btranslator from scratch.
### Useful for testing installation scripts.

mv /var/www/btranslator /var/www/btranslator-bak

cd $(dirname $0)
cd ../install/install-scripts/

./20-make-and-install-btranslator.sh
./25-git-clone-btranslator.sh
./30-separate-translation-data.sh

PO_files=/var/www/PO_files
data=/var/www/btranslator_data
ln -sf $PO_files $data/get/
ln -sf $PO_files $data/import/

./40-configure-btranslator.sh

../config.sh


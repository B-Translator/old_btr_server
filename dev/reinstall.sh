#!/bin/bash
### reinstall btranslator from scratch

mv /var/www/btranslator /var/www/btranslator-bak

cd $(dirname $0)

../install-scripts/20-make-and-install-btranslator.sh
../install-scripts/30-separate-translation-data.sh
../install-scripts/40-configure-btranslator.sh

../config.sh


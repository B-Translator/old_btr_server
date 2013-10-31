#!/bin/bash

echo "===== GETTING WordPress ====="

. ./inc.sh
change_dir WordPress

svn_checkout http://svn.automattic.com/wordpress-i18n/sq/tags/3.3.2/ wp-sq
svn_checkout http://svn.automattic.com/wordpress-i18n/fr_FR/tags/3.3/ wp-fr
#svn_checkout http://svn.automattic.com/wordpress-i18n/de_DE/tags/3.3.2/ wp-de
#svn_checkout http://svn.automattic.com/wordpress-i18n/it_IT/tags/3.3.2/ wp-it
#svn_checkout http://svn.automattic.com/wordpress-i18n/sl_SI/tags/3.3/ wp-sl
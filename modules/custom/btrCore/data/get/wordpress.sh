#!/bin/bash

echo "===== GETTING WordPress ====="

. ./inc.sh
change_dir WordPress

svn_checkout http://svn.automattic.com/wordpress-i18n/sq/tags/3.5.2/ wp-sq
svn_checkout http://svn.automattic.com/wordpress-i18n/fr_FR/tags/3.6/ wp-fr
#svn_checkout http://svn.automattic.com/wordpress-i18n/de_DE/tags/3.8/ wp-de
#svn_checkout http://svn.automattic.com/wordpress-i18n/it_IT/tags/3.8/ wp-it
#svn_checkout http://svn.automattic.com/wordpress-i18n/sl_SI/tags/3.8/ wp-sl

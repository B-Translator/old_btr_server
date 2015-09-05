#!/bin/bash
### Update all projects at once.

for dir in /var/www/btr*
do
    echo
    echo "===> $dir"
    cd $dir
    drush vset update_check_disabled 1 -y
    drush pm-refresh
    drush up -y
    cat <<EOF > $dir/robots.txt
User-agent: *
Disallow: /
EOF
done

for dir in /var/www/bcl*
do
    echo
    echo "===> $dir"
    cd $dir
    drush vset update_check_disabled 1 -y
    drush pm-refresh
    drush up -y
    sed -i $dir/robots.txt \
        -e '/# B-Translator/,$ d'
    cat <<EOF >> $dir/robots.txt
# B-Translator
Disallow: /btr/
Disallow: /?q=btr/
Disallow: /translations/
Disallow: /?q=translations/
Disallow: /vocabulary/
Disallow: /?q=vocabulary/
EOF
done

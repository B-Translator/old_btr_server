#!/bin/bash
### Watch the latest Disqus comments for l10n-sq
### and notify the relevant users about them.
### Run it on background like this:
###     utils/watch-comments.php &

cd $(dirname $0)

url='http://l10n-sq.disqus.com/latest.rss'
rsstail="rsstail -u $url -l -d -n 0"
$rsstail | ./watch-comments.php


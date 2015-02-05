#!/bin/bash
### Watch the latest Disqus comments for l10n-sq
### and notify the relevant users about them.

cd $(dirname $0)

url='http://l10n-sq.disqus.com/latest.rss'
#rsstail="rsstail -u $url -1 -l -d -i 15 -n 0"
rsstail="rsstail -u $url -1 -l -d -i 1 -n 2"
$rsstail | ./watch-comments.php


#!/bin/bash
### Send tweets from command line.
### For installation instructions see:
### http://xmodulo.com/2013/12/access-twitter-command-line-linux.html

t='/usr/local/bin/t'
base_url=https://l10n.org.al
tweet="$(wget --no-check-certificate $base_url/translations/twitter/sq -O-)"
mention=$($t following | sort -R | tail -1)
$t update "$tweet @$mention"

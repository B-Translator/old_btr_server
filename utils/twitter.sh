#!/bin/bash
### Send tweets from command line.
### For installation instructions see:
### http://xmodulo.com/2013/12/access-twitter-command-line-linux.html

t='/usr/local/bin/t'
lng=sq
tweet=$(curl -k https://btranslator.org/translations/twitter/$lng)
mention=$($t following | sort -R | tail -1)
$t update "$tweet @$mention"

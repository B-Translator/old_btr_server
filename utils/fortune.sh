#!/bin/bash

fortune='/usr/games/fortune'
t='/usr/local/bin/t'
tweet=$($fortune -s -n 140 25% english 75% shqip)
$t update "$tweet"


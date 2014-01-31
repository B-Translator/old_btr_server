#!/bin/bash

fortune='/usr/games/fortune'
t='/usr/local/bin/t'
tweet=$($fortune -s -n 140 30% literature 70% sami-frasheri)
$t update "$tweet"


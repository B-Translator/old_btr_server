#!/bin/bash

### go to this directory
cd $(dirname $0)

nohup_out=nohup-get.out
rm -f $nohup_out
nohup nice get/all.sh > $nohup_out &
sleep 1
tail -f $nohup_out

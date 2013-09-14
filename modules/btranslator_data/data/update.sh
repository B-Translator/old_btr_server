#!/bin/bash

### go to the script directory
cd $(dirname $0)

### get the PO files and import them
get/all.sh
import/all.sh


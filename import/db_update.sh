#!/bin/bash

### go to the script directory
cd $(dirname $0)

### get the PO files and import them
get-scripts/get-all.sh
import-scripts/import-all.sh

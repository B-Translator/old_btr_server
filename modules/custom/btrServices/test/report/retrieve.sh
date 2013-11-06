#!/bin/bash

### general contribution statistics
curl -k -i -X GET -H "Accept: application/json"  \
     "https://dev.l10n.org.xx/public/btr/report/statistics?lng=sq"

### top contributors
curl -k -i -X GET -H "Accept: application/json"  \
     "https://dev.l10n.org.xx/public/btr/report/topcontrib?lng=sq&period=week&size=5"

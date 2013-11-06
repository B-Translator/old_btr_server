#!/bin/bash

curl -k -i -H "Content-type: application/json"  \
     -X POST https://dev.l10n.org.xx/public/btr/report/topcontrib.json	\
     -d '{"lng": "sq", "period": "week", "size": 10}'

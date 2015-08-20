#!/bin/bash

curl -k -i -H "Content-type: application/json"  \
     -X POST https://dev.btr.example.org/api/report/topcontrib.json	\
     -d '{"lng": "sq", "period": "week", "size": 10}'

#!/bin/bash

curl -k -i -H "Content-type: application/json"  \
     -X POST https://dev.btr.example.org/public/btr/report/statistics.json  \
     -d '{"lng": "sq"}'

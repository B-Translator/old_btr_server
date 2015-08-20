#!/bin/bash

curl -k -i -H "Content-type: application/json"  \
     -X POST https://dev.btr.example.org/api/
report/statistics.json  \
     -d '{"lng": "sq"}'

#!/bin/bash

. ./awk.sh

if ! [[ $# -eq 1 ]]; then
echo "Script running only with 1 command line argument"
exit 1
fi

if ! [[ $1 =~ ^[1-4]$ ]]; then
echo "Choose a value from 1 to 4"
echo "1 - All entries sorted by response code"
echo "2 - All unique IPs found in records"
echo "3 - All requests with errors (response code - 4xx or 5xx)"
echo "4 - All unique IPs that occur among failed requests"
exit 1
fi

do_search $1

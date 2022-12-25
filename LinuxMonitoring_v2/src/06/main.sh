#!/bin/bash

if ! [[ $# -eq 0 ]]; then
echo "Script running without command line argument"
exit 1
fi

goaccess ../04/*access.log -o index.html --log-format=COMBINED
sudo rm -rf /var/www/html/index.html
sudo mv index.html /var/www/html/index.html

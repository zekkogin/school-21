#!/bin/bash

. ./functions.sh

if ! [[ $# -eq 0 ]]; then
echo "This script is running without arguments"
exit 1
fi

for i in {5..1};
do
    touch "$i"access.log
    notes=$(shuf -n1 -i 100-1000)
    for (( j=0; j<notes; j++ ))
    do
        echo -n "$(rand_ip)" >> "$i"access.log
        echo -n " - - " >> "$i"access.log
        echo -n "["$(date -d "$i day ago + $j minutes" '+%d/%b/%Y:%H:%M:%S %z')"] " >> "$i"access.log
        echo -n "\"$(rand_method) / " >> "$i"access.log
        echo -n "HTTP/1.1\" " >> "$i"access.log
        echo -n "$(rand_code_answer) " >> "$i"access.log
        echo -n "1000 " >> "$i"access.log
        echo -n "\"$(rand_url)\" " >> "$i"access.log
        echo "$(rand_agent)" >> "$i"access.log
    done
done
 
 #rand_date
 

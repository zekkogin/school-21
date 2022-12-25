#!/bin/bash
. ./clean.sh

if ! [[ $# -eq 1 ]]; then
echo "Invalid number of arguments"
exit 1
fi

if ! [[ $1 =~ ^[1-3]$ ]]; then
echo "Invalid choose of method (Only 1,2,3)"
exit 1
fi

if [[ $1 -eq 1 ]]; then

clean_log

fi
 
if [[ $1 -eq 2 ]]; then

clean_date

fi
 
if [[ $1 -eq 3 ]]; then

clean_mask

fi
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

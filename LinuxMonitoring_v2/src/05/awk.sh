#!/bin/bash

function do_search(){

path="../04/*access.log"

if [[ $1 -eq 1 ]];then
    awk '{print $0}' $path | sort -k 9
fi

if [[ $1 -eq 2 ]];then
    awk '{print $1}' $path | uniq
fi

if [[ $1 -eq 3 ]];then
    awk '{ if( $9 ~/^[54]..$/) print $0 }' $path
fi

if [[ $1 -eq 4 ]];then
    awk '{ if( $9 ~/^[54]..$/) print $1 }' $path | uniq
fi

}

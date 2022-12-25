#!/bin/bash

function clean_log() {

    log_temp=$(cat ../02/log.txt | awk '{print $2}')
    reg='/$'
    
    for n in $log_temp
    do
        if ! [[ $n =~ $reg ]]; then
            sudo rm -r $n 2> /dev/null
        fi
    done

}


function clean_date() {

    echo "Input date YYYY-MM-DD:"
    read date_start

    echo "Input time start HH:MM"
    read time_start

    echo "Input time end HH:MM"
    read time_end
    
    check_date_time $date_start $time_start $time_end
    
    newerthan="$date_start $time_start"
    olderthan="$date_start $time_end"

    find ../03/test -type f -newermt "$newerthan:00" ! -newermt "$olderthan:00" -delete

    find ../03/test -type d -newermt "$newerthan:00" ! -newermt "$olderthan:00" -delete

}

function check_date_time() {

    if ! [[ ${#1} -eq 10 ]]; then
        echo "Wrong date format"
        exit 1
    fi
    
    if ! [[ ${#2} -eq 5 ]]; then
        echo "Wrong time start format"
        exit 1
    fi
    
    if ! [[ ${#3} -eq 5 ]]; then
        echo "Wrong time end format"
        exit 1
    fi
}

function clean_mask(){

    echo "Input mask (example abcdefg_DDMMYY)"
    read mask
    
    letters=$(echo $mask | awk -F '_' '{print $1}')
    date=$(echo $mask | awk -F '_' '{print $2}')
    
    strlen=${#letters}
    letter=${letters:0:1}
    
    if [ $strlen -lt 5 ]; then
    for ((; $strlen<5; strlen=$((strlen + 1 )) )); do
    letters=$(echo $letters | sed "s/$letter/$letter$letter/")
    done
    fi
    
    letters+="*_$date"
    
    find / -name $letters | xargs rm -rf
}

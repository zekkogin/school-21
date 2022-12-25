#!/bin/bash
start=$(date +%s)
. ./printing.c

reg="[\/]$"

 if [[ $# != 1 ]]
 then
	 echo "Incorrect input"
 else
	if ! [[ $1 =~ $reg ]]
        then
		echo "Incorrect input"
	else
		if [[ -d "$1" ]]
	        then 
	  		 
			Printing $1
 	   		end=$(date +%s)
			echo "Script execution time (in seconds) = $(($end - $start))"
 	        else
		       	echo "Directory not found"
	 	fi
	fi
fi



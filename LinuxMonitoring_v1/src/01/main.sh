#!/bin/bash

# This script write command line argument 
# to terminal if is not digit

if [ $# == 0 ] 
   then
	echo "This script doesn\`t work without command line argument"
   else
	   if [ $# -gt 1 ]
	   then
		   echo "Doesn\`t work with >1 command line argument"
	   else
		   if [[ $1 =~ ^[-+]?[0-9]*[./]?[0-9]+$ ]] && [[ $1 != "0/0" ]]
	  	then
			echo "false"
	        else
			echo "$1"
	        fi
	   fi
fi

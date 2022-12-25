#!/bin/bash

. ./variables.c
. ./printing.c
. ./set_colors.c

reg=^[1-6]$

 if [[ "$#" != 4 ]]

  then

  echo "Incorrect number of command-line arguments. Enter 4 arguments."

 else
	if ! [[ "$1" =~ $reg ]] || ! [[ "$2" =~ $reg ]] || ! [[ "$3" =~ $reg ]] || ! [[ "$4" =~ $reg ]]
	then
		echo "Incorrect arguments. Only 1-6 numbers."
	else
		
		if [[ "$1" = "$2" ]] || [[ "$3" = "$4" ]]

		then
		echo "Can\`t print equal foreground and background colors. Please, repeat script."

		else
	
		 StartExportVariables
 		 StartExportColors
 
		 Arg1=$(SetColorbg $1) 
		 Arg2=$(SetColorfg $2)
 	 	 Arg3=$(SetColorbg $3)
		 Arg4=$(SetColorfg $4)

		 StartPrinting

		 fi
	fi
 fi

# Arg1 = Value name background
# Arg2 = Value name foreground
# Arg3 = Value background
# Arg4 = Value foreground

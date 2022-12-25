#!/bin/bash

. ./variables.c
. ./printing.c

if [[ $# > 0 ]]
	then
	echo "This script doesn\`t work with command line arguments"
else
StartExportVariables
StartPrinting

printf "\nSave the logs? Y/N\n"

read answer

	if [[ "$answer" =~ [Yy] ]]
		then
		file_date=$(date "+%d_%m_%y_%H_%M_%S")
		filename="$file_date.status"
		StartPrinting >> $filename
	else
		echo "Ok. Don\`t save. J[oKa"
	fi
fi

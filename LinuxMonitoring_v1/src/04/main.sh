#!/bin/bash

. ./variables.c
. ./printing.c
. ./set_colors.c
. ./config.cfg
if [[ $# > 0 ]] 
	then
		echo "This script doesn\`t work with command line arguments"
	else
 StartExportVariables
 StartExportColors

 default1=0
 default2=0
 default3=0
 default4=0
 CorrectColor="^[1-6]$"

 if ! [[ $column1_background =~ $CorrectColor ]]
 then 
 column1_background=6
 default1=1
 fi
 if ! [[ $column1_font_color =~ $CorrectColor ]]
 then
 column1_font_color=1
 default2=1
 fi
 if ! [[ $column2_background =~ $CorrectColor ]]
 then
 column2_background=2
 default3=1
 fi
 if ! [[ $column2_font_color =~ $CorrectColor ]]
 then 
 column2_font_color=4
 default4=1
 fi

 Arg1=$(SetColorbg $column1_background) 
 Arg2=$(SetColorfg $column1_font_color)
 Arg3=$(SetColorbg $column2_background)
 Arg4=$(SetColorfg $column2_font_color)

 if [[ $column1_background == $column1_font_color ]] || [[ $column2_background == $column2_font_color ]]
 then
	 echo "Can\`t print equal foreground and background colors."
	 echo "In config.cfg void arguments autochange to 6-1-2-4."
	 echo "Black - white - red - blue"
 else

 StartPrinting
 printf "\n"
 StartPrintingColors
 fi
fi

#Column 1 background = default (black)
#Column 1 font color = default (white)
#Column 2 background = default (red)
#Column 2 font color = default (blue)

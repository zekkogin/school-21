#!/bin/bash

. ./func_mask.c

function StartPrinting {
	NC=$(tput sgr0)

	echo "${Arg1}${Arg2}HOSTNAME${NC} = ${Arg3}${Arg4}$var1${NC}"

	echo "${Arg1}${Arg2}TIMEZONE${NC} = ${Arg3}${Arg4}$var2_0 $var2_1${NC}"

	echo "${Arg1}${Arg2}USER${NC} = ${Arg3}${Arg4}$var3${NC}"

	echo "${Arg1}${Arg2}OS${NC} = ${Arg3}${Arg4}$var4${NC}"

	echo "${Arg1}${Arg2}DATE${NC} = ${Arg3}${Arg4}$var5${NC}"

	echo "${Arg1}${Arg2}UPTIME${NC} = ${Arg3}${Arg4}$var6${NC}"

	echo "${Arg1}${Arg2}UPTIME_SEC${NC} = ${Arg3}${Arg4}$var7${NC}"

	echo "${Arg1}${Arg2}IP${NC} = ${Arg3}${Arg4}$var8${NC}"

	echo "${Arg1}${Arg2}MASK${NC} = ${Arg3}${Arg4}$var9${NC}"

	echo "${Arg1}${Arg2}GATEWAY${NC} = ${Arg3}${Arg4}$var10${NC}"

	echo "${Arg1}${Arg2}RAM_TOTAL${NC} = ${Arg3}${Arg4}$var11${NC}"

	echo "${Arg1}${Arg2}RAM_USED${NC} = ${Arg3}${Arg4}$var12${NC}"

	echo "${Arg1}${Arg2}RAM_FREE${NC} = ${Arg3}${Arg4}$var13${NC}"

	echo "${Arg1}${Arg2}SPACE_ROOT${NC} = ${Arg3}${Arg4}$var14${NC}"

	echo "${Arg1}${Arg2}SPACE_ROOT_USED${NC} = ${Arg3}${Arg4}$var15${NC}"

	echo "${Arg1}${Arg2}SPACE_ROOT_FREE${NC} = ${Arg3}${Arg4}$var16${NC}"

}


function PrintExtended {
	case "$1" in
		1) echo "(white)" ;;
	        2) echo "(red)" ;;
		3) echo "(green)" ;;
		4) echo "(blue)" ;;
		5) echo "(purple)" ;;
		6) echo "(black)" ;;
	esac
}

function StartPrintingColors {

	if [[ $default1 = 1 ]] 
	then
	 column1_background="default (black)"
	fi
	if [[ $default2 = 1 ]]
	then
	 column1_font_color="default (white)"
	fi
	if [[ $default3 = 1 ]]
	then
	 column2_background="default (red)"
	fi
	if [[ $default4 = 1 ]]
	then
	 column2_font_color="default (blue)"
	fi

	echo -e "Column 1 background = $column1_background $(PrintExtended $column1_background)"

	echo "Column 1 font color = $column1_font_color $(PrintExtended $column1_font_color)"

	echo "Column 2 background = $column2_background $(PrintExtended $column2_background)"

	echo "Column 2 font color = $column2_font_color $(PrintExtended $column2_font_color)"
}


#!/bin/bash

. ./func_mask.c

function StartPrinting {
	NC=$(tput sgr0)

	echo -e "${Arg1}${Arg2}HOSTNAME${NC} = ${Arg3}${Arg4}$var1${NC}"

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


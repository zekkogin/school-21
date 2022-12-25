#!/bin/bash

. ./func_calc.c
. ./func_mask.c

function StartPrinting {

	echo "HOSTNAME = $var1"

	echo "TIMEZONE = $var2_0 $var2_1"

	echo "USER = $var3"

	echo "OS = $var4"

	echo "DATE = $var5"

	echo "UPTIME = $var6"

	echo "UPTIME_SEC = $var7"

	echo "IP = $var8"

	printf "MASK = "
	prefixtodecimal

	echo "GATEWAY = $var10"

	printf "RAM_TOTAL = "
	calc $var11/1048576

	printf "RAM_USED = "
	calc $var12/1048576

	printf "RAM_FREE = "
	calc $var13/1048576

	echo "SPACE_ROOT = $var14"
	echo "SPACE_ROOT_USED = $var15"
	echo "SPACE_ROOT_FREE = $var16"

}


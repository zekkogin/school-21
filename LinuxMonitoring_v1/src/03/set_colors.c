. ./colors.c

SetColorbg() {

	case $1 in
	 1) res=$WHITEbg ;;
	 2) res=$REDbg ;;
 	 3) res=$GREENbg ;;
 	 4) res=$BLUEbg ;;
	 5) res=$PURPLEbg ;;
 	 6) res=$BLACKbg ;;
 	esac
	echo $res
}

SetColorfg() {

	case $1 in
	1) res=$WHITEfg ;;
	2) res=$REDfg ;;
	3) res=$GREENfg ;;
	4) res=$BLUEfg ;;
	5) res=$PURPLEfg ;;
	6) res=$BLACKfg ;;
	esac
	echo $res
}


function prefixtodecimal {

temp=$(ip -o -f inet addr show | awk '/scope/ {print $4}' | grep -m 1 -o '[^/]*$')

mask1=0
mask2=0
mask3=0
mask4=0
counter=7

while [ $temp -gt 24 ]
do	
       	mask4=$(( $mask4 + 2**$counter ))
	  	counter=$(( $counter - 1 ))
		temp=$(( $temp - 1 ))
	done
	
	counter=7
	
	while [ $temp -gt 16 ]
	do
		mask3=$(( $mask3 + 2**$counter ))
		counter=$(( $counter - 1 ))
		temp=$(( $temp - 1 ))
	done
	
	counter=7
	
	while [ $temp -gt 8 ]
	do
		mask2=$(( $mask2 + 2**$counter ))
		counter=$(( $counter - 1 ))
		temp=$(( $temp - 1 ))
	done
	
	counter=7
	
	while [ $temp -gt 0 ]
	do
		mask1=$(( $mask1 + 2**counter ))
		counter=$(( $counter - 1 ))
		temp=$(( $temp - 1 ))
	done

printf "%.0f.%.0f.%.0f.%.0f\n" "$mask1" "$mask2" "$mask3" "$mask4"

}

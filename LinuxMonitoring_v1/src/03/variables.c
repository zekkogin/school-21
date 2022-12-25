
function StartExportVariables {

	 var1=$(hostname)

	 var2_0=$(timedatectl | grep zone | awk '{print $3}')
	 var2_1=$(timedatectl show | grep TimeU -m 1 | awk '{print $4}')

	 var3=$(whoami)

	 var4=$(hostnamectl | grep Operating | cut -b 21-100)

	 var5=$(date | cut -b 5-25)

	 var6=$(uptime -p)

	 var7=$(awk '{ printf "%.d seconds", $1 }' /proc/uptime)

	 var8=$(ip -4 a | grep inet -m 1 | awk '{ print $2 }')

	 var10=$(ip route | grep default | awk '{print $3}')

	 var11=$(free | grep mem -i | awk '{print $2}')
	 var12=$(free | grep mem -i | awk '{print $3}')
	 var13=$(free | grep mem -i | awk '{print $4}')

	 var14=$(df /root | grep -e / | awk '{printf "%.2f MB", $2/1024}')
	 var15=$(df /root | grep -e / | awk '{printf "%.2f MB", $3/1024}')
	 var16=$(df /root | grep -e / | awk '{printf "%.2f MB", $4/1024}')

}

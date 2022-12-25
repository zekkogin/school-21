#!/bin/bash
. ./check.sh

function generate_files() {

num_files_temp=$num_files
file_size=${file_size%Mb}
file_letters_main=$(echo $file_letters | cut -d '.' -f 1)
file_letters_ext=$(echo $file_letters | cut -d '.' -f 2)

strlen=${#file_letters_main}
letter=${file_letters_main:0:1}

if [ $strlen -lt 5 ]; then
for ((; $strlen<5; strlen=$((strlen + 1 )) )); do
file_letters_main=$(echo $file_letters_main | sed "s/$letter/$letter$letter/")
done
fi
names=$file_letters_main
unic_letters=$(echo $file_letters_main | tr -s 'a-z')
count_of_unic_letters=${#unic_letters}
maxsize=$((244-strlen))
declare -i loop_1=$maxsize

loop_2_exist=0
loop_3_exist=0
loop_4_exist=0
loop_5_exist=0
loop_6_exist=0
loop_7_exist=0

counter2_rm=0
counter3_rm=0
counter4_rm=0
counter5_rm=0
counter6_rm=0
counter7_rm=0


letter_1=${unic_letters:0:1}
if [[ $count_of_unic_letters > 1 ]]; then
letter_2=${unic_letters:1:1}
declare -i loop_2=$maxsize
loop_2_exist=$((loop_2_exist+1))
fi
if [[ $count_of_unic_letters > 2 ]]; then
letter_3=${unic_letters:2:1}
declare -i loop_3=$maxsize
loop_3_exist=$((loop_3_exist+1))
fi
if [[ $count_of_unic_letters > 3 ]]; then
letter_4=${unic_letters:3:1}
declare -i loop_4=$maxsize
loop_4_exist=$((loop_4_exist+1))
fi
if [[ $count_of_unic_letters > 4 ]]; then
letter_5=${unic_letters:4:1}
declare -i loop_5=$maxsize
loop_5_exist=$((loop_5_exist+1))
fi
if [[ $count_of_unic_letters > 5 ]]; then
letter_6=${unic_letters:5:1}
declare -i loop_6=$maxsize
loop_6_exist=$((loop_6_exist+1))
fi
if [[ $count_of_unic_letters > 6 ]]; then
letter_7=${unic_letters:6:1}
declare -i loop_7=$maxsize
loop_7_exist=$((loop_7_exist+1))
fi

      file_name_to_dd=""

for ((; $loop_1>=0; loop_1=$((loop_1-1)) )) do
	if ! [[ $loop_1 -eq $maxsize ]]; then
	names=$(echo $names | sed "s/$letter_1/$letter_1$letter_1/")
	file_name_to_dd="$names.$file_letters_ext$(date +"_%d%m%y")"
    check_space
	dd if=/dev/zero of="$dir/$1/$file_name_to_dd" bs=1M count=$file_size 2> /dev/null
    echo "File" $dir"/"$1"/"$file_name_to_dd"/" --- $(date +'%e.%m.%Y') --- $file_size"Mb" >> log.txt
	num_files_temp=$((num_files_temp - 1))
	if [ $num_files_temp -eq 0 ]; then
	break
	fi
	size=$((size + 1))
	fi
	if [[ $loop_2_exist -eq 1 ]]; then
	for ((; $loop_2>=0; loop_2=$((loop_2-1)) )) do
		if ! [[ $loop_2 -eq $maxsize ]] && ! [[ $size -eq $maxsize ]]; then
		names=$(echo $names | sed "s/$letter_2/$letter_2$letter_2/")
		size=$((size + 1))
		counter2_rm=$((counter2_rm + 1))
		file_name_to_dd="$names.$file_letters_ext$(date +"_%d%m%y")"
        check_space
		dd if=/dev/zero of="$dir/$1/$file_name_to_dd" bs=1M count=$file_size 2> /dev/null
        echo "File" $dir"/"$1"/"$file_name_to_dd"/" --- $(date +'%e.%m.%Y') --- $file_size"Mb" >> log.txt
		num_files_temp=$((num_files_temp - 1))
		if [ $num_files_temp -eq 0 ]; then
		break 2
		fi
		fi
		if [[ $loop_2 -eq 0 ]]; then
		for ((; $counter2_rm > 0; counter2_rm=$((counter2_rm-1)) )) do
		names=$(echo $names | sed "s/$letter_2//")
		size=$((size - 1))
		done
		loop_2=$((maxsize-count_of_letters))
		break 1
		fi
		if [[ $loop_3_exist -eq 1 ]]; then
		for ((; $loop_3>=0; loop_3=$((loop_3-1)) )) do
			if ! [[ $loop_3 -eq $maxsize ]] && ! [[ $size -eq $maxsize ]]; then
			names=$(echo $names | sed "s/$letter_3/$letter_3$letter_3/")
			size=$((size + 1))
			counter3_rm=$((counter3_rm + 1))
			file_name_to_dd="$names.$file_letters_ext$(date +"_%d%m%y")"
            check_space
			dd if=/dev/zero of="$dir/$1/$file_name_to_dd" bs=1M count=$file_size 2> /dev/null
            echo "File" $dir"/"$1"/"$file_name_to_dd"/" --- $(date +'%e.%m.%Y') --- $file_size"Mb" >> log.txt
			num_files_temp=$((num_files_temp - 1))
			if [ $num_files_temp -eq 0 ]; then
			break 3
			fi
			fi
			if [[ $loop_3 -eq 0 ]]; then
			for ((; $counter3_rm > 0; counter3_rm=$((counter3_rm-1)) )) do
			names=$(echo $names | sed "s/$letter_3//")
			size=$((size - 1))
			done
			loop_3=$((maxsize-count_of_letters))
			break
			fi
			if [[ $loop_4_exist -eq 1 ]]; then
			for ((; $loop_4>=0; loop_4=$((loop_4-1)) )) do
				if ! [[ $loop_4 -eq $maxsize ]] && ! [[ $size -eq $maxsize ]]; then
				names=$(echo $names | sed "s/$letter_4/$letter_4$letter_4/")
				size=$((size + 1))
				counter4_rm=$((counter4_rm + 1))
				file_name_to_dd="$names.$file_letters_ext$(date +"_%d%m%y")"
                check_space
				dd if=/dev/zero of="$dir/$1/$file_name_to_dd" bs=1M count=$file_size 2> /dev/null
                echo "File" $dir"/"$1"/"$file_name_to_dd"/" --- $(date +'%e.%m.%Y') --- $file_size"Mb" >> log.txt
				num_files_temp=$((num_files_temp - 1))
				if [ $num_files_temp -eq 0 ]; then
				break 4
				fi
				fi
				if [[ $loop_4 -eq 0 ]]; then
				for ((; $counter4_rm > 0; counter4_rm=$((counter4_rm-1)) )) do
				names=$(echo $names | sed "s/$letter_4//")
				size=$((size - 1))
				done
				loop_4=$((maxsize-count_of_letters))
				break
				fi
				if [[ $loop_5_exist -eq 1 ]]; then
				for ((; $loop_5>=0; loop_5=$((loop_5-1)) )) do
					if ! [[ $loop_5 -eq $maxsize ]] && ! [[ $size -eq $maxsize ]]; then
					names=$(echo $names | sed "s/$letter_5/$letter_5$letter_5/")
					size=$((size + 1))
					counter5_rm=$((counter5_rm + 1))
                    file_name_to_dd="$names.$file_letters_ext$(date +"_%d%m%y")"
                    check_space
                    dd if=/dev/zero of="$dir/$1/$file_name_to_dd" bs=1M count=$file_size 2> /dev/null
                    echo "File" $dir"/"$1"/"$file_name_to_dd"/" --- $(date +'%e.%m.%Y') --- $file_size"Mb" >> log.txt
                    num_files_temp=$((num_files_temp - 1))
					if [ $num_files_temp -eq 0 ]; then
					break 5
					fi
					fi
					if [[ $loop_5 -eq 0 ]]; then
					for ((; $counter5_rm > 0; counter5_rm=$((counter5_rm-1)) )) do
					names=$(echo $names | sed "s/$letter_5//")
					size=$((size - 1))
					done
					loop_5=$((maxsize-count_of_letters))
					break
					fi
					if [[ $loop_6_exist -eq 1 ]]; then
					for ((; $loop_6>=0; loop_6=$((loop_6-1)) )) do
						if ! [[ $loop_6 -eq $maxsize ]] && ! [[ $size -eq $maxsize ]]; then
						names=$(echo $names | sed "s/$letter_6/$letter_6$letter_6/")
						size=$((size + 1))
						counter6_rm=$((counter6_rm + 1))
                        file_name_to_dd="$names.$file_letters_ext$(date +"_%d%m%y")"
                        check_space
                        dd if=/dev/zero of="$dir/$1/$file_name_to_dd" bs=1M count=$file_size 2> /dev/null
                        echo "File" $dir"/"$1"/"$file_name_to_dd"/" --- $(date +'%e.%m.%Y') --- $file_size"Mb" >> log.txt
                        num_files_temp=$((num_files_temp - 1))
						if [ $num_files_temp -eq 0 ]; then
						break 6
						fi
						fi
						if [[ $loop_6 -eq 0 ]]; then
						for ((; $counter6_rm > 0; counter6_rm=$((counter6_rm-1)) )) do
						names=$(echo $names | sed "s/$letter_6//")
						size=$((size - 1))
						done
						loop_6=$((maxsize-count_of_letters))
						break
						fi
						if [[ $loop_7_exist -eq 1 ]]; then
						for ((; $loop_7>=0; loop_7=$((loop_7-1)) )) do
							if ! [[ $loop_7 -eq $maxsize ]] && ! [[ $size -eq $maxsize ]]; then
							names=$(echo $names | sed "s/$letter_7/$letter_7$letter_7/")
							size=$((size + 1))
							counter7_rm=$((counter7_rm + 1))
                            file_name_to_dd="$names.$file_letters_ext$(date +"_%d%m%y")"
                            check_space
                            dd if=/dev/zero of="$dir/$1/$file_name_to_dd" bs=1M count=$file_size 2> /dev/null
                            echo "File" $dir"/"$1"/"$file_name_to_dd"/" --- $(date +'%e.%m.%Y') --- $file_size"Mb" >> log.txt
                            num_files_temp=$((num_files_temp - 1))
							if [ $num_files_temp -eq 0 ]; then
							break 7
							fi
							fi
							if [[ $loop_7 -eq 0 ]]; then
							for ((; $counter7_rm > 0; counter7_rm=$((counter7_rm-1)) )) do
							names=$(echo $names | sed "s/$letter_7//")
							size=$((size - 1))
							done
							loop_7=$((maxsize-count_of_letters))
							break
							fi
						done
						fi
					done
					fi
				done
				fi
			done
			fi
		done
		fi
	done
	fi
done

}

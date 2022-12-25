#!/bin/bash
start=`date +%s`

# main.sh az az.az 3Mb
. ./check.sh
. ./cringe.sh

export count_of_arg=${#}
export num_subfolders=$((1 + RANDOM % 99))
export num_files=$((1 + RANDOM % 99))

export folder_letters=${1}
export file_letters=${2}
export file_size=${3}

do_check
check_space
touch log.txt

paths=$(find /home -type d -maxdepth 4 -mindepth 1 2> /dev/null ! \( -path "*/bin" -o -path "*/bin/*" -o -path "*/sbin" -o -path "*/sbin/*" \))
dir="/home"

letter_dir=${folder_letters:0:1}
strlen=${#folder_letters}
if [ $strlen -lt 5 ]; then
for ((; $strlen<5; strlen=$((strlen + 1 )) )); do
folder_letters=$(echo $folder_letters | sed "s/$letter_dir/$letter_dir$letter_dir/")
done
fi

folder_name=$folder_letters
declare -i counter=0

echo $num_subfolders "num_subfolders"
echo $num_files "num_files"

  	for dir in $paths; do
    folder_name=$(echo $folder_name | sed "s/$letter_dir/$letter_dir$letter_dir/")
    counter=$((counter + 1))
  	folder_name_ext="$folder_name$(date +"_%d%m%y")"
  	mkdir "$dir/$folder_name_ext"
    echo " Dir" $dir"/"$folder_name_ext "+++" $(date +'%e.%m.%Y') "+++"  >> log.txt
    check_space
    generate_files $folder_name_ext
    if [ $counter -eq $num_subfolders ]; then
    break
    fi

  done

     end=`date +%s`
     runtime=$((end-start))
     echo "Runtime of script" $runtime "seconds"
        echo "Runtime of script" $runtime "seconds" >> log.txt

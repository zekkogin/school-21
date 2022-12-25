#!/bin/bash

# Files generator (6 arguments)
# 1 - absolute path 2 - number of subfolders 3 - list of characters names of dir`s
# 4 - number of files in each dir 5 - list of characters names of files and extensions
# 6 - size of files ( x < 100 Kilobytes ).
# maxsize folder name 248 + 7
# main.sh /opt/test 4 az 5 az.az 3kb

. ./check.sh
. ./cringe.sh

export count_of_arg=${#}
export path=${1}
export num_subfolders=${2}
export folder_letters=${3}
export num_files=${4}
export file_letters=${5}
export file_size=${6}

do_check
check_space
touch log.txt

folder_letters_unic=$(echo $folder_letters | tr -s 'a-z')

counter_unic_letter=${#folder_letters_unic}
counter_unic_letter=$((counter_unic_letter - 1))
letter_dir=${folder_letters_unic:$counter_unic_letter:1}
strlen=${#folder_letters}
if [ $strlen -lt 4 ]; then
for ((; $strlen<4; strlen=$((strlen + 1 )) )); do
folder_letters=$(echo $folder_letters | sed "s/$letter_dir/$letter_dir$letter_dir/")
done
fi

maxsize=$((248-strlen))

folder_name=$folder_letters
declare -i counter=0
max_folders=$((($counter_unic_letter + 1) * $maxsize))

#echo "maximum of folders for $folder_letters_unic letters is $max_folders"

  	for ((; $num_subfolders>0; num_subfolders=$((num_subfolders - 1)) )); do
      
    folder_name=$(echo $folder_name | sed "s/$letter_dir/$letter_dir$letter_dir/")
    counter=$((counter + 1))
  	folder_name_ext="$folder_name$(date +"_%d%m%y")"
  	mkdir "$path/$folder_name_ext" 2> /dev/null
    echo " Dir" $path"/"$folder_name_ext "+++" $(date +'%e.%m.%Y') "+++"  >> log.txt
    if [[ $num_files -gt 0 ]]; then
    generate_files $folder_name_ext
    fi
    if [ $counter -eq $maxsize ]; then
    counter_unic_letter=$((counter_unic_letter - 1))
    counter=0
    folder_name=$folder_letters
    letter_dir=${folder_letters_unic:$counter_unic_letter:1}
    fi
  done
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

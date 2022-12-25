
function do_check() {

file_letters_main=$(echo $file_letters | cut -d '.' -f 1)
file_letters_ext=$(echo $file_letters | cut -d '.' -f 2)

regex_folder_letters='^[A-Za-z]{1,7}$'
regex_file_letters='^[A-Za-z]{1,7}[.][A-Za-z]{1,3}$'
regex_file_size='^[0-9]+[k][b]$'
file_size_temp=${file_size%kb}

 if [[ $count_of_arg != 6 ]]
 then
     echo "Invalid number of arguments"
     exit 1
 fi
 
 if ! [[ -d $path ]]
 then
     echo "Path doesn\` exist"
     echo "First argument"
     exit 1
 fi
 
 if [[ $num_subfolders < 0 ]] && ! [[ $num_subfolders =~ '^[0-9]*$' ]]
 then
     echo "Number of subfolders can\`t set below zero or character"
     echo "Second argument"
     exit 1
 fi
 
 if ! [[ $folder_letters =~ $regex_folder_letters ]]
 then
     echo "Use only english alphabet (no more than 7 characters) folder"
     echo "Third argument"
     exit 1
 fi
 
 if [[ $num_files < 0 ]] && ! [[ $num_files =~ '^[0-9]*$' ]]
 then
     echo "Number of files can not below zero"
     echo "Fourth argument"
     exit 1
 fi
 
 if ! [[ $file_letters =~ $regex_file_letters ]]
 then
     echo "Invalid file name (no more than 7 characters) and extension (no more than 3 characters) (ex. qwertyu.txt)"
     echo "Fifth argument"
     exit 1
 fi
 
 if ! [[ $file_size =~ $regex_file_size ]] || [[ $file_size_temp -lt 0 ]] || [[ $file_size_temp -gt 100 ]];
 then
     echo "Not valid file size (no more than 100 kilobytes)"
     echo "Sixth argument"
     exit 1
 fi
}

function check_space() {

 size_of_mounting_point=$(df -H | grep "/"$ | awk '{print $4}' | sed 's/.$//')

 if [[ $size_of_mounting_point < 1 ]]
 then
     echo "Don\`t enough memory in disk (you should have more than 1 Gb)"
     exit 1
 fi

}

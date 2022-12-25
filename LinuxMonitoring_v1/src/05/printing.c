
function Printing {

	echo "Total number of folders (including all nested ones) = $(find $1 -type d| wc -l)"
	
	echo "Top 5 folders of maximum size arranged is descending order (path and size):"
	du -h $1 | sort -h -r | head -5 | awk 'BEGIN{cnt=1}{printf "%d - %s, %s \n", cnt , $2, $1; cnt++}'

	printf "Total number of files = "
	find $1 -type f | wc -l

	printf "Number of:\nConfiguration files (with the .conf extension) = "
	find $1 -type f -name "*.conf" | wc -l
	printf "Text files = "
	find $1 -type f -exec file $1 {} + | grep text | wc -l
	printf "Log files (with the extension .log) = "
       	find $1 -type f -name "*.log" | wc -l
	printf "Executable files = "
	find $1 -type f -exec file $1 {} + | grep executable | wc -l
	printf "Archive files = "
	find $1 -type f -name "*.rar" -o -name "*.7zip" -o -name "*.tar" -o -name "*.7z" -o -name "*.s7z" -o -name "*.apk" -o -name "*.tgz" | wc -l
	printf "Symbolic links = "
        ls -lR $1 | grep ^l | wc -l

       
        echo "Top 10 files of maximum size arranged is descending order (path, size and type): "

	for counter in {1..10}
	do
	temp=$(find $1 -type f -exec du -h {} + | sort -hr | head -10 | sed "${counter}q;d")
	if ! [[ -z $temp ]]
	then
	echo -n "$counter - "
	echo -n "$(echo $temp | awk '{print $2}')"
	echo -n ", "
	echo -n "$(echo $temp | awk '{print $1}')"
	echo -n ", "
	echo "$(echo $temp | grep -m 1 -o -E "\.[^/.]+$" | awk -F . '{print $2}')"
	fi
	done

	echo "Top 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file): "
	for counter in {1..10}
	do
	temp_for_executable=$(find $1 -type f -exec file {} + | grep executable | awk '{print $1}' | sed 's/.$//' | xargs)
	temp1=$(du -h $temp_for_executable | sort -hr | head -10 | sed "${counter}q;d")
	if ! [[ -z $temp1 ]]
	then
	echo -n "$counter - "
	echo -n "$(echo $temp1 | awk '{print $2}')"
	echo -n ", "
	echo -n "$(echo $temp1 | awk '{print $1}')"
	echo -n ", "
	path=$(echo $temp1 | awk '{print $2}')
	hash=$(echo $path | md5sum | awk '{print $1}')
	echo "$hash"
	fi
	done
			
}


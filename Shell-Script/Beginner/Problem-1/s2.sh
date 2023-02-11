
#---------------------------------------- TASK 2 ---------------------------------------------

#................... taking directory name as input from user ................... 

echo "Enter name of directory to create: "
read dir_name

#Verifying Directory name and creating it if it doesn't exist
if [ ! -d $dir_name ]
then
	mkdir $dir_name
	echo "Done! (^_^)"
fi

#Comparing variables
V=987
W=0

echo "Enter the value of W:"
read W

if [ $V -gt $W ]
then
        echo "W < V"
fi

index=0
date1=`date +%s`;
chr=(A B C D E F G H I J K L M N O P Q R S T U V W X Y Z)
filename=${chr[$index]}${chr[$index]}${chr[$index]}

#Successively creating files after every 7 sec named AAA, BBB, CCC,..... 
while true;do

	if [ $(date -u --date @$((`date +%s` - $date1)) +%S) == 07 ]
	then
		date1=`date +%s`
		touch $dir_name/$filename
		
		filename=${chr[$index]}${chr[$index]}${chr[$index]}
		index=$((index+1))
		
		if (($index > 25))
		then
			index=0
		fi
	fi
done

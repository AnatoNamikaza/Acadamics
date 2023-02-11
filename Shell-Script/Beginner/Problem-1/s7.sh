
#---------------------------------------- TASK 7 ---------------------------------------------

#...................displays the files in the "/etc" directory 
echo $"****** print the files in the /etc directory ******"
fileName=`ls /etc`
for File in $fileName
    do
	echo $File

    done
echo $'\n' # new line


#...................displays the files in the "/etc" directory which contain the character string "root" 
echo $"****** displays the files in the /etc directory which contain the character string root ******"
fileName=`ls /etc | grep root`
if [ -z "$fileName" ]
then
      echo "\$fileName is NULL"
else
	for File in $fileName
	do
		echo $File

	done
fi
echo $'\n' # new line

#displays top 8 lines of  "/etc/apt/sources.list" 
echo $"****** displays top 8 lines of  /etc/apt/sources.list ******"

fileName="/etc/apt/sources.list"
count=0
cat $fileName | while read p
do
	if((count<=8))
	then 
		echo $p
	fi
	((count++))
done
echo $'\n' # new line

#sorted first the file, then  displays those line that consist of characters "Beautiful flowers"
echo $"******sorted first the file, then  displays those line that consist of characters Beautiful flowers******"
echo $'\nEnter word that you wanna search in /etc/apt/sources.list '
read search
fileName="-n /etc/apt/sources.list"
sort $fileName | grep $search | while read p
do
	echo $p
done
echo $'\n' # new line

#creates a variable named: "CONFIG_TERMIN" and assigns it as value the absolute path of the profile system file: "/ etc / profile",
echo $'****** creates a variable named: CONFIG_TERMIN and assigns it as value the absolute path of the profile system file: / etc / profile *******'

CONFIG_TERMIN=`whereis /etc/profile`
echo $CONFIG_TERMIN







#! /bin/bash

File_Extension=$1

if [ "$#" -eq "0" ]
then
    echo "Enter File Extension to search:"
    read File_Extension
fi

C_count=0
Sub_count=0

for item in *
do
    if [ -d $item ]
    then
        Sub_count=0
        for item2 in $item/*
        do
            if [ -f $item2 ]    
            then
                if [[ "$item2" == *"$File_Extension"* ]]
                then
                    ((Sub_count++))
                fi
            fi
        done    
        echo "Directory" $item "has" $Sub_count $File_Extension "file."
        echo
    elif [ -f $item ]    
    then
        if [[ "$item" == *"$File_Extension"* ]]
        then
            ((C_count++))
        fi
    fi
done

echo "Current Directory has" $C_count $File_Extension "file."

exit 1

# Ouput_1:
# $ bash q3.sh .txt
# Directory OS_Lab_4 has 3 .txt file.
# Current Directory has 2 .txt file.

# Ouput_2:
# $ bash q3.sh .sh
# Directory OS_Lab_4 has 0 .sh file.
# Current Directory has 4 .sh file.

# Ouput_3:
# $ bash q3.sh .cpp
# Directory OS_Lab_4 has 2 .cpp file.
# Current Directory has 0 .cpp file.

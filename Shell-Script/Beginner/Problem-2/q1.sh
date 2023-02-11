#! /bin/bash

if [ $# -ne 2 ]
then
    echo "Incorrect parameter format."
    exit 1
fi

if [[ ! -f $1 ]]
then
    echo "The file $1 does not exist!"
    exit 1
elif [[ ! -f $2 ]]
then
    echo "The file $2 does not exist!"
    exit 1
fi

count=$(($(wc -l < "$1")+$(wc -l < "$2")))

echo "Total number of Lines:" $count

# Output_1:
# $ seq 1 11 > 1.txt 
# $ seq 421 452 > 2.txt 
# $ bash q1.sh 1.txt 2.txt 
# Total number of Lines: 43

# Output_2:
# $ seq 1 10 > 1.txt
# $ seq 1 10 > 2.txt
# $ bash q1.sh 1.txt 2.txt 
# Total number of Lines: 20

#!/bin/bash

SECONDS=0

while read -r number
do 
	echo $(($number*2)) >> newfile1.txt
done < file1.txt

duration=$SECONDS
echo "$duration seconds"
echo "Task Done"

#!/bin/bash

for ((i=0; i<1000000; i++)) 
do echo $RANDOM
done > "file1.txt"
echo "Million Random Number file generated."

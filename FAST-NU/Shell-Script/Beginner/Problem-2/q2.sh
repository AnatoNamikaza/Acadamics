#! /bin/bash

args=($@)
vote_0=0
vote_1=0
n=0

while [ $n -lt $# ]
do
    if [[ ${args[$n]} == "0" ]]
    then
        ((vote_0++))
    elif [[ ${args[$n]} == "1" ]]
    then
        ((vote_1++))
    fi
    n=$((n+1))
done

if [ $vote_0 -gt $vote_1 ]
then
    echo "Winner is 0 with " $vote_0 "votes"
elif [ $vote_1 -gt $vote_0 ]
then
    echo "Winner is 1 with " $vote_1 "votes"
else
    echo "Vote is a tie. Each obtained " $vote_0 "votes."
fi

# Output_1:
# $ bash q2.sh 0 1 1 0 0 0 1 1
# Vote is a tie. Each obtained  4 votes.

# Output_2:
# $ bash q2.sh 0 1 1 0 0 0 1 
# Winner is 0 with  4 votes

# Output_3:
# $ bash q2.sh 0 1 1 0 1 
# Winner is 1 with  3 votes

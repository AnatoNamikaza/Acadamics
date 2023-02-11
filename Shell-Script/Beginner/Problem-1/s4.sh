
#---------------------------------------- TASK 4 --------------------------------------------

files=`printenv`;count=0;for value in $files ;do((count++)); done;printLines=5;count=$(expr $count - $printLines);for value in $files; do if(($count <= 0)); then echo $value;fi;((count--));done; XYZ="WORK VARIABLE";unset XYZ

export EEE="CONTEXT";env | grep EEE

echo
echo

read -p "Hello, what's your first name: " first_name

echo "Welcome, your first name is: $first_name"

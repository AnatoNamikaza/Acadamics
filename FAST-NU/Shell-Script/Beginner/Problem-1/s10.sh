# ------------------------------------------- TASK 10  ------------------------------------------- 

#print number of rows that present in /etc/passwd
file="/etc/passwd"
lines=`grep -c "." $file`
echo Number of lines in $file is $lines
#print new line on terminal
echo $'\n'

# no print the value of shell variable and print all these values 
files=`printenv`
for value in $files
	do
		echo $value
	done
#print new line on terminal
echo $'\n'

#locates the executable binary file "clear"
clear=`whereis clear`
echo $clear
#print new line on terminal
echo $'\n'

#writes the contents of the manual page for the touch command to a file named fghijkl, under the home directory of the logged in user.
fileName="fghijkl"
`man ls >> ~/$fileName`


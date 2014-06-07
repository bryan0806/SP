#func2.sh
#Use of function
function printit(){
	echo "Your choice is $1" #這個$1 必須要參考底下指令的下達
}
echo "This program will print your selection!"
case $1 in
 "one")
 	printit 1
	;;
 "two")
 	printit 2
 	;;
 "three")
 	printit 3
 	;;
 *)
 	echo "Usage $0 {one|two|three}"
	;;
esac

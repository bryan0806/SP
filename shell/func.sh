#func.sh
#Use of function
function printit(){
	echo -n "Your choice is " #加上-n可以不斷行繼續在同一行顯示
}
echo "This program will print your selection!"
case $1 in
 "one")
 	printit; echo $1 | tr 'a-z' 'A-Z' #將參數做大小寫轉換
	;;
 "two")
 	printit; echo $1 | tr 'a-z' 'A-Z' #將參數做大小寫轉換
 	;;
 "three")
 	printit; echo $1 | tr 'a-z' 'A-Z' #將參數做大小寫轉換
 	;;
 *)
 	echo "Usage $0 {one|two|three}"
	;;
esac

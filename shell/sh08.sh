#sh08.sh
#use command "sh sh08.sh one two three four five six" to see the result
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> $@"
shift #進行第一次 "一個變數的shift"
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> $@"
shift 3 #進行第2次 "3個變數的shift"
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> $@"

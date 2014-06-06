#sh08.sh
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> $@"
shift #進行第一次 "一個變數的shift"
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> $@"
shift 3 #進行第2次 "3個變數的shift"
echo "Total parameter number is ==> $#"
echo "Your whole parameter is ==> $@"

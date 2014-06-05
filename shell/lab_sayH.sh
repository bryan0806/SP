#lab_sayH.sh
#若只輸入firstname而無lastname 則將lastname預設為 "先生"
read -p "Enter your firstname and lastname: " firstname lastname
last=${lastname:-"先生"}
echo "Hello $firstname $last, Let be friend!"


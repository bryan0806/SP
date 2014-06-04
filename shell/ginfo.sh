# 系統變數,放在雙引號內會先轉成內容值之後在顯示
# 指令分隔符號：同一列要下多個指令需要使用分號

clear
echo "Hello $USER"
echo "Today is ";date
echo "Number of user login ";who|wc -l
echo "Calendar";cal


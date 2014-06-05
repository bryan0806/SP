#sh03.sh
#讓使用者輸入檔案名稱,並取得fileuser這個變數
echo -e "I will use 'touch' command to create 3 files."
read -p "Please input your filename:" fileuser
#為了避免使用者隨意按Enter,利用變數功能分析檔名是否有設定
filename=${fileuser:-"filename"} #判斷是否有設定 如果沒有預設值為filename
#開始利用date指令來取得所需要的檔名
date1=$(date --date='2 days ago' +%Y%m%d) #前兩天的日期
date2=$(date --date='1 days ago' +%Y%m%d) #前1天的日期
date3=$(date +%Y%m%d)
file1=${filename}${date1}
file2=${filename}${date2}
file3=${filename}${date3}
#將檔名建立
touch "$file1"
touch "$file2"
touch "$file3"


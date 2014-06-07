#lab_for_filehead2.sh
#將副檔名html的檔案 前兩列資料讀出後存到file_heads檔案內
for file in `ls *.html`
do
	head -n 2 $file >> file_heads
done

# 寫一程式1.查看 /root/test/logical 這個名稱是否存在 2.若不存在
#則建立一個檔案 3.如果存在 判斷該名稱是否為檔案 若為檔案則刪除
# 之後 建立一個目錄 名稱為logical 之後離開
# 4.如果存在的話 且為目錄 將之刪除

if [ -e /root/test/logical ]; then
	if [ -f /root/test/logical ]; then
		echo "enter here"
		rm -f /root/test/logical
		mkdir /root/test/logical
		exit 0;
 	elif [ -d /root/test/logical ]; then
		rmdir /root/test/logical
 	fi
else
 	echo "again here"
 	touch /root/test/logical
 	exit 0;
fi

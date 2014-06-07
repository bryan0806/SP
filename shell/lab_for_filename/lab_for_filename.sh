#lab_for_filename.sh
#把目錄下大寫的檔案名稱修改成小寫的檔案名稱

for i in `ls | grep [A-Z]`
do
	mv $i `echo $i | tr [A-Z] [a-z]`
done

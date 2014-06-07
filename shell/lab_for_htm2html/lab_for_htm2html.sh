#lab_for_htm2html.sh
#把*.htm 修改成 *.html
for file in `ls *.htm`
do
	mv $file ${file%.*}.html
done

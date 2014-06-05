#lab_score.sh
#輸入一分數 在90~100分之間印出優等 接下來 甲等 乙等

read -p "Enter a score: " score
if [ $score -ge 90 ]
then
 echo "優等"
elif [ $score -ge 80 ]
then
 echo "甲等"
elif [ $score -ge 70 ]
then
 echo "乙等"
fi




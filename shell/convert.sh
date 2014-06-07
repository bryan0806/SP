#convert.sh
#using command "./convert.sh -b 2 -n 100
#bc 為 linux 內建計算機
while [ "$1" ]
do
 if [ "$1" == "-b" ];then
  ob="$2"
  case $ob in
   16) basesystem="Hex";;
   8) basesystem="Oct";;
   2) basesystem="bin";;
   *) basesystem="Unknow";;
  esac
  shift 2
 elif [ "$1" == "-n" ]
 then
  num="$2"
  shift 2
 else
  echo "Program $0 does not recognize option $1"
  exit 1
 fi
done
output=`echo "obase=$ob;ibase=10;$num;" | bc`  #bc 是linux 內建計算機
#obase ibase  都是bc 的設定指令 接下來輸入的數字 都會被轉成obase位元的數字
#可在linux 終端機下面輸入bc 玩看看
echo "$num Decimal number = $output in $basesystem number system (base=$ob)"


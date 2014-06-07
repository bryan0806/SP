#car.sh
#這個範例使用case(like c switch)
if [ -z $1 ];then  # if $1 == NULL
 rental="*** Unknow vehicle***"
elif [ -n $1 ];then # if $1 != NULL
#otherwise make first arg as rental
 rental=$1 
fi


case $rental in
 "car"|"Car") echo "For $rental Rs.20 per k/m";;
 "van"|"Van") echo "For $rental Rs.10 per k/m";;
 "jeep"|"Jeep") echo "For $rental Rs.5 per k/m";;
 "bicycle"|"Bicycle") echo "For $rental 20 paisa per k/m";;
 *) echo "Sorry,I can not gat a $rental for you";;
esac


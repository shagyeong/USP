#while 2

sum=0
i=1

while [ $i -le 10 ] #i <= 10
do
	sum=`expr $sum + $i`
	i=`expr $i + 1`
done

echo "1+2+...+10=$sum"

exit 0

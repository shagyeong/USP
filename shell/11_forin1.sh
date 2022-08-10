#for~in 1

sum=0

for i in 1 2 3 4 5
do
	sum=`expr $sum + $i`
done

echo "1+2+3+4+5=$sum"

exit 0

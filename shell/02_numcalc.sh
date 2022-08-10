#숫자 계산
num1=100
num2=$num1+200
num3=`expr $num1 + 200`
num4=`expr \( $num1 + 200 \) / 10 \* 2`

echo $num1
echo $num2
echo $num3
echo $num4

exit 0

#while 3

echo "비밀번호를 입력 : "
read pw

while [ $pw != "1234" ]
do
	echo "비밀번호 오류"
	read pw
done

echo "로그인 완료"

exit 0

#break, continue, exit

echo "무한반복 - b : break, c : continue, e : exit"

while [ 1 ]
do
	read answer
	case $answer in
	b | B)
		break;;
	c | C)
		continue;;
	e | E)
		exit 1;;
	esac;
done

echo "break로 탈출해 정상종료"

exit 0

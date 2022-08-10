#함수의 파라미터 사용

sum () {
	echo `expr $1 + $2`
}

sum 21 22

exit 0

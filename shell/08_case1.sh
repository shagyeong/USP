#case~esac문

case "$1" in
	start)
		echo "시작";;
	stop)
		echo "중지";;
	restart)
		echo "다시 시작";;
	*)
		echo "알 수 없는 매개변수";;
esac

exit 0

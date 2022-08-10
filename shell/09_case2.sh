#case~esac 2

echo "리눅스가 재미있다. (yes/no)"
read answer

case $answer in
	yes | Yes | YES | y | Y)
		echo "더욱 열심히 하십시오.";;
	[nN]*)
		echo "안타깝습니다.";;
	*)
		echo "답변 오류"
		exit 1;;
esac

exit 0

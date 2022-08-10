#eval : 문자열을 명령문으로 인식하고 실행

str="head -5 19*.sh"

echo $str
eval $str

exit 0

#파일과 관련된 조건

fname=readme.md #변수 선언시 공백이 없어야 함을 기억하라

if [ -e $fname ]
then 
  echo " $fname 이 존재함"
else
  echo " $fname 이 존재하지 않음"
fi

exit 0

# -d : 파일이 디렉토리면 참
# -e : 파일이 존재하면 참
# -f : 파일이 일반 파일이면 참
# -g : 파일에 set-group-id가 설정되면 참
# -r : 파일이 읽기 기능이면 참
# -s : 파일 크기가 0이 아니면 참
# -u : 파일에 set-user-id가 설정되면 참
# -w : 파일이 쓰기 가능 상태면 참
# -x : 파일이 실행 가능 상태면 참

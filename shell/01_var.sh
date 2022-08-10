#변수의 입력과 출력
v1="hi woo"
echo $v1
echo "$v1" #변수를 큰따옴표로 묶거나 묶지 않아도 된다
echo '$v1' #작은따옴표로 묶어 문자로 취급
echo \$v1  #역슬래시로 '$'을 문자로 취급

echo "값 입력 : "
read v1
echo '$v1' = $v1
exit 0

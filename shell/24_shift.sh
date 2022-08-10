#shift

myfunc () {
    str=""

    while [ "$1" != "" ]
    do
        str="$str $1"
        shift
    done

    echo $str
}

myfunc aaa bbb ccc ddd eee

exit 0
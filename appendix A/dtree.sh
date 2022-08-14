#! /bin/sh

usgage() {
    echo "Usage : $0 [-a] [-f] [-h] [-p] [-s] [Directory]"
    echo " [option] -a (-A) : directory and file"
    echo "          -f (-F) : output to file (dtree.text)"
    echo "          -h (-H) : help"
    echo "          -p (-P) : output to printer"
    echo "          -s (-s) : with block-number"
    echo " "
    exit 1
}

tailr() {
    awk ' {
        line[NR] = $0
    }
    END {
        for(i = NR; i > 0; i--){
            print line[i]
        }
    } '
}

DIR=`pwd`
OPT=""
OPT1=""

for kinta in $*
do
    case $kinta in

#...
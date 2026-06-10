#!/bin/sh

sum() {
    result=0

    for x in "$@"
    do
        result=`expr "$result" + "$x" 2>/dev/null`

        if [ $? -ne 0 ]
        then
            echo 0
            return 1
        fi
    done

    echo "$result"
    return 0
}

read line1
read line2

s1=`sum $line1`
s2=`sum $line2`

if [ "$s1" = "$s2" ]
then
    echo "Equal"
else
    echo "Not equal"
fi

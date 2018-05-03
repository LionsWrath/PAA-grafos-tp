#!/bin/bash

tests=('1' '2' '3' '4' '5')

for ((sz=0; sz<${#tests[@]}; sz++)) do
    test=${tests[${sz}]}

    time ../a.out < in_${test}.txt | diff out_${test}.txt -
done

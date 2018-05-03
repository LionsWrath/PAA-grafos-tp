#!/bin/bash

tests=('2e_100000_133332' '2e_10000_13332' 'cy_100000_133332' 'in_80001_100000' 'ofw_100000_133332' 'sofw_100000_99999' 'vf_1000_499500' 'vf_100_4950')

for ((sz=0; sz<${#tests[@]}; sz++)) do
    test=${tests[${sz}]}

    time ../../a.out < ${test}.txt | diff ${test}.out -
done

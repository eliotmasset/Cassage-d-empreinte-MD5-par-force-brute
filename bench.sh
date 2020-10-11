#!/bin/bash

END=$1
WORD=$2
CORE=$3

for ((i=1;i<=END;i++)); do
    tmpfile=$(mktemp)
    printf "m\n${WORD}\n${CORE}\n" | ./main > $tmpfile && grep "secondes" $tmpfile >> result.txt
done


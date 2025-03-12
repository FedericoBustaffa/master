#!/bin/bash

if [ -f "times.csv" ]; then
    echo "times.csv is going to be overwrited"
    read -p "do you want to continue? [y/n] " choice
    if [[ "$choice" != "y" ]]; then
        exit 1
    fi
fi

# delete the content of previous run
for f in *.txt; do
    truncate -s 0 $f
done

# run all simulations and save results
make -j
for j in {512,1024,2048,4096,8192,16384}; do
    for i in {0..49}; do
        ./softmax_plain.out $j 1 1>> plain_times_$j.txt 2>> plain_res_$j.txt
        ./softmax_auto.out $j 1 1>> auto_times_$j.txt 2>> auto_res_$j.txt
        ./softmax_avx.out $j 1 1>> avx_times_$j.txt 2>> avx_res_$j.txt
    done
done

RED="\e[31m"
GREEN="\e[32m"
RESET="\e[0m"

# check that every program compute the same result
function compare_results() {
    diff $1 $2 > /dev/null 2>&1
    if [[ $? != 0 ]]; then
        echo -e "${RED}$1 - $2: failed${RESET}"
    else
        echo -e "${GREEN}$1 - $2: passed${RESET}"
    fi
}

for j in {512,1024,2048,4096,8192,16384}; do
    compare_results plain_res_$j.txt auto_res_$j.txt
    compare_results plain_res_$j.txt avx_res_$j.txt
    compare_results auto_res_$j.txt avx_res_$j.txt
    echo "---------------"
done

# aggregate time files
python aggregate.py *_times_*.txt

# delete all sparse files
rm *.txt

#!/bin/bash

for i in {0..19}; do
	./softmax_plain.out $1 1 1>> plain_times.txt 2>> plain.txt
	./softmax_auto.out $1 1 1>> auto_times.txt 2>> auto.txt
	./softmax_avx.out $1 1 1>> avx_times.txt 2>> avx.txt
done

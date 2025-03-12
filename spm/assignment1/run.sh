#!/bin/bash

for i in {0..49}; do
	for j in {512,1024,2048,4096,8192}; do
		./softmax_plain.out $1 1 1>> plain_times.txt 2>> plain_res.txt
		./softmax_auto.out $1 1 1>> auto_times.txt 2>> auto_res.txt
		./softmax_avx.out $1 1 1>> avx_times.txt 2>> avx_res.txt
	done
done

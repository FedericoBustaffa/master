#!/bin/bash

for i in {0..19}; do
	./softmax_plain.out $1 1 1>> log.txt 2>> plain.txt
	./softmax_auto.out $1 1 1>> log.txt 2>> auto.txt
done
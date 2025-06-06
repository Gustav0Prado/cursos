#!/usr/bin/bash
make clean; make; clear;
for file in exemplos/*.in; do
    grafo=$(basename $file .in)
    diff <(./teste < exemplos/$grafo.in) exemplos/$grafo.out
done
#!/usr/bin/bash
make clean; make; clear;
for file in $(ls -v exemplos/*.in); do
    grafo=$(basename $file .in)
    echo -n "$grafo: "
    saida=$(diff <(./teste < exemplos/$grafo.in) exemplos/$grafo.out)
    if [[ $saida ]]; then
        echo "$saida"
    else
        echo "OK"
    fi

done
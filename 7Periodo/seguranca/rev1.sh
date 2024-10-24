#!/bin/bash

upperlim=500

for ((i=0; i<=upperlim; i++)); do
    echo "$i" | nc  200.238.144.25 4443 | tail -c 2 | tr -d "\n"
done

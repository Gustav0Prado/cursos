#!/bin/bash
make integral
echo ">>> Integral Sequencial"
time ./integral-seq
printf "\n"

echo ">>> Integral Paralela"
time ./integral-par
#!/bin/bash
make
clear

echo ">>> Integral Sequencial"
time ./integral-seq
printf "\n"

echo ">>> Integral Paralela - Vetor"
time ./integral-par
printf "\n"

echo ">>> Integral Paralela - Critical"
time ./integral-par-crit
printf "\n"

echo ">>> Integral Paralela - omp for"
time ./integral-par-pfor
printf "\n"

echo ">>> Integral Paralela - Uma linha"
time ./integral-pfull
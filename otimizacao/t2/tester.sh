#!/bin/bash

clear;

echo "Sem cortes de otimalidade/viabilidade"
printf "\n"
./separa -of < $1

printf "\n"
echo "========================================="

printf "\n"
echo "Sem cortes de otimalidade"
./separa -o < $1

printf "\n"
echo "========================================="


printf "\n"
echo "Branch and Bound com Bdada"
./separa -a < $1

printf "\n"
echo "========================================="


printf "\n"
echo "Branch and Bound com Bcriada"
./separa < $1
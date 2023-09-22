#!/bin/bash

make clean
make

./generate.py

TIMEFORMAT=%R

echo "------------------"

time ./tsp < simple.in

echo "------------------"

time ./tsp-par < simple.in
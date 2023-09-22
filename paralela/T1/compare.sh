#!/bin/bash

make clean
make

echo "------------------"

time ./tsp < simple.in

echo "------------------"

time ./tsp-par < simple.in
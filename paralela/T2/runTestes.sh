#!/usr/bin/bash

for file in ex/*.in; do
   cp $file simple.in
   NAME=$(basename $file)
   echo $NAME
   ./compare.py -e
done

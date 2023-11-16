#!/usr/bin/bash

for file in ex/*.in; do
   cp $file simple.in
   NAME=$(basename $file)
   echo $NAME
   if [[ "$NAME" != "tsp.in" ]];then
      ./compare -e
   else
      ./compare -e -p
   fi
done
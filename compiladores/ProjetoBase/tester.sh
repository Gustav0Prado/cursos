#!/bin/bash

files=$(find ../PgmasTomasz/ -name Exemplo*)

cd ./src
make clean > /dev/null
make > /dev/null
for f in $files; do
   ./compilador "../$f/pgma.pas" > /dev/null
   diff MEPA "../$f/MEPA" > /dev/null
   if [ $? -eq 1 ]; then
      echo "ERRO NO EXEMPLO - $f"
   fi
done
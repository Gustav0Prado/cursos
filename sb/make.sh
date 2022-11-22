#!/bin/bash

shopt -s extglob

for i in "$@"
do
   if [ "$i" = "--clean" -o "$i" = "-c" ]; then
      rm -v !(*.s|*.pdf|*.sh|.gitignore)
   else
      as $i.s -o $i.o
      ld $i.o -o $i
      ./$i
      echo $?
   fi
done
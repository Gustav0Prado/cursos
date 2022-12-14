#!/bin/bash

#set -x #echo on
shopt -s extglob

args=("$@")
last=${args[$#-1]}
i=(${args[0]})

if [ "$last" = "--clean" -o "$last" = "-c" ]; then
   rm -fv !(*.s|*.pdf|*.sh|.gitignore)
elif [ "$last" = "--printf" -o "$last" = "-p" ]; then
   as $i.s -o $i.o -g
   ld $i.o -o $i -dynamic-linker /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 \
   /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o \
   /usr/lib/x86_64-linux-gnu/crtn.o -lc
   ./$i
else
   as $i.s -o $i.o -g
   ld $i.o -o $i
   ./$i
   echo $?
fi

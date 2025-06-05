#!/usr/bin/bash
clear && make clean && make && diff <(./teste < exemplos/$1.in) exemplos/$1.out
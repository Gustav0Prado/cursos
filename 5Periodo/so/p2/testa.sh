#!/bin/bash
make task=pingpong-tasks1.c
./a.out | diff pingpong-tasks1.txt -

make task=pingpong-tasks2.c
./a.out | diff pingpong-tasks2.txt -

make task=pingpong-tasks3.c
./a.out | diff pingpong-tasks3.txt -

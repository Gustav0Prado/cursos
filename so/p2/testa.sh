#!/bin/bash
cc -Wall ppos_core.c pingpong-tasks1.c
./a.out | diff pingpong-tasks1.txt -

cc -Wall ppos_core.c pingpong-tasks2.c
./a.out | diff pingpong-tasks2.txt -

cc -Wall ppos_core.c pingpong-tasks3.c
./a.out | diff pingpong-tasks3.txt -
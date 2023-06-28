#!/usr/bin/python3

import random, sys

with open('exemplos/exRand.in', 'w+') as file:
   h = int(sys.argv[1])
   c = int(sys.argv[2])
   a = int(sys.argv[3])
   
   chosen = []

   file.write(f"{h} {c} {a}\n")
   for i in range(c+a):
      while True:
         x = random.randint(1, h)
         y = random.randint(1, h)
         if (x != y) and ((x,y) not in chosen):
            break
      chosen.append((x, y))
      
   for (x, y) in chosen:
      file.write(f"{x} {y}\n")
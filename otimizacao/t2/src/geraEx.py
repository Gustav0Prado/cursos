#!/usr/bin/python3

import random

with open('exemplos/exRand.in', 'w+') as file:
   file.write("20 10 5\n")
   for i in range(15):
      while True:
         a = random.randint(1, 20)
         b = random.randint(1, 20)
         if a != b:
            break
      
      file.write(f"{a} {b}\n")
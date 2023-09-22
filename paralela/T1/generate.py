#!/usr/bin/python3

import random

f = open("simple.in", "w")

inst = random.randint(1,3)

f.write(f"{inst}\n");

for i in range(inst):
    towns = random.randint(5, 8)
    f.write(f"{towns}\n")
    for j in range(towns):
        f.write(f"{random.randint(0, 150)} {random.randint(0, 150)}\n")
#!/usr/bin/python3

import random

f = open("simple.in", "w")

f.write("1\n");

towns = random.randint(5, 8)

f.write(f"{towns}\n")

for i in range(towns):
    f.write(f"{random.randint(0, 150)} {random.randint(0, 150)}\n")
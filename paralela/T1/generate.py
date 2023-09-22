#!/usr/bin/python3

import random

def generateExample(maxInst, minTowns, maxTowns):
    f = open("simple.in", "w")

    inst = random.randint(1, maxInst)

    f.write(f"{inst}\n");

    for i in range(inst):
        towns = random.randint(minTowns, maxTowns)
        f.write(f"{towns}\n")
        for j in range(towns):
            f.write(f"{random.randint(0, 150)} {random.randint(0, 150)}\n")
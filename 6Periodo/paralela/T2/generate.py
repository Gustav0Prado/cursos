#!/usr/bin/python3

import random

def generateExample(inst, minTowns, maxTowns):
    f = open("simple.in", "w")

    f.write(f"{inst}\n");

    for i in range(inst):
        towns = random.randint(minTowns, maxTowns)
        f.write(f"{towns}\n")
        for j in range(towns):
            f.write(f"{random.randint(0, 150)} {random.randint(0, 150)}\n")
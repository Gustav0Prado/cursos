#!/usr/bin/python3

n = int(input())

# Procura primeiro e segundo fator
for i in range(2, 1025):
    if n % i == 0: break
print(i)

for j in range(i+1, 1025):
    if n % j == 0: break
print(j)
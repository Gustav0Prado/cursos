#!/usr/bin/python3

import sys, math

# -----------------------------------------------
# Le entrada padrao
if len(sys.argv) != 4:
    print("ERRO! Uso do programa: ./RSA <texto> <N> <E>")
    exit()

texto = list(map(int, sys.argv[1].split(' ')))
N = int(sys.argv[2])
E = int(sys.argv[3])

# -----------------------------------------------
# Procura primeiro e segundo fator
for p in range(2, 1025):
    if N % p == 0: break
print(f'p = {p}')

for q in range(p+1, 1025):
    if N % q == 0: break
print(f'q = {q}')

# -----------------------------------------------
# Calcula a chave privada
phi = (p-1) * (q-1)
priv = (phi + 1) / E
print(f'Chave privada = {priv:.0f}')

# -----------------------------------------------
# Usa exponenciacao modular pra calcular texto descriptografado
texto_final = ""
for t in texto:
    texto_descripto = 1
    i = 0
    while i < priv:
        i += 1
        texto_descripto = (t * texto_descripto) % N
    texto_final += str(texto_descripto) + " "

print(texto_final)
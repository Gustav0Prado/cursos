#!/usr/bin/python3
import sys, math

# -----------------------------------------------
# Le entrada padrao
if len(sys.argv) != 4:
    print("ERRO! Uso do programa: ./RSA <texto> <N> <E>")
    exit()

texto = [ord(i) for i in sys.argv[1]]
N = int(sys.argv[2])
E = int(sys.argv[3])

# -----------------------------------------------
# Usa exponenciacao modular pra calcular texto descriptografado
texto_final = []
for t in texto:
    texto_descripto = 1
    i = 0
    while i < E:
        i += 1
        texto_descripto = (t * texto_descripto) % N
    texto_final.append(f'{texto_descripto}')
print(f'Texto criptografado = {''.join(texto_final)}')
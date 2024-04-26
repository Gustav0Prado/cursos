#!/usr/bin/python3
# Fiz esse script para consegui usar os exemplos dados dentro do prolog
import sys, subprocess, ast

if ((len(sys.argv) != 2) or (not ".in" in sys.argv[1])):
    print("Uso do script: ./wumpus.py ./exemplos/{nome_do_arquivo}.in")
    exit()

with open(sys.argv[1]) as file:
    N = int(file.readline())
    L = []
    for i in range(N):
        L.append([int(s) for s in file.readline().split(' ')])

cmd = f"swipl -s src/main.pl -g wumpus_simplificado({N},{str(L).replace(' ', '')}). -g halt"
print(cmd)
clist = cmd.split(' ')

result = subprocess.run(clist, stdout=subprocess.PIPE)
print(result.stdout.decode().rstrip())

# Printa a matriz com o caminho percorrido usando setinhas (isso eh mais por curiosidade mesmo)
print("\nCaminho percorrido:")

pos = ast.literal_eval(result.stdout.decode().split('-> ')[1])

M =[]
for i in range(N):
    B = []
    for j in range(N):
        B.append(str(L[i][j]).replace('3', '➌'))
    M.append(B)

for elem,next_elem in zip(pos, pos[1:]):
    # Foi pra direita
    if (elem[0] == next_elem[0]) and (elem[1] < next_elem[1]):
        (i, j) = elem[0], elem[1]
        M[i][j] = '▸'

    # Foi pra cima
    if (elem[0] > next_elem[0]) and (elem[1] == next_elem[1]):
        (i, j) = elem[0], elem[1]
        M[i][j] = '▴'

    # Foi pra esquerda
    if (elem[0] == next_elem[0]) and (elem[1] > next_elem[1]):
        (i, j) = elem[0], elem[1]
        M[i][j] = '◂'

    # Foi pra baixo
    if (elem[0] < next_elem[0]) and (elem[1] == next_elem[1]):
        (i, j) = elem[0], elem[1]
        M[i][j] = '▾'

for l in M:
    print(' '.join(l))
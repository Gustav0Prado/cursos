#! /usr/bin/python3
# Gustavo do Prado Silva - GRR20203942
import sys, math, itertools

clausulas = []
num_var = 0
num_clausulas = 0

def bit_to_var(b:list, cl:list, tam:int):
   res = []
   cl2 = cl.copy()

   for i in range(tam):
      if(cl[i] < 0): cl2[i] = -cl[i]
      
   for i in range(tam):
      if(b[i] == '1'): res.append(cl2[i])
      else: res.append(-cl2[i])
   return res

def permut_valida(b:list, cl: list, tam: int):
   res = 0
   for i in range(tam):
      if (cl[i] > 0): res += int(b[i])
      elif(b[i] == '0'): res += 1
   return (res > 0)
   

def restr_validos(cl:list):
   permutacoes = []
   # Cria uma lista com todas as permutacoes de bits de tamanho igual ao da clausula
   bits = ["".join(seq) for seq in itertools.product("01", repeat=len(cl))]
   for b in bits:
      p = bit_to_var(b, cl, len(cl))
      if (permut_valida(b, cl, len(cl))):
         permutacoes.append(' '.join([str(x) for x in p]))
   print(f'{len(permutacoes)} {" ".join(permutacoes)}')

# Leitura do arquivo de entrada
with open(sys.argv[1]) as entrada:
   for line in entrada:
      token = line.strip('\n').split(' ')

      # Achou declaracao da cnf
      if (token[0] == 'p'):
         num_var = int(token[2])
         num_clausulas = int(token[3])

      # Achou declaracao das clausulas
      if (token[0] != 'c') and (token[0] != 'p'):
         token = [int(x) for x in token]
         clausulas.append(token[:-1])

# print(f'{clausulas}\n')

# Printa variáveis, podem ser negativas (negadas/falso) ou positivas (verdadeiras)
print(num_var)
for i in range(num_var):
   print(f'2 {-(i+1)} {i+1}')

# Printa restrições
print(num_clausulas)
for cl in clausulas:
   print('V')
   print(f'{len(cl)} {" ".join(str(x).strip("-") for x in cl)}')
   restr_validos(cl)
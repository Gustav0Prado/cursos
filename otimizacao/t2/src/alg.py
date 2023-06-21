import sys
from hero import *

nodes = 0
optL = []
optR = []
optConflict = 1000000;

# Chamada recusriva de enumeração, cortando os ramos não viáveis
def Backtrack(choice:list, left:list, right:list, n:int):
   """Processamento sem cortes de otimalidade

   Args:
       choice (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       n (int): número de heróis ainda não escolhidos
   """


   global nodes, optL, optR, optConflict
   nodes += 1

   if(n == 0):
      c = num_conflicts(left, right)
      if(c < optConflict):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      next = choice[0]

      # enumera escolhas do próximos elementos (sem a última escolha)
      # mas apenas caso seja viável (grupo não vazio)

      if len(left)  <= n and (has_affinity(left, next) or not has_affinity(right, next)) :
         Backtrack(choice[1:], left + [next], right, n-1)
      if len(right) <= n and (has_affinity(right, next) or not has_affinity(left, next)) :
         Backtrack(choice[1:], left, right + [next], n-1)


# Chamada recusriva de enumeração (Sem optimalidade e viabilidade)
def Enumerate(choice:list, left:list, right:list, n:int):
   """Processamento sem cortes de viabilidade

   Args:
       choice (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       l (int): nú mero de heróis já escolhidos
   """

   global nodes, optL, optR, optConflict
   nodes += 1

   if(n == 0):
      c = num_conflicts(left, right)
      if(c < optConflict):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      next = choice[0]
      # enumera escolhas do próximos elementos (sem a última escolha)
      Enumerate(choice[1:], left + [next], right, n-1)
      Enumerate(choice[1:], left, right + [next], n-1)


def print_saida(first:Hero, time:float):
   """Gera saida do programa na stdout e stderr

   Args:
       first (Hero): Primeiro heroi
       time (float): Tempo gasto no processamento
   """
   
   global nodes, optL, optR, optConflict

   print(optConflict)
   if first in optL:
      print(' '.join(map(str, optL)))
   else:
      print(optR)
   print(f"{nodes} Nós na árvore e { time * 1000 } milissegundos de execução", file=sys.stderr)
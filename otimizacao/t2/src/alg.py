import sys
from hero import *

nodes = 0
optL = []
optR = []
optConflict = 1000000;

def restriction(nextChoice:Hero, a:list, b:list, n:int) -> bool:
   """Checa se restrição do Backtracking é verdadeira

   Args:
       a (list): Grupo em que elemento sera inserido
       b (list): O outro grupo
       n (int): Quantidade de herois já escolhidos

   Returns:
       bool: Retorna se a restrição é verdadeira ou falsa
   """
   return len(a) < n-1 and (has_affinity(a, nextChoice) or not has_affinity(b, nextChoice))


def Bcriada(C:list, a:list, b:list) -> int:
   """Função Bdada dos professores

   Args:
       choices (list): Herois com groupo ainda não escolhido
       a (list): 1° grupo com herois já escolhidos
       b (list): 2° grupo com herois já escolhidos

   Returns:
       int: Número de triângulos de conflito com heróis ainda não escolhidos
   """
   return (num_conflicts(a, b) + num_triangles(C))


def Bdada(C:list, a:list, b:list) -> int:
   """Função Bdada dos professores

   Args:
       choices (list): Herois com groupo ainda não escolhido
       a (list): 1° grupo com herois já escolhidos
       b (list): 2° grupo com herois já escolhidos

   Returns:
       int: Número de triângulos de conflito com heróis ainda não escolhidos
   """
   return (num_conflicts(a, b) + num_triangles(C))



# Chamada recusriva de enumeração, cortando os ramos não viáveis
def BranchAndBound(choices:list, left:list, right:list, l:int, n:int, B):
   """Processamento sem cortes de otimalidade

   Args:
       choices (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       n (int): número de heróis ainda não escolhidos
   """


   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right)
      if(c < optConflict):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      nextChoice = choices[0]

      if B(choices, left, right) <= optConflict:
         if restriction(nextChoice, left, right, n) :
            BranchAndBound(choices[1:], left + [nextChoice], right, l+1, n, B)

         if restriction(nextChoice, right, left, n):
            BranchAndBound(choices[1:], left, right + [nextChoice], l+1, n, B)


# Chamada recusriva de enumeração, cortando os ramos não viáveis
def Backtrack(choices:list, left:list, right:list, l:int, n:int):
   """Processamento sem cortes de otimalidade

   Args:
       choices (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       n (int): número de heróis ainda não escolhidos
   """


   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right)
      if(c < optConflict):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      nextChoice = choices[0]

      if restriction(nextChoice, left, right, n) :
         Backtrack(choices[1:], left + [nextChoice], right, l+1, n)

      if restriction(nextChoice, right, left, n):
         Backtrack(choices[1:], left, right + [nextChoice], l+1, n)


# Chamada recusriva de enumeração (Sem optimalidade e viabilidade)
def Enumerate(choices:list, left:list, right:list, l:int, n:int):
   """Processamento sem cortes de viabilidade

   Args:
       choices (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       l (int): nú mero de heróis já escolhidos
   """

   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right)
      if(c < optConflict and affinities_ok(left, right)):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      next = choices[0]
      # enumera escolhas do próximos elementos (sem a última escolha)
      Enumerate(choices[1:], left + [next], right, l+1, n)
      Enumerate(choices[1:], left, right + [next], l+1, n)


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
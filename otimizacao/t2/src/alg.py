import sys
from hero import *

nodes = 0
optL = []
optR = []
optConflict = 1000000;

def restriction(flag:bool, nextChoice:int, a:list, b:list, af:set, n:int) -> bool:
   """Checa se restrição do Backtracking é verdadeira

   Args:
       flag(bool): Flag de corte de viabilidade
       a (list): Grupo em que elemento sera inserido
       b (list): O outro grupo
       n (int): Quantidade de herois já escolhidos

   Returns:
       bool: Retorna se a restrição é verdadeira ou falsa
   """
   if(not flag):
      return True
   return len(a) < n-1 and (has_affinity(a, nextChoice, af) or not has_affinity(b, nextChoice, af))


def Bcriada(flags:Flags, C:list, a:list, b:list) -> int:
   """Função Bdada dos professores

   Args:
       heroes (list): Herois com groupo ainda não escolhido
       a (list): 1° grupo com herois já escolhidos
       b (list): 2° grupo com herois já escolhidos

   Returns:
       int: Número de triângulos de conflito com heróis ainda não escolhidos
   """
   if (not flags.o):
      return True
   return (num_conflicts(a, b, C) + num_triangles(C))


def Bdada(flags:Flags, C:list, a:list, b:list) -> int:
   """Função Bdada dos professores

   Args:
       C (list): Lista de conflitos
       a (list): 1° grupo com herois já escolhidos
       b (list): 2° grupo com herois já escolhidos

   Returns:
       int: Número de triângulos de conflito com heróis ainda não escolhidos
   """
   if (not flags.o):
      return True
   return (num_conflicts(a, b, C) + num_triangles(C))


def Recursion(heroes:list, af:set, conf:set,  left:list, right:list, l:int, n:int, B, flags:Flags):
   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right, conf)
      if(c < optConflict and affinities_ok(left, right, af)):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      nextChoice = heroes[0]

      if B(flags, conf, left, right) <= optConflict:
         if restriction(flags.f, nextChoice, left, right, af, n) :
            Recursion(heroes[1:], af, conf, left + [nextChoice], right, l+1, n, B, flags)

         if restriction(flags.f, nextChoice, right, left, af, n):
            Recursion(heroes[1:], af, conf, left, right + [nextChoice], l+1, n, B, flags)


# Chamada recusriva de enumeração, cortando os ramos não viáveis
def BranchAndBound(heroes:list, af:set, conf:set,  left:list, right:list, l:int, n:int, B):
   """Processamento sem cortes de otimalidade

   Args:
       heroes (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       n (int): número de heróis ainda não escolhidos
   """


   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right, conf)
      if(c < optConflict):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      nextChoice = heroes[0]

      if B(conf, left, right) <= optConflict:
         if restriction(nextChoice, left, right, af, n) :
            BranchAndBound(heroes[1:], af, conf, left + [nextChoice], right, l+1, n, B)

         if restriction(nextChoice, right, left, af, n):
            BranchAndBound(heroes[1:], af, conf, left, right + [nextChoice], l+1, n, B)


# Chamada recusriva de enumeração, cortando os ramos não viáveis
def Backtrack(heroes:list, af:set, conf:set,  left:list, right:list, l:int, n:int):
   """Processamento sem cortes de otimalidade

   Args:
       heroes (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       n (int): número de heróis ainda não escolhidos
   """


   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right, conf)
      if(c < optConflict):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      nextChoice = heroes[0]

      if restriction(nextChoice, left, right, af, n) :
         Backtrack(heroes[1:], af, conf, left + [nextChoice], right, l+1, n)

      if restriction(nextChoice, right, left, af, n):
         Backtrack(heroes[1:], af, conf, left, right + [nextChoice], l+1, n)


# Chamada recusriva de enumeração (Sem optimalidade e viabilidade)
def Enumerate(heroes:list, af:set, conf:set, left:list, right:list, l:int, n:int):
   """Processamento sem cortes de viabilidade

   Args:
       heroes (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       l (int): nú mero de heróis já escolhidos
   """

   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right, conf)
      if(c < optConflict and affinities_ok(left, right, af)):
         optL = left
         optR = right
         optConflict = c
      return
   else:
      next = heroes[0]
      # enumera escolhas do próximos elementos (sem a última escolha)
      Enumerate(heroes[1:], af, conf ,left + [next], right, l+1, n)
      Enumerate(heroes[1:], af, conf, left, right + [next], l+1, n)


def print_saida(first:int, time:float):
   """Gera saida do programa na stdout e stderr

   Args:
       first (int): Primeiro heroi
       time (float): Tempo gasto no processamento
   """
   
   global nodes, optL, optR, optConflict

   print(optConflict)
   if first in optL:
      print(' '.join(map(str, optL)))
   else:
      print(optR)
   print(f"{nodes} Nós na árvore e { time * 1000 } segundo(s) de execução", file=sys.stderr)
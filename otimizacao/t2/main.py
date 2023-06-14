#!/bin/python3

import sys, time

# Vars globais
n = -1
nodes = 0
optL = []
optR = []
optConflict = 1000000;

class Hero:
   def __init__(self, id):
      self.conflicts = []
      self.affinities = []
      self.id = id

   def __str__(self):
      return str(self.id)
   
   def __repr__(self):
      return str(self.id)


def individual_conflicts(subject:Hero, team:list) -> int:
   """Retorna quantos conflitos há com o herói subject na lista team

   Args:
       subject (Hero): Herói que terá conflitos buscados
       team (list): Grupo de heróis onde serão procurados conflitos

   Returns:
       int: Número de conflitos com o herói subject
   """
   c = 0

   for hero in team:
      if subject in hero.conflicts:
         c += 1
   
   return c


def num_conflicts(left:list, right:list) -> int:
   """Calcula o número total de conflitos nos dois grupos de heróis

   Args:
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"

   Returns:
       int: Número de conflitos
   """
   conf = 0

   for hero in left:
      for conflict in hero.conflicts:
         if conflict in left:
            conf += 1
   
   for hero in right:
      for conflict in hero.conflicts:
         if conflict in right:
            conf += 1

   return conf


def has_affinity(subject:Hero, team:list) -> bool:
   """Retorna se um alguem do grupo team tem afinidade com subject

   Args:
       subject (Hero): Herói que será comparado
       team (list): Time de heróis em que a afinidade será buscada

   Returns:
       bool: True caso alguém tenha afinidade e False caso contrário
   """

   for h in team:
      for af in h.affinities:
         if af.id == subject.id:
            return True
   
   return False

# Chamada recusriva de enumeração, cortando os ramos não viáveis
def backtrack(choice:list, left:list, right:list, l:int):
   """Processamento sem cortes de otimalidade

   Args:
       choice (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       l (int): nú mero de heróis já escolhidos
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
      next = choice[0]
      # enumera escolhas do próximos elementos (sem a última escolha)
      # mas apenas caso seja viável (grupo não vazio)
      if(len(right) < n-1):
         backtrack(choice[1:], left + [next], right, l+1)
      if(len(left) < n-1):
         backtrack(choice[1:], left, right + [next], l+1)


# Chamada recusriva de enumeração (Sem optimalidade e viabilidade)
def enumerate(choice:list, left:list, right:list, l:int):
   """Processamento sem cortes de viabilidade

   Args:
       choice (list): Lista com todos os heróis que ainda não foram escolhidos para um grupo
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"
       l (int): nú mero de heróis já escolhidos
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
      next = choice[0]
      # enumera escolhas do próximos elementos (sem a última escolha)
      enumerate(choice[1:], left + [next], right, l+1)
      enumerate(choice[1:], left, right + [next], l+1)


def print_saida(first:Hero, time:float):
   """Gera saida do programa na stdout e stderr

   Args:
       first (Hero): Primeiro heroi
       time (float): Tempo gasto no processamento
   """
   print(optConflict)
   if first in optL:
      print(' '.join(map(str, optL)))
   else:
      print(optR)
   print(f"{nodes} Nós na árvore e { time * 1000 } milissegundos de execução", file=sys.stderr)


def main():
   global n, nodes, optL, optR, optConflict

   choice = []
   left = []
   right = []

   # Le n, k e m da entrada padrão
   inp = input()
   inp = inp.split()
   n = int(inp[0])
   k = int(inp[1])
   m = int(inp[2])

   # Cria lista com n heróis
   for i in range(n):
      choice.append(Hero(i+1))

   # Le os k conflitos
   for i in range(k):
      inp = input()
      inp = inp.split()

      index0 = int(inp[0]) - 1
      index1 = int(inp[1]) - 1

      # Inclui conflito na lista do primeiro heroi citado
      choice[index0].conflicts.append(choice[index1])

   # Le as m afinidades
   for i in range(m):
      inp = input()
      inp = inp.split()

      index0 = int(inp[0]) - 1
      index1 = int(inp[1]) - 1

      # Inclui afinidades na lista do primeiro heroi citado
      choice[index0].affinities.append(choice[index1])

   # Caso a linha de comando tenha alguma opção
   if len(sys.argv) == 2:

      #sem otimalidade
      if(sys.argv[1] == "-o"):
         timer = time.time()
         backtrack(choice, left, right, 0)
         print_saida(choice[0], (time.time() - timer) )

      # sem viabilidade
      elif(sys.argv[1] == "-f"):
         timer = time.time()
         enumerate(choice, left, right, 0)
         print_saida(choice[0], (time.time() - timer) )
         
      # elif(sys.argv[1] == "-a"):
      #    # funcao dada
   #else:
      # BB normal


# define main
if __name__ == "__main__":
   main()
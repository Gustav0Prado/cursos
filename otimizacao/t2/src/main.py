#!/bin/python3

import sys, time
from alg import *

# define main
if __name__ == "__main__":
   heroes = []
   conflicts = set()
   affinities = set()
   
   left = []
   right = []

   # Le n, k e m da entrada padrão
   inp = input().split()
   n = int(inp[0])
   k = int(inp[1])
   m = int(inp[2])

   # Cria lista com n heróis
   for i in range(n):
      heroes.append(i+1)

   # Le os k conflitos
   for i in range(k):
      inp = input().split()

      index0 = int(inp[0])
      index1 = int(inp[1])

      # Inclui conflito na lista do primeiro heroi citado
      if(index0 < index1):
         conflicts.add(tuple([index0, index1]))
      else:
         conflicts.add(tuple([index1, index0]))

   # Le as m afinidades
   for i in range(m):
      inp = input().split()

      index0 = int(inp[0])
      index1 = int(inp[1])

      # Inclui conflito na lista do primeiro heroi citado
      if(index0 < index1):
         affinities.add(tuple([index0, index1]))
      else:
         affinities.add(tuple([index1, index0]))

   # Caso a linha de comando tenha alguma opção
   if len(sys.argv) == 2:

      #sem otimalidade
      if(sys.argv[1] == "-o"):
         timer = time.time()
         Backtrack(heroes, affinities, conflicts, left, right, 0, n)
         print_saida(heroes[0], (time.time() - timer) )

      # sem viabilidade
      elif(sys.argv[1] == "-f"):
         timer = time.time()
         Enumerate(heroes, affinities, conflicts,  left, right, 0, n)
         print_saida(heroes[0], (time.time() - timer) )
         
      elif(sys.argv[1] == "-a"):
         timer = time.time()
         BranchAndBound(heroes, affinities, conflicts,  left, right, 0, n, Bdada)
         print_saida(heroes[0], (time.time() - timer) )
   else:
      print(f"\t{num_triangles(heroes)} triângulo(s)")
      timer = time.time()
      BranchAndBound(heroes, affinities, conflicts,  left, right, 0, n, Bcriada)
      print_saida(heroes[0], (time.time() - timer) )
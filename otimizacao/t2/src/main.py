#!/bin/python3

import sys, time
from hero import Hero
from alg import *

# define main
if __name__ == "__main__":
   choices = []
   left = []
   right = []

   # Le n, k e m da entrada padrão
   inp = input().split()
   n = int(inp[0])
   k = int(inp[1])
   m = int(inp[2])

   # Cria lista com n heróis
   for i in range(n):
      choices.append(Hero(i+1))

   # Le os k conflitos
   for i in range(k):
      inp = input().split()

      index0 = int(inp[0]) - 1
      index1 = int(inp[1]) - 1

      # Inclui conflito na lista do primeiro heroi citado
      choices[index0].conflicts.append(choices[index1])

   # Le as m afinidades
   for i in range(m):
      inp = input().split()

      index0 = int(inp[0]) - 1
      index1 = int(inp[1]) - 1

      # Inclui afinidades na lista do primeiro heroi citado
      # guarda sempre no de menor indice
      if(index0 < index1):
         choices[index0].affinities.append(choices[index1])
      else:
         choices[index1].affinities.append(choices[index0])

   # Caso a linha de comando tenha alguma opção
   if len(sys.argv) == 2:

      #sem otimalidade
      if(sys.argv[1] == "-o"):
         timer = time.time()
         Backtrack(choices, left, right, 0, n)
         print_saida(choices[0], (time.time() - timer) )

      # sem viabilidade
      elif(sys.argv[1] == "-f"):
         timer = time.time()
         Enumerate(choices, left, right, 0, n)
         print_saida(choices[0], (time.time() - timer) )
         
      elif(sys.argv[1] == "-a"):
         timer = time.time()
         BranchAndBound(choices, left, right, 0, n, Bdada)
         print_saida(choices[0], (time.time() - timer) )
   else:
      print(f"\t{num_triangles(choices)} triângulo(s)")
      timer = time.time()
      BranchAndBound(choices, left, right, 0, n, Bcriada)
      print_saida(choices[0], (time.time() - timer) )
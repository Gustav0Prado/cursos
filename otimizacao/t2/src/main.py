#!/bin/python3

import sys, time
from hero import Hero
from alg import *

# define main
if __name__ == "__main__":
   choice = []
   left = []
   right = []

   # Le n, k e m da entrada padrão
   inp = input().split()
   n = int(inp[0])
   k = int(inp[1])
   m = int(inp[2])

   # Cria lista com n heróis
   for i in range(n):
      choice.append(Hero(i+1))

   # Le os k conflitos
   for i in range(k):
      inp = input().split()

      index0 = int(inp[0]) - 1
      index1 = int(inp[1]) - 1

      # Inclui conflito na lista do primeiro heroi citado
      choice[index0].conflicts.append(choice[index1])

   # Le as m afinidades
   for i in range(m):
      inp = input().split()

      index0 = int(inp[0]) - 1
      index1 = int(inp[1]) - 1

      # Inclui afinidades na lista do primeiro heroi citado
      choice[index0].affinities.append(choice[index1])

   # Caso a linha de comando tenha alguma opção
   if len(sys.argv) == 2:

      #sem otimalidade
      if(sys.argv[1] == "-o"):
         timer = time.time()
         Backtrack(choice, left, right, n)
         print_saida(choice[0], (time.time() - timer) )

      # sem viabilidade
      elif(sys.argv[1] == "-f"):
         timer = time.time()
         Enumerate(choice, left, right, n)
         print_saida(choice[0], (time.time() - timer) )
         
      # elif(sys.argv[1] == "-a"):
      #    # funcao dada
   #else:
      # BB normal
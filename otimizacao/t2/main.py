#!/bin/python3

import sys

n = 3
nodes = 0

# Chamada recusriva de enumeração, cortando os ramos não viáveis
def backtrack(choice, left, right, l):
   global nodes
   
   nodes += 1

   if(l == n):
      print(f"{str(left) : <12} | {str(right) : <12}")
      # if solucao otima: salva
      return
   else:
      next = choice[0]
      # enumera escolhas do próximos elementos (sem a última escolha)
      # mas apenas caso seja viável (grupo não vazio)
      if(len(left) < n-1):
         backtrack(choice[1:], left + [next], right, l+1)
      if(len(right) < n-1):
         backtrack(choice[1:], left, right + [next], l+1)


# Chamada recusriva de enumeração (Sem optimalidade e viabilidade)
def enumerate(choice, left, right, l):
   global nodes

   nodes += 1

   if(l == n):
      print(f"{str(left) : <12} | {str(right) : <12}")
      # if solucao otima: salva
      return
   else:
      next = choice[0]
      # enumera escolhas do próximos elementos (sem a última escolha)
      enumerate(choice[1:], left + [next], right, l+1)
      enumerate(choice[1:], left, right + [next], l+1)


def main():
   global nodes

   choice = []
   left = []
   right = []
   optList = []
   optConflict = -1

   #inicializa lista de escolhas
   for i in range(n):
      choice.append(i+1)

   # sem otimalidade
   # if(sys.argv[1] == "-o"):
   #    backtrack(choice, left, right, 0)

   # # sem viabilidade
   # elif(sys.argv[1] == "-f"):
   #    enumerate(choice, left, right, 0)
      
   # elif(sys.argv[1] == "-a"):
   #    # funcao dada

   enumerate(choice, left, right, 0)

   print(f"\t{nodes} Nós na árvore", file=sys.stderr)

   nodes = 0
   backtrack(choice, left, right, 0)
   print(f"\t{nodes} Nós na árvore", file=sys.stderr)


# define main
if __name__ == "__main__":
   main()
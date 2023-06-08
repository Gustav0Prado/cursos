#!/bin/python3

n = 4

# Chamada recusribva de enumeração (Sem optimalidade e viabilidade)
def tree(choice, left, right, l):
   if(l == n):
      print(f"{str(left) : <12} | {str(right) : <12}")
      # if solucao otima: salva
      return
   else:
      next = choice[0]
      tree(choice[1:], left + [next], right, l+1)
      tree(choice[1:], left, right + [next], l+1)


def main():
   choice = []
   left = []
   right = []
   optList = []
   optConflict = -1

   #inicializa lista de escolhas
   for i in range(n):
      choice.append(i+1)

   # Primeira chamada
   tree(choice, left, right, 0)


if __name__ == "__main__":
   main()
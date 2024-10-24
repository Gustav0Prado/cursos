#!/usr/bin/python3

import random, time

def swap(l:list, pos1:int, pos2:int) -> list:
   l[pos1], l[pos2] = l[pos2], l[pos1]
   return l


def timestamp() -> int:
   return int(time.time()*1000)


def particiona(A:list, lo:int, hi:int) -> int:
   pivo = A[hi]
   i = lo - 1

   for j in range(lo, hi):
      if A[j] < pivo:
         i += 1
         swap(A, i, j)
   
   if pivo < A[i+1]:
      swap(A, i+1, hi)

   return i+1


def quicksort(A:list, lo:int, hi:int):
   if lo < hi:
      p = particiona(A, lo, hi)
      quicksort(A, lo, p-1)
      quicksort(A, p+1, hi)


def BubbleSort(v:list, n:int):
   if n < 1: return

   for i in range(n):
      for j in range(n-i-1):
         if v[j] > v[j+1]:
            swap(v, j, j+1)


if __name__ == "__main__":
   size = int(input("Tamanho do vetor: "))

   array = []
   qArr  = []
   bArr  = []

   # Cria array com numeros em posicoes aleatorias
   for i in range(size):
      while True:
         x = random.randint(1, size)
         if x not in array:
            array.append(x)
            break
   

   # Copia array
   qArr = array.copy()
   bArr = array.copy()

   # Executa Quicksort
   t1 = timestamp()
   quicksort(qArr, 0, size-1)
   t2 = timestamp()
   print(f"Quicksort:  {t2-t1} ms")

   # Executa BubbleSort
   t1 = timestamp()
   BubbleSort(bArr, size)
   t2 = timestamp()
   print(f"BubbleSort: {t2-t1} ms")

   array.sort()

   if (qArr != array):
      print("ERRO NO QUICKSORT!!")
      print("\t", array)
      print("\t", qArr)

   if (bArr != array):
      print("ERRO NO BUBBLESORT!!")
      print("\t", array)
      print("\t", bArr)

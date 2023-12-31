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
   # Caso o outro time nâo vá ficar vazio e as afinidades estejam corretas
   # (Vai obrigatoriamente para um lado caso tenha afinidade ou pode ir pros dois caso nâo tenha com ninguém)
   if len(a) < n-1:
      # Se tem afinidade com os dois lados, árvore não é viável
      if (has_affinity(a, nextChoice, af) and has_affinity(b, nextChoice, af)):
         return False
      elif (has_affinity(a, nextChoice, af)):
         return True
      # Não tem afinidade com nenhum dos dois lados
      elif(not has_affinity(b, nextChoice, af)):
         return True
   return False


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
   return (num_conflicts(a, b, C) + num_pentagon(a+b, C))


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
   return (num_conflicts(a, b, C) + num_triangles(a+b, C))


def Recursion(heroes:list, af:set, conf:set,  left:list, right:list, l:int, n:int, B, flags:Flags):
   global nodes, optL, optR, optConflict
   nodes += 1

   if(l == n):
      c = num_conflicts(left, right, conf)
      if(c < optConflict):
         # Sem viabilidade, checa se é viável
         if(not flags.f and affinities_ok(left, right, af)):
            optL = left
            optR = right
            optConflict = c
         # Com cortes de viabilidade, apenas salva solução
         elif(flags.f):
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
   # print(f"{nodes} Nós na árvore e { (time * 1000) } milisegundo(s) de execução", file=sys.stderr)
   print(f"{nodes} { (time * 1000) }", file=sys.stderr)
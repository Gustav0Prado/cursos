#!/usr/bin/python3
# Gustavo do Prado Silva - GRR20203942

import sys

class Dominio:
   def __init__(self, tamanho, valores):
      self.tamanho = tamanho
      self.valores = valores

   def __str__(self):
      return "\tTamanho do domínio = " + str(self.tamanho) + "\n\tValores do domínio = " + str(self.valores)
   
class Restricao:
   def __init__(self, tipo, tamanho_escopo, escopo, tamanho_tuplas, tuplas):
      self.tipo = tipo
      self.tamanho_escopo = tamanho_escopo
      self.escopo = escopo
      self.tamanho_tuplas = tamanho_tuplas
      self.tuplas = tuplas

   def __str__(self):
      saida  = "\tTipo da restricao = " + str(self.tipo) + "\tTamanho do escopo = " + str(self.tamanho_escopo) + "\n\tEscopo = " + str(self.escopo)
      saida += "\n\tTamanho do tuplas = " + str(self.tamanho_tuplas) + "\n\tTuplas = " + str(self.tuplas)
      return saida

def split(lista, tam):
   res = []
   while lista != []:
      l = []
      for i in range(tam):
         l.append(lista.pop(0))
      res.append(l)
   return res


dominio_problema    = []
restricoes_problema = []
num_var  = 0
num_rest = 0

with open(sys.argv[1]) as entrada:
   num_var = int(entrada.readline())
   for i in range(num_var):
      linha = entrada.readline()
      res = [eval(i) for i in linha.strip('\n').split(' ')]
      
      dominio_xn = Dominio(res[0], res[1:])
      dominio_problema.append(dominio_xn)

   num_rest = int(entrada.readline())
   for i in range(num_rest):
      linha_tipo   = entrada.readline()
      linha_escopo = entrada.readline()
      linha_tuplas = entrada.readline()
      
      res_escopo = [eval(i) for i in linha_escopo.strip('\n').split(' ')]
      res_tuplas = [eval(i) for i in linha_tuplas.strip('\n').split(' ')]
      
      restricao_n = Restricao(linha_tipo, res_escopo[0], res_escopo[1:], res_tuplas[0], split(res_tuplas[1:], res_tuplas[0]))
      restricoes_problema.append(restricao_n)

for i in range(num_var):
   print(f'Variável {i}')
   print(dominio_problema[i])

for i in range(num_rest):
   print(f'Restrição {i}')
   print(restricoes_problema[i])
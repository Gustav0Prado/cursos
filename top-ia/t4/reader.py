#!/usr/bin/python3
# Gustavo do Prado Silva - GRR20203942

import sys

class Problema:
   def __init__(self):
      self.dominio_problema    = []
      self.restricoes_problema = []
      self.num_var  = 0
      self.num_rest = 0

#------------------------------------------------------------------------------------------------

class Dominio:
   def __init__(self, tamanho, valores):
      self.tamanho = tamanho
      self.valores = valores
      self.valido  = [1]*tamanho

   def __str__(self):
      return "\tTamanho do domínio = " + str(self.tamanho) + "\n\tValores do domínio = " + str(self.valores)
   
#------------------------------------------------------------------------------------------------

class Restricao:
   def __init__(self, tipo, tamanho_escopo, escopo, tamanho_tuplas, tuplas):
      self.tipo = tipo
      self.tamanho_escopo = tamanho_escopo
      self.escopo = escopo
      self.tamanho_tuplas = tamanho_tuplas
      self.tuplas = tuplas

   def __str__(self):
      saida  = "\tTipo da restricao = " + str(self.tipo) + "\tTamanho do escopo = " + str(self.tamanho_escopo) + "\n\tEscopo = " + str(self.escopo)
      saida += "\n\tQuantidade de tuplas = " + str(self.tamanho_tuplas) + "\n\tTuplas = " + str(self.tuplas)
      return saida

#------------------------------------------------------------------------------------------------

# Particiona uma lista em várias listas menores de tamanho tam
def split(tam, lista):
   res = []
   while lista != []:
      l = []
      for i in range(tam):
         l.append(lista.pop(0))
      res.append(l)
   return res

#------------------------------------------------------------------------------------------------

def le_entrada():
   prob = Problema()

   # Le variaveis
   prob.num_var = int(sys.stdin.readline())
   for i in range(prob.num_var):
      linha = sys.stdin.readline()
      res = [eval(i) for i in linha.strip('\n').split(' ')] # Converte a linha dada na entrada para uma lista de inteiros
      
      dominio_xn = Dominio(res[0], res[1:])
      prob.dominio_problema.append(dominio_xn)

   # Le as restrições
   prob.num_rest = int(sys.stdin.readline())
   for i in range(prob.num_rest):
      linha_tipo   = sys.stdin.readline().strip('\n')
      linha_escopo = sys.stdin.readline()
      linha_tuplas = sys.stdin.readline()
      
      res_escopo = [eval(i) for i in linha_escopo.strip('\n').split(' ')] # Converte a linha dada na entrada para uma lista de inteiros
      res_tuplas = [eval(i) for i in linha_tuplas.strip('\n').split(' ')] # Converte a linha dada na entrada para uma lista de inteiros
      
      restricao_n = Restricao(linha_tipo, res_escopo[0], res_escopo[1:], res_tuplas[0], split(res_escopo[0], res_tuplas[1:]))
      prob.restricoes_problema.append(restricao_n)
      
   return prob

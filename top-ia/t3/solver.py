#!/usr/bin/python3
# Gustavo do Prado Silva - GRR20203942

from reader import *

# Retorna primeiro valor do dominio que ainda nao foi usado
def prox_valido(dom: Dominio):
   for i in range(dom.tamanho):
      if dom.valido[i] == 1:
         dom.valido[i] = 0   # Marca valor como usado
         return dom.valores[i]

# Acha o proximo valido, mas retorna apenas o primeiro que atende as restricoes
def prox_valor(prob: Problema, dom: Dominio, valores: list):
   a_i = prox_valido(dom)
   while (a_i != None) and (not verifica_restricoes(prob, valores+[a_i])):
      a_i = prox_valido(dom)
   return a_i

# Ao voltar o nivel da recursao, reseta quais valores sao validos nos proximos niveis
def reset_validos(dom: Dominio):
   dom.valido = [1]*dom.tamanho

def val_escopo(escopo:list, valores:list):
   l = []
   for i in escopo:
      l.append(valores[i-1])
   return l

def verifica_restricoes(prob: Problema, valores: list):
   # Verifica as tuplas da restricao, 
   for res in prob.restricoes_problema:
      if res.escopo[-1] > len(valores): return True
      if res.tipo == 'V':
         valida = False
         for tupla in res.tuplas:
            if tupla == val_escopo(res.escopo, valores): valida = True
         if not valida: return False
      else:
         for tupla in res.tuplas:
            if tupla == val_escopo(res.escopo, valores): return False
   return True

def backtrack(prob: Problema):   
   valores = []  # Cria uma valoracao inicial zerada
   i = 0

   while (i >= 0) and (i < prob.num_var):
      print(valores)
      a_i = prox_valor(prob, prob.dominio_problema[i], valores)
      if a_i != None:
         valores.append(a_i)
         i = i + 1
      else:
         reset_validos(prob.dominio_problema[i])
         valores.pop()
         i = i - 1
   
   return valores

def main():
   prob = le_entrada()
   val = backtrack(prob)
   
   print(f'Resultado = {val}')

if __name__ == "__main__":
   main()
#!/usr/bin/python3
# Gustavo do Prado Silva - GRR20203942

from reader import *

# Retorna primeiro valor do dominio que ainda nao foi usado
def prox_valor(dom: Dominio):
   for i in range(dom.tamanho):
      if dom.valido[i] == 1:
         dom.valido[i] = 0
         return dom.valores[i]

# Ao voltar o nivel da recursao, reseta quais valores sao validos nos proximos niveis
def reset_validos(dom: Dominio):
   dom.valido = [1]*dom.tamanho

# Verifica se alguma das restricoes nao esta sendo seguida
def verifica_restricoes(prob: Problema, valores: list):
   # TODO: pular verificacao na primeira vez
   for res in prob.restricoes_problema:
      for tupla in res.tuplas:
         for i in range(res.tamanho_tuplas):
            print(f'escopo: {res.escopo}')
            print(f'tupla: {tupla}')
            print(f'valores: {valores}')
            if valores[res.escopo[i]] != tupla[i]:
               return False

def backtrack(prob: Problema):   
   valores = [0]*prob.num_var  # Cria uma valoracao inicial zerada
   i = 0

   while (i >= 0) and (i < prob.num_var):
      if not verifica_restricoes(prob, valores):
         reset_validos(prob.dominio_problema[i])
         i = i - 1
      else:
         a_i = prox_valor(prob.dominio_problema[i])
         valores[i] = a_i
         i = i + 1
   
   return valores

def main():
   prob = le_entrada()
   val = backtrack(prob)
   
   print(val)

   # print(f'{prob.num_var} Variáveis')
   # print(f'{prob.num_rest} Restrições')

   # for i in range(prob.num_var):
   #    print(f'Variável {i}')
   #    print(prob.dominio_problema[i])

   # for i in range(prob.num_rest):
   #    print(f'Restrição {i}')
   #    print(prob.restricoes_problema[i])

if __name__ == "__main__":
   main()
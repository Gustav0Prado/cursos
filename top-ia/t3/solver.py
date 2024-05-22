#!/usr/bin/python3
# Gustavo do Prado Silva - GRR20203942

from reader import *

# Retorna primeiro valor do dominio que ainda nao foi usado
def prox_valido(dom: Dominio):
   for i in range(dom.tamanho):
      if dom.valido[i] == 1:
         dom.valido[i] = 0   # Marca valor como usado
         return dom.valores[i]
      
#------------------------------------------------------------------------------------------------

# Acha o proximo valido, mas retorna apenas o primeiro que atende as restricoes
def prox_valor(prob: Problema, dom: Dominio, valores: list):
   a_i = prox_valido(dom)
   while (a_i != None) and (not verifica_restricoes(prob, valores+[a_i])):
      a_i = prox_valido(dom)
   return a_i

#------------------------------------------------------------------------------------------------

# Ao voltar o nivel da recursao, reseta quais valores sao validos nos proximos niveis
def reset_validos(dom: Dominio):
   dom.valido = [1]*dom.tamanho

#------------------------------------------------------------------------------------------------

# Retorna uma lista l com os valores das variáveis dos indices indicados pelo escopo
def val_escopo(escopo:list, valores:list):
   l = []
   for i in escopo:
      l.append(valores[i-1])
   return l

#------------------------------------------------------------------------------------------------

# Verifica se valoracao fere alguma restricao dada
def verifica_restricoes(prob: Problema, valores: list):
   
   # Para cada restricao, verifica se possui todas as variáveis para aquele escopo
   # e se sim, verifica se estao validas comparando com as todas as tuplas dela
   for res in prob.restricoes_problema:
      if res.escopo[-1] > len(valores): return True
      
      if res.tipo == 'V':
         valida = False
         
         # Tenta verificar se existe pelo menos uma tupla que valide essa valoração dada
         for tupla in res.tuplas:
            if tupla == val_escopo(res.escopo, valores): valida = True
         
         if not valida: return False
      else:

         # Verifica se valoração é igual a qualquer uma das tuplas, o que é inválido
         for tupla in res.tuplas:
            if tupla == val_escopo(res.escopo, valores): return False
   return True

#------------------------------------------------------------------------------------------------

def backtrack(prob: Problema):   
   valores = []  # Cria uma valoracao inicial zerada
   i = 0

   while (i >= 0) and (i < prob.num_var):
      # print(valores)
      a_i = prox_valor(prob, prob.dominio_problema[i-1], valores)
      
      # Achou algum valor possivel como proximo
      if a_i != None:
         valores.append(a_i)
         i = i + 1

      # Caso contrário, reseta valores válidos do dominio,
      # retira ultimo valor (se existir algum) e retrocede
      else:
         reset_validos(prob.dominio_problema[i-1])
         if valores: valores.pop()
         i = i - 1
   
   if i > 0: return valores
   else: return None

#------------------------------------------------------------------------------------------------

def main():
   prob = le_entrada()
   val = backtrack(prob)
   
   if val != None: print(f'Resultado = {val}')
   else: print("Problema Inconsistente - Sem Solução")

if __name__ == "__main__":
   main()
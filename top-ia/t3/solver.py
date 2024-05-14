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
def prox_valor(prob: Problema, dom: Dominio, valores: list, i:int):
   a_i = prox_valido(dom)
   while not verifica_restricoes(prob, valores[:i] + [a_i] + valores[i+1:]):
      a_i = prox_valido(dom)
   return a_i

# Ao voltar o nivel da recursao, reseta quais valores sao validos nos proximos niveis
def reset_validos(dom: Dominio):
   dom.valido = [1]*dom.tamanho
      
# Verifica se alguma das restricoes nao esta sendo seguida
def verifica_restricoes(prob: Problema, valores: list):
   # Verifica as tuplas da restricao, 
   for res in prob.restricoes_problema:
      ind0 = res.escopo[0]-1
      ind1 = res.escopo[1]-1
      validas = 0

      # Caso as variaveis do escopo atual nao tenham sido escolhidas ainda, pula para a proxima restricao
      if (valores[ind0] == 0) or (valores[ind1] == 0): continue
      for tupla in res.tuplas:
         
         # print(f'valores: {[valores[ind0], valores[ind1]]} - tupla: {tupla} - achou: {validas}')

         # Restricao verifica se eh valido, tenta achar pelo menos uma restricao que valide os valores
         if res.tipo == 'V':
            if [valores[ind0], valores[ind1]] == tupla: validas += 1
         
         # Restricao verifica se eh invalido, se quebrar alguma retorna invalido, caso contrario continua
         else:
            if [valores[ind0], valores[ind1]] == tupla: return False
            else: validas += 1
      
      # Não respeitou nenhuma das restricoes
      if validas == 0: return False
   return True

# Verifica se existe algum valor no dominio que respeita as restricoes
def eh_consistente(prob: Problema, dom:Dominio, valores: list, i:int):
   for valor in dom.valores:
      if verifica_restricoes(prob, valores[:i] + [valor] + valores[i+1:]):
         return True
   return False

def backtrack(prob: Problema):   
   valores = [0]*prob.num_var  # Cria uma valoracao inicial zerada
   i = 0

   while (i >= 0) and (i < prob.num_var):
      # print(valores)
      if not eh_consistente(prob, prob.dominio_problema[i], valores, i):
         reset_validos(prob.dominio_problema[i])
         i = i - 1
      else:
         a_i = prox_valor(prob, prob.dominio_problema[i], valores, i)
         valores[i] = a_i
         i = i + 1
   
   return valores

def main():
   prob = le_entrada()
   val = backtrack(prob)
   
   print(f'Resultado = {val}')

if __name__ == "__main__":
   main()
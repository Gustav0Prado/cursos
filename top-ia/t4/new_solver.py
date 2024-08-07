#!/usr/bin/python3
# Gustavo do Prado Silva - GRR20203942

from reader import *
from copy import deepcopy

#------------------------------------------------------------------------------------------------
# Ao voltar o nivel da recursao, reseta quais valores sao validos nos proximos niveis
def reset_validos(dom: Dominio):
   dom.valores = dom.orig.copy()

#------------------------------------------------------------------------------------------------
# Retorna primeiro valor do dominio que ainda nao foi usado
def escolhe_prox(dom: Dominio):
   dom.invalidos.append(dom.valores[0])
   return dom.valores.pop(0)
   
#------------------------------------------------------------------------------------------------
# Retorna lista com a valoracao das variaveis de um determinado escopo
def extrai_vars(valores: list, escopo:list):
   return [valores[i-1] for i in escopo]

#------------------------------------------------------------------------------------------------
# Verifica se valoracao obedece as restricoes
def restricoes_validas(prob: Problema, dom: Dominio, valores: list):
   # Para cada restricao, verifica se possui todas as variáveis para aquele escopo
   # e se sim, verifica se estao validas comparando com as todas as tuplas dela
   for res in prob.restricoes_problema:
      if res.tipo == 'V':
         valida = False
         
         # Tenta verificar se existe pelo menos uma tupla que valide essa valoração dada
         for tupla in res.tuplas:
            if tupla == extrai_vars(valores, res.escopo): valida = True
         if not valida: return False
      else:
         for tupla in res.tuplas:
            if tupla == extrai_vars(valores, res.escopo): return False
   return True

#------------------------------------------------------------------------------------------------
# Retorna se não existem valores válidos no dominio
def nenhum_valido (dom: Dominio):
   return (len(dom.valores) == 0)

#------------------------------------------------------------------------------------------------
# Retorna se existe alguma combinacao de valores dos outros dominios que respeite a restricao
def existem_dominios_validos(a_j: int, x_j: int, r_c: Restricao, dominios: list, N: int):
   valoracao = [None]*N
   i = 0
   
   # Deixa apenas x_j como valido
   dominios[x_j].valores = [a_j]

   # Faz o backtracking procurando valoracoes validas das outras variaveis
   # que respeitem R_c
   while (i >= 0) and (i <= N):
      if (i == N):
         # Tenta verificar se existe pelo menos uma tupla que valide essa valoração dada
         for tupla in r_c.tuplas:
            if tupla == extrai_vars(valoracao, r_c.escopo): return True

         # Nao respeitou a restricao
         i = i - 1

      else:
         if nenhum_valido(dominios[i]) and (valoracao[i] != None):
            # Precisa pensar melhor nisso aq eu acho
            if i != x_j:
               for inv in dominios[i].invalidos:
                  dominios[i].valores.append(inv)
               dominios[i].invalidos = []
            else:
               # Deixa apenas x_j como valido
               dominios[x_j].valores = [a_j]
            valoracao[i] = None
            i = i - 1
         else:
            a_i = escolhe_prox(dominios[i])
            valoracao[i] = a_i
            i = i + 1
   return False

#------------------------------------------------------------------------------------------------
# Atualiza domínio j, tal que R_c é GAC em relação a x_j
def revisaGAC(prob:Problema, r_c: Restricao, dominios: list, x_j: int, valoracao: list):
   D_j = deepcopy(dominios)
   remover = []

   for a_j in dominios[x_j].valores:
      for i in range(len(valoracao)):
         if valoracao[i] != None:
            D_j[i].valores.append(valoracao[i])
            
      # se nao existe uma combinacao que satisfaz r_c, remove do dominio
      if not existem_dominios_validos(a_j, x_j, r_c, D_j, prob.num_var):
         remover.append(a_j)
      
   # elementos sao salvos pra remover depois senao o python se perde na lista
   for item in remover:
      dominios[x_j].valores.remove(item)

#------------------------------------------------------------------------------------------------
# Consistencia de arco generalizada
def GAC_3(prob: Problema, valoracao: list):
   pilha = []

   for r_c in prob.restricoes_problema:
      for x_i in range(prob.num_var):
         pilha.append((r_c, x_i))
   
   # Revisa todos os pares R_c e x_i
   while len(pilha) != 0:
      (r_c, x_i) = pilha.pop()
      D_i = prob.dominio_problema[x_i].valores.copy()
      revisaGAC(prob, r_c, prob.dominio_problema, x_i, valoracao)

      # Se houve alteração em D_i, propaga ela
      if D_i != prob.dominio_problema:
         for r_c in prob.restricoes_problema:
            for x_j in range(prob.num_var):
               if x_j != x_i: pilha.append((r_c, x_j))

#------------------------------------------------------------------------------------------------
def backtrack(prob: Problema):   
   valoracao = [None] * prob.num_var  # Cria uma valoracao inicial "zerada"
   i = 0

   while (i >= 0) and (i <= prob.num_var):
      if (i == prob.num_var):
         if restricoes_validas(prob, prob.dominio_problema[i-1], valoracao):
            return valoracao
         else:
            i = i - 1

      else:
         if nenhum_valido(prob.dominio_problema[i]) and (valoracao[i] != None):
            reset_validos(prob.dominio_problema[i])
            valoracao[i] = None
            i = i - 1
         else:
            GAC_3(prob, valoracao)
            a_i = escolhe_prox(prob.dominio_problema[i])
            valoracao[i] = a_i
            i = i + 1
   return None

#------------------------------------------------------------------------------------------------
def main():
   prob = le_entrada()
   val = backtrack(prob)
   
   if val != None: 
      for i in range(len(val)):
         print(f'x{i+1} = {val[i]}')
   else: print("INVIAVEL ")

if __name__ == "__main__":
   main()
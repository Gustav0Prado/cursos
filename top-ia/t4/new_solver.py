#!/usr/bin/python3
# Gustavo do Prado Silva - GRR20203942

from reader import *

#------------------------------------------------------------------------------------------------
# Ao voltar o nivel da recursao, reseta quais valores sao validos nos proximos niveis
def reset_validos(dom: Dominio):
   for i in range(dom.tamanho):
      if dom.valido[i] == 0: dom.valido[i] = 1

#------------------------------------------------------------------------------------------------
# Retorna primeiro valor do dominio que ainda nao foi usado
def escolhe_prox(dom: Dominio):
   for i in range(dom.tamanho):
      if dom.valido[i] == 1:
         dom.valido[i] = 0   # Marca valor como usado
         return dom.valores[i]
   
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
# Retorna se todos os valores do dominio sao invalidos
def nenhum_valido (dom: Dominio):
   return all(i == 0 for i in dom.valido)


#------------------------------------------------------------------------------------------------
# Atualiza domínio j, tal que R_c é GAC em relação a x_j
def revisaGAC(r_c: Restricao, dominios: list, x_j: int):
   for a_j in dominios[x_j]:
      # se nao existe uma combinacao que satisfaz r_c, remove do dominio

#------------------------------------------------------------------------------------------------
# Consistencia de arco generalizada
def GAC_3(prob: Problema):
   pilha = []

   for r_c in prob.restricoes_problema:
      for x_i in prob.num_var:
         pilha.append((r_c, x_i))
   
   # Revisa todos os pares R_c e x_i
   while len(pilha) != 0:
      (r_c, x_i) = pilha.pop()
      D_i = prob.dominio_problema[x_i]
      revisaGAC(r_c, prob.dominio_problema, x_i)

      # Se houve alteração em D_i, propaga ela
      if D_i != prob.dominio_problema[x_i]:
         for r_c in prob.restricoes_problema:
            for x_j in prob.num_var:
               if x_j != x_i: pilha.append((r_c, x_j))

#------------------------------------------------------------------------------------------------
def backtrack(prob: Problema):   
   valores = []  # Cria uma valoracao inicial zerada
   i = 0

   while (i >= 0) and (i <= prob.num_var):
      if (i == prob.num_var):
         if restricoes_validas(prob, prob.dominio_problema[i-1], valores):
            return valores
         else:
            if valores: valores.pop()
            i = i - 1

      else:
         if nenhum_valido(prob.dominio_problema[i]):
            reset_validos(prob.dominio_problema[i])
            if valores: valores.pop()
            i = i - 1
         else:
            a_i = escolhe_prox(prob.dominio_problema[i])
            valores.append(a_i)
            # print(f'i = {i} | valores = {valores} | dominio = {prob.dominio_problema[i].valido} | a_i = {a_i}')
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
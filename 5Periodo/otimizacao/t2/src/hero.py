class Flags:
   def __init__(self, o, f, a):
      self.o = o
      self.f = f
      self.a = a

def num_conflicts(left:list, right:list, conflicts:set) -> int:
   """Calcula o número total de conflitos nos dois grupos de heróis

   Args:
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"

   Returns:
       int: Número de conflitos
   """
   conf = 0

   for hero in left:
      for (l, r) in conflicts:
         if hero == l and r in left:
            conf += 1
   
   for hero in right:
      for (l, r) in conflicts:
         if hero == l and r in right:
            conf += 1

   return conf


def affinities_ok(teamA:list, teamB:list, affinities:set) -> bool:
   """Retorna se todas as afinidades de um herói estão na mesma equipe que ele

   Args:
       teamA (list): Primeira equipe
       teamB (list): Segunda  equipe

   Returns:
       bool: True caso estejam, False caso contrário
   """
   for hero in teamA:
      for (l, r) in affinities:
         if hero == l and r not in teamA:
            return False
         
   for hero in teamB:
      for (l, r) in affinities:
         if hero == l and r not in teamB:
            return False
   
   return True


def has_affinity(team:list, subject:int, affinities:set) -> bool:
   """Retorna se um alguem do grupo team tem afinidade com subject

   Args:
       subject (int): Herói que será comparado
       team (list): Time de heróis em que a afinidade será buscada

   Returns:
       bool: True caso alguém tenha afinidade e False caso contrário
   """

   if len(team) == 0:
      return False

   for h in team:
      for af in affinities:
         if (h in af and subject in af):
            return True
   
   return False


def compl(a:tuple, b:tuple) -> tuple:
   """Devolve o complemento da interseção de um conjunto 

   Args:
       a (tuple): conjunto a
       b (tuple): conjunto b

   Returns:
       tuple: Conjunto com {elementos de a que não estão em b} U {elementos de b que não estão em a}
   """
   d = list(b).copy()

   if a[0] in b:
      d.remove(a[0])
      d.append(a[1])
   
   else:
      d.remove(a[1])
      d.append(a[0])
   
   d.sort()
   return tuple(d)


def num_triangles(C:list, team:set):
   """Calcula número de triângulos de conflitos em uma lista de herois

   Args:
       team (list): Lista de conflitos a procurar triângulos
   """

   if(len(team) < 3):
      return 0

   p = sorted(list(team))
   for i in p:
      if i[0] in C or i[1] in C:
         p.remove(i)

   t = 0
   i = 0
   while i < len(p):
      found = 0
      for j in range(len(p)):
         # Se algum de membro de p[j] está em p[i], verifica se o complemento dos dois
         # também está na lista
         if p[i] != p[j] and any(x in p[j] for x in p[i]):
            c = compl(p[i], p[j])
            if c in p:
               t += 1

               pj = p[j]
               pi = p[i]

               p.remove(pi)
               p.remove(pj)
               p.remove(c)
               found = 1
               i = 0

         if found:
            break
      if not found:
         i += 1
   return t

def num_pentagon(C:list, team:set):
   """Calcula número de triângulos de conflitos em uma lista de herois

   Args:
       team (list): Lista de conflitos a procurar triângulos
   """

   # Se tiver menos que 5 conflitos é impossível criar pentágono
   if(len(team) < 5):
      return 0

   # Ordena pares do conjunto e remove pares onde algum membro já foi escolhido
   p = sorted(list(team))
   for i in p:
      if i[0] in C or i[1] in C:
         p.remove(i)

   q_pent = 0
   i = 0
   while i < len(p):
      found = 0
      for j in range(len(p)):
         # Se saem do mesmo lugar, procura um caminho entre i e j
         if p[i] != p[j] and p[i][0] == p[j][0]:
            way = 0
            visited = []
            nextI = p[i][1]
            for elem in p:
               # Compara elementos diferentes de i e j buscando um caminho para o próximo I
               if elem != p[i] and elem != p[j] and elem[0] == nextI:
                  nextI = elem[1]
                  visited.append(elem)
                  way += 1
            # Se possui três elementos ligando o caminho, é um pentágono (5 elementos)
            if way == 3 and (p[j][1] == visited[2][1]):
               pj = p[j]
               pi = p[i]

               for v in visited:
                  p.remove(v)
               
               p.remove(pi)
               p.remove(pj)
               q_pent += 1
               found = 1
               i = 0
         if found:
            break
      if not found:
         i += 1


   return q_pent
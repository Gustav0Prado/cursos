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
   for i in p:
      for j in p[p.index(i)+1:]:
         # Se algum de membro de p[j] está em p[i], verifica se o complemento dos dois
         # também está na lista
         if any(x in j for x in i):
            c = compl(i, j)
            if c in p:
               t += 1

               p.remove(i)
               p.remove(j)
               p.remove(c)

               break

   return t

def num_pentagon(C:list, team:set):
   """Calcula número de triângulos de conflitos em uma lista de herois

   Args:
       team (list): Lista de conflitos a procurar triângulos
   """

   if(len(team) < 5):
      return 0

   p = sorted(list(team))
   for i in p:
      if i[0] in C or i[1] in C:
         p.remove(i)

   q_pent = 0
   for i in p:
      for j in p:
         # Procura um caminho entre i e j
         if i != j and i[0] == j[0]:
            way = 0
            nextI = i[1]
            for elem in p:
               # Compara elementos diferentes de i e j buscando um caminho para o próximo I
               if elem != i and elem != j and elem[0] == nextI:
                  nextI = elem[1]
                  way += 1
            # Se possui três elementos ligando o caminho é um pentágono (5 elementos)
            if way == 3:
               q_pent += 1


   return q_pent
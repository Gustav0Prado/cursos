class Hero:
   def __init__(self, id):
      self.conflicts = []
      self.affinities = []
      self.id = id

   def __str__(self):
      return str(self.id)
   
   def __repr__(self):
      return str(self.id)


def num_conflicts(left:list, right:list) -> int:
   """Calcula o número total de conflitos nos dois grupos de heróis

   Args:
       left (list): Grupo do "lado esquerdo"
       right (list): Grupo do "lado direito"

   Returns:
       int: Número de conflitos
   """
   conf = 0

   for hero in left:
      for conflict in hero.conflicts:
         if conflict in left:
            conf += 1
   
   for hero in right:
      for conflict in hero.conflicts:
         if conflict in right:
            conf += 1

   return conf



def has_conflict(team:list, subject:Hero) -> bool:
   """Retorna se um alguem do grupo team tem conflito com subject

   Args:
       subject (Hero): Herói que será comparado
       team (list): Time de heróis em que a conflito será buscada

   Returns:
       bool: True caso alguém tenha conflito e False caso contrário
   """

   for h in team:
      for af in h.conflicts:
         if af.id == subject.id:
            return True
   
   return False


def has_affinity(team:list, subject:Hero) -> bool:
   """Retorna se um alguem do grupo team tem afinidade com subject

   Args:
       subject (Hero): Herói que será comparado
       team (list): Time de heróis em que a afinidade será buscada

   Returns:
       bool: True caso alguém tenha afinidade e False caso contrário
   """

   for h in team:
      for af in h.affinities:
         if af.id == subject.id:
            return True
   
   return False

def num_triangles(team:list):
   """Calcula número de triângulos de conflitos em uma lista de herois

   Args:
       team (list): Lista de herois a procurar triângulos
   """

   t = 0

   for hero in team:
      for i in range(len(hero.conflicts)-1):
         
         conf = hero.conflicts[i]
         
         # Para cada conflito de um heroi h, checa se ele tem conflito com algum outro
         # elemento da lista de conflitos de h
         for j in range(len(hero.conflicts)-i):
            nextconf = hero.conflicts[j]
            if nextconf in conf.conflicts:
               t += 1
   
   return t
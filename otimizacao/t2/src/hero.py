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


def affinities_ok(teamA:list, teamB:list) -> bool:
   """Retorna se todas as afinidades de um herói estão na mesma equipe que ele

   Args:
       teamA (list): Primeira equipe
       teamB (list): Segunda  equipe

   Returns:
       bool: True caso estejam, False caso contrário
   """
   for hero in teamA:
      for af in hero.affinities:
         if af not in teamA:
            return False
         
   for hero in teamB:
      for af in hero.affinities:
         if af not in teamB:
            return False
   
   return True


def has_affinity(team:list, subject:Hero) -> bool:
   """Retorna se um alguem do grupo team tem afinidade com subject

   Args:
       subject (Hero): Herói que será comparado
       team (list): Time de heróis em que a afinidade será buscada

   Returns:
       bool: True caso alguém tenha afinidade e False caso contrário
   """

   if len(team) == 0:
      return False

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
      # Para cada conflito c de um heroi h, checa se os conflitos de c estão em h (tirando o proprio c)
      # ou seja, checa se fecha um triângulo (A -> B,C e B -> C, onde -> indica conflito)
      for c in hero.conflicts:
         for k in c.conflicts:
            if k in hero.conflicts:
               t += 1
               break
   
   return t
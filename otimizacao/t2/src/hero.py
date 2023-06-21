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
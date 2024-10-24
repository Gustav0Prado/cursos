select nome
from disciplina
where sala = 'R128'
   UNION (
      select nomedisc
      from matricula
      group by nomedisc
      having count(numalu) > 5
   );
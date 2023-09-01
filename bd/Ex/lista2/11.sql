select a.nomealu
from aluno a
where a.numalu not in (select m.numalu from matricula m);
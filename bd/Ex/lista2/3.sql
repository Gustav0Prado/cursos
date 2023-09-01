select d.nome
from aluno a join matricula m on a.numAlu=m.numAlu join disciplina d on m.nomeDisc=d.nome join professor p on d.idprof=p.idprof
group by d.nome
having count(a.numalu) > 5 union (select d.nome from disciplina d where d.sala ilike 'r128');
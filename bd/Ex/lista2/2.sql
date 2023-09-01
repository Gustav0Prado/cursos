select max(a.idade) as idademax
from aluno a join matricula m on a.numAlu=m.numAlu join disciplina d on m.nomeDisc=d.nome join professor p on d.idprof=p.idprof
where a.curso ilike 'hist_ria' or p.nomeprof ilike 'ivana s%';
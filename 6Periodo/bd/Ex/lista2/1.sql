select a.nomealu
from aluno a join matricula m on a.numAlu=m.numAlu join disciplina d on m.nomeDisc=d.nome join professor p on d.idprof=p.idprof                                                                                                       rof=p.idprof
where a.ano=2 and nomeprof ilike 'ivana s%';
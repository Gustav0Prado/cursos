# Todas as relacoes da tabela
select *
from aluno a join matricula m on a.numAlu=m.numAlu join disciplina d on m.nomeDisc=d.nome join professor p on d.idprof=p.idprof;
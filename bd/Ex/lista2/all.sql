# Todas as relacoes da tabela
select *
from aluno a natural join matricula m join disciplina d on m.nomeDisc=d.nome natural join professor p;
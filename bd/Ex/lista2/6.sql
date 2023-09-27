select p.nomeprof          
from aluno a natural join matricula m join disciplina d on m.nomeDisc=d.nome natural join professor p
group by p.nomeprof
having count(a.nomealu) < 5;
select p.nomeprof          
from aluno a join matricula m on a.numAlu=m.numAlu join disciplina d on m.nomeDisc=d.nome join professor p on d.idprof=p.idprof
group by p.nomeprof
having count(a.nomealu) < 5;
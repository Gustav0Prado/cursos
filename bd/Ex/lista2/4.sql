select a.nomealu
from aluno a natural join matricula m join d disciplina on m.nomedisc=d.nome
group by a.nomealu, d.horario
having count(m.nomedisc) > 1;
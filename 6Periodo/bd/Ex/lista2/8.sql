select a.ano, avg(a.idade) 
from aluno a
group by a.ano
having a.ano <> 2
order by a.ano;
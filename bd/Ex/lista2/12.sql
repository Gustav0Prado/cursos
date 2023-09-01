# desonesto mas funciona
select a.idade, floor(avg(a.ano))
from aluno a
group by a.idade;

# jeito diferente
SELECT a1.idade, a1.ano
FROM aluno a1
GROUP BY idade, ano
HAVING COUNT(*) >= ALL (
   SELECT COUNT(*)
   FROM aluno a2
   WHERE a2.idade = a1.idade
   GROUP BY a2.ano
)
order by idade;
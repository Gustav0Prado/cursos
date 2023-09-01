SELECT p.nomeProf, count(d.nome) AS qtdedisc
FROM Professor p JOIN disciplina d ON p.idProf = d.idProf
WHERE p.idProf IN (
   SELECT idProf
   FROM disciplina
   WHERE sala = 'R128'
)
GROUP BY p.nomeprof
HAVING COUNT(DISTINCT d.sala) = 1;
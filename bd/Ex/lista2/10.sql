# Parece comparar cada elemento com a tabela inteira
SELECT a.nomealu
FROM aluno a NATURAL JOIN matricula m
GROUP BY a.nomealu
HAVING COUNT(m.nomedisc) >= ALL (
   SELECT COUNT(nomedisc)    
   FROM matricula
   GROUP BY numalu
);
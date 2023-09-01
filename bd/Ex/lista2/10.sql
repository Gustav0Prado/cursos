# Parece comparar cada elemento com a tabela inteira
SELECT a.nomealu
FROM aluno a JOIN matricula m ON a.numalu = m.numalu
GROUP BY a.nomealu
HAVING COUNT(m.nomedisc) >= ALL (
   SELECT COUNT(nomedisc)    
   FROM matricula
   GROUP BY numalu
);
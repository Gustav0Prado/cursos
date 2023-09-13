-- Questão 1
SELECT id, populacao, pais
FROM cidade;

-- Questão 2
SELECT *
FROM continente
WHERE area > 10000000;

-- Questão 3
SELECT c.id, p.nome
FROM cidade c, pais p
WHERE c.pais = p.codigo;

-- Questão 4
SELECT p.codigo, p.nome
FROM cidade c JOIN pais p ON c.pais=p.codigo;

-- Questão 5
SELECT cidade
FROM cidademar UNION (
    SELECT cidade
    FROM cidaderio
);

-- Questão 6
SELECT DISTINCT cidade
FROM cidaderio cm1
WHERE NOT EXISTS ((
    SELECT rio
    FROM rio) EXCEPT (
        SELECT cidade FROM cidaderio cm2
        WHERE cm1.rio=cm2.rio));

-- Questão 7
SELECT p.nome
FROM pais p, paislingua pl
WHERE p.codigo=pl.pais AND
    lingua IN ('Portuguese', 'English')

-- Questão 8
SELECT c.id
FROM cidade c
EXCEPT (SELECT cidade FROM cidaderio);

-- Questão 9
SELECT pais, COUNT(religiao) AS qtdreligioes
FROM paisreligiao
GROUP BY pais;

-- Questão 10
SELECT pais, COUNT(lingua) AS qtdlinguas
FROM paislingua
GROUP BY pais
HAVING count(lingua) > 1;
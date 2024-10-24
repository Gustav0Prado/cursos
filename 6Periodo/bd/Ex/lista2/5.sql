# Usando agregação (me parece gambiarra lol)
select p.nomeprof
from disciplina d join professor p on d.idprof=p.idprof
group by p.nomeprof
having count(d.sala) in (select count(distinct sala) from disciplina);

# Usando divisão
select distinct nomeprof
from professor p1
where not exists ((select sala from disciplina)
   except (
      select d.sala
      from disciplina d join professor p2 on d.idprof = p2.idprof
      where p1.idprof=p2.idprof)
   );
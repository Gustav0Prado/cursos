select p1.nomepess
from pessoa p1, pessoa p2                                                                             
where p1.nomepess <> p2.nomepess and p1.cidade=p2.cidade;
select distinct p.nomepess 
from pessoa p, compra c
where p.nomepess=c.comprador OR p.nomepess=c.vendedor;
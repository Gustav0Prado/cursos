select p.*
from pessoa p, produto pr, compra c
where p.nomepess=c.comprador and pr.pnome=c.produto and pr.categoria ilike 'eletr_nico%';
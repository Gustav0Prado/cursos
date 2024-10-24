select distinct p.*
from pessoa p, compra c, produto as pr, companhia as f
where p.nomepess=c.comprador AND c.produto=pr.pnome AND c.vendedor ilike 'pedro' OR p.nomepess=c.comprador AND c.produto=pr.pnome AND pr.fabricante=f.cnome AND f.valorAcao > 50.00;
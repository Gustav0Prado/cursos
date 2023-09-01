select distinct p.*
from pessoa p, produto pr, compra c, companhia f
where p.nomepess=c.comprador and pr.pnome=c.produto and pr.fabricante =f.cnome and f.pais ilike 'jap_o' except (
   select p.* from pessoa p, produto pr, compra c, companhia f where p.nomepess=c.comprador and pr.pnome=c.produto and pr.fabricante=f.cnome and f.pais ilike 'brasil'
);
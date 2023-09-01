select c.comprador, avg(p.preco) as media
from compra c, produto p
where p.pnome=c.produto group by c.comprador;
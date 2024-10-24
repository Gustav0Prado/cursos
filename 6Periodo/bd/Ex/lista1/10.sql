select c.vendedor,Sum(p.preco) as totalVendas
from compra c, produto p
where p.pnome=c.produto group by c.vendedor;
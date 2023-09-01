select p.categoria, avg(p.preco) as media, min(p.preco) as menor, max(p.preco) as maior
from produto p
group by p.categoria;
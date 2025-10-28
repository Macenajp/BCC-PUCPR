##Realizar as seguintes consultas:
##Listar todos os clientes em ordem alfabética.
SELECT * FROM clientes ORDER BY nome;

##Mostrar todos os pedidos com status PENDING.
SELECT * FROM pedidos WHERE status='PENDING';

##Exibir os 5 pedidos de maior valor.
SELECT * FROM pedidos ORDER BY total_valor DESC LIMIT 5;

##Listar apenas os produtos distintos já vendidos.
SELECT DISTINCT produto_nome FROM compras, pedidos WHERE status='paid';

##Mostrar os pedidos pagos na última semana.
SELECT * FROM pedidos WHERE status = 'PAID' AND data_pedido >= '2025-09-08' AND data_pedido <= '2025-09-14';

##Selecionar os nomes e e-mails dos clientes cujo e-mail começa com a letra “a”.
SELECT nome, email FROM clientes WHERE nome LIKE 'a%';

##Exibir todos os itens de compras com quantidade maior que 1.
SELECT * FROM compras WHERE quantidade < 1;

##Contar quantos pedidos cada cliente já realizou.
SELECT cliente_id, COUNT(*) total_pedidos FROM pedidos GROUP BY  cliente_id;

##Calcular o valor total gasto por cada cliente em pedidos pagos.
SELECT nome,(SELECT SUM(total_valor) FROM pedidos WHERE pedidos.cliente_id = clientes.cliente_id AND pedidos.status='PAID') total_gasto FROM clientes;

##Descobrir qual produto foi mais vendido em quantidade.
SELECT produto_nome, SUM(quantidade) total_vendido FROM compras GROUP BY produto_nome ORDER BY total_vendido DESC;

##Mostrar os pedidos junto com o nome do cliente que os realizou.
SELECT pedido_id, data_pedido, status, total_itens, total_valor, (SELECT nome FROM clientes WHERE clientes.cliente_id=pedidos.cliente_id) nome_cliente FROM pedidos;

##Comparar o valor total do pedido com a soma dos subtotais dos itens.
SELECT p.pedido_id, p.total_valor, SUM(c.subtotal) AS soma_itens, p.total_valor - SUM(c.subtotal) AS diferenca FROM pedidos p JOIN compras c ON p.pedido_id = c.pedido_id GROUP BY p.pedido_id, p.total_valor;

##Calcular o ticket médio (valor médio dos pedidos) por cliente.
SELECT nome,(SELECT AVG(total_valor) FROM pedidos WHERE pedidos.cliente_id=clientes.cliente_id) ticket_medio FROM clientes;

##Descobrir o produto com o maior valor unitário registrado.
SELECT produto_nome, valor_unitario FROM compras WHERE valor_unitario=(SELECT MAX(valor_unitario) FROM compras);

##Listar quantos pedidos foram feitos por ano.
SELECT YEAR(data_pedido), COUNT(*) FROM pedidos GROUP BY YEAR(data_pedido);

##Mostrar os clientes que nunca realizaram pedidos.
SELECT nome FROM clientes WHERE cliente_id NOT IN (SELECT cliente_id FROM pedidos);

##Listar os produtos mais comprados nos últimos 10 dias.
SELECT produto_nome, SUM(quantidade) FROM compras WHERE pedido_id IN (SELECT pedido_id FROM pedidos WHERE data_pedido >= NOW() - INTERVAL 10 DAY) GROUP BY produto_nome ORDER BY SUM(quantidade) DESC;

##Identificar o cliente que mais gastou no total.
SELECT nome, (SELECT SUM(total_valor) FROM pedidos WHERE pedidos.cliente_id=clientes.cliente_id) total_gasto FROM clientes ORDER BY total_gasto DESC LIMIT 1;

##Mostrar o valor médio, mínimo e máximo dos pedidos pagos.
SELECT AVG(total_valor), MIN(total_valor), MAX(total_valor) FROM pedidos WHERE status='PAID';

##Exibir o ranking de clientes por quantidade de pedidos realizados.
SELECT nome, (SELECT COUNT(*) FROM pedidos WHERE pedidos.cliente_id=clientes.cliente_id) total_pedidos FROM clientes ORDER BY total_pedidos DESC;

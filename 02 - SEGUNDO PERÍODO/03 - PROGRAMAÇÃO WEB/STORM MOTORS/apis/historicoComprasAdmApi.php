<?php
    session_start();
    header('Content-Type: application/json; charset=UTF-8');

    try {
        $usuario_tipo = $_SESSION['usuario_tipo'] ?? null;
        if ($usuario_tipo !== 'admin') {
            throw new Exception("Acesso negado: apenas administradores podem acessar o histórico de compras.");
        }

        $pdo = new PDO("mysql:host=localhost:3306;dbname=stormmotors;charset=utf8", "root", "PUC@1234");
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $stmt = $pdo->prepare("
            SELECT 
                p.id AS pedido_id,
                p.id_usuario,
                c.nome AS nome_cliente,
                p.nome_carro,
                p.cor,
                p.preco,
                p.imagem,
                p.data_pedido
            FROM pedidos p
            LEFT JOIN clientes c ON c.id = p.id_usuario
            ORDER BY p.data_pedido DESC
        ");
        $stmt->execute();
        $pedidos = $stmt->fetchAll(PDO::FETCH_ASSOC);
        echo json_encode([
            "sucesso" => true,
            "pedidos" => $pedidos
        ]);

    } catch (Exception $e) {
        echo json_encode([
            "sucesso" => false,
            "mensagem" => $e->getMessage()
        ]);
    }
?>

<?php
session_start();
header('Content-Type: application/json; charset=UTF-8');

try {
    $id_usuario = $_SESSION["usuario_id"] ?? null;
    if (!$id_usuario) {
        throw new Exception("Usuário não logado");
    }

    $pdo = new PDO("mysql:host=localhost:3306;dbname=stormmotors;charset=utf8", "root", "PUC@1234");
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $stmt = $pdo->prepare("
        SELECT 
            p.id AS pedido_id,
            p.nome_carro,
            p.cor,
            p.preco,
            p.data_pedido,
            p.imagem,
            sp.status,
            sp.data_status
        FROM pedidos p
        LEFT JOIN status_pedidos sp ON sp.id_pedido = p.id
        WHERE p.id_usuario = ?
        ORDER BY p.data_pedido DESC, sp.data_status ASC
    ");
    $stmt->execute([$id_usuario]);
    $pedidosComStatus = $stmt->fetchAll(PDO::FETCH_ASSOC);

    $pedidos = [];
    foreach ($pedidosComStatus as $row) {
        $pedido_id = $row['pedido_id'];

        if (!isset($pedidos[$pedido_id])) {
            $pedidos[$pedido_id] = [
                'id' => $pedido_id,
                'nome_carro' => $row['nome_carro'],
                'cor' => $row['cor'],
                'preco' => $row['preco'],
                'data_pedido' => $row['data_pedido'],
                'imagem' => $row['imagem'],
                'status' => []
            ];
        }

        if ($row['status']) {
            $pedidos[$pedido_id]['status'][] = [
                'status' => $row['status'],
                'data_status' => $row['data_status']
            ];
        }
    }
    echo json_encode([
        "usuario" => [
            "id" => $id_usuario,
            "nome" => $_SESSION["usuario_nome"] ?? "Usuário"
        ],
        "pedidos" => array_values($pedidos) 
    ]);

} catch (Exception $e) {
    echo json_encode([
        "sucesso" => false,
        "mensagem" => $e->getMessage()
    ]);
}
?>

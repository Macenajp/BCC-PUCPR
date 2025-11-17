<?php
// Inicia a sessão (para saber quem está logado)
session_start();
header('Content-Type: application/json; charset=UTF-8');

try {
    // 1. Pega o ID do usuário da SESSÃO (que foi salvo no login)
    $id_usuario = $_SESSION["usuario_id"] ?? null;
    if (!$id_usuario) {
        throw new Exception("Usuário não logado");
    }

    // 2. Conexão via PDO
    $pdo = new PDO("mysql:host=localhost:3306;dbname=stormmotors;charset=utf8", "root", "PUC@1234");
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // 3. Consulta SQL com JOIN (junção)
    $stmt = $pdo->prepare("
        SELECT 
            p.id AS pedido_id, p.nome_carro, p.cor, p.preco, p.data_pedido, p.imagem,
            sp.status, sp.data_status
        FROM pedidos p
        -- Junta (LEFT JOIN) os status (sp) onde o id_pedido for igual
        LEFT JOIN status_pedidos sp ON sp.id_pedido = p.id
        -- A CONDIÇÃO DE FILTRO: ONDE (WHERE) o id_usuario do pedido
        -- é igual ao ID do usuário que está logado
        WHERE p.id_usuario = ? 
        -- Ordena os resultados
        ORDER BY p.data_pedido DESC, sp.data_status ASC
    ");
    // 4. Executa a consulta, passando o ID do usuário logado como parâmetro seguro
    $stmt->execute([$id_usuario]);
    $pedidosComStatus = $stmt->fetchAll(PDO::FETCH_ASSOC);

    // 5. Processamento (Agrupamento)
    // A consulta acima retorna dados "planos", ex:
    // Pedido 1 | Status A
    // Pedido 1 | Status B
    // Este código PHP agrupa os status *dentro* de seus pedidos
    
    $pedidos = []; // Array final
    foreach ($pedidosComStatus as $row) {
        $pedido_id = $row['pedido_id'];

        // Se é a primeira vez que vemos este ID de pedido...
        if (!isset($pedidos[$pedido_id])) {
            // Cria a "ficha" principal do pedido
            $pedidos[$pedido_id] = [
                'id' => $pedido_id,
                'nome_carro' => $row['nome_carro'],
                'cor' => $row['cor'],
                'preco' => $row['preco'],
                'data_pedido' => $row['data_pedido'],
                'imagem' => $row['imagem'],
                'status' => [] // Cria uma lista vazia para os status
            ];
        }

        // Se esta linha da consulta tiver um status (não for nulo)...
        if ($row['status']) {
            // Adiciona o status (com sua data) à lista de status deste pedido
            $pedidos[$pedido_id]['status'][] = [
                'status' => $row['status'],
                'data_status' => $row['data_status']
            ];
        }
    }
    
    // 6. Envia o JSON final (formatado e agrupado) para o JavaScript
    // `array_values` transforma o array associativo (com chaves de ID) em um array simples [ ... ]
    echo json_encode([
        "usuario" => [ // (Informativo)
            "id" => $id_usuario,
            "nome" => $_SESSION["usuario_nome"] ?? "Usuário"
        ],
        "pedidos" => array_values($pedidos) 
    ]);

} catch (Exception $e) {
    // Captura erros (ex: "Usuário não logado")
    echo json_encode([
        "sucesso" => false,
        "mensagem" => $e->getMessage()
    ]);
}
?>

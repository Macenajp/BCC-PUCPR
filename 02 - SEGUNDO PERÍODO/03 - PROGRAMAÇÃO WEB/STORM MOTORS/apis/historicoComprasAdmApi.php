<?php
    // Inicia a sessão (para verificar o tipo de usuário)
    session_start();
    header('Content-Type: application/json; charset=UTF-8');

    try {
        // --- Bloco de Segurança (Server-side) ---
        // 1. Pega o tipo de usuário da SESSÃO
        $usuario_tipo = $_SESSION['usuario_tipo'] ?? null;
        
        // 2. Segunda verificação de segurança.
        // Mesmo se um usuário comum tentasse chamar esta URL de API diretamente,
        // esta verificação (no lado do servidor) falharia.
        if ($usuario_tipo !== 'admin') {
            // Joga uma Exceção (erro) que será capturada pelo 'catch'
            throw new Exception("Acesso negado: apenas administradores podem acessar o histórico de compras.");
        }

        // 3. Conexão PDO
        $pdo = new PDO("mysql:host=localhost:3306;dbname=stormmotors;charset=utf8", "root", "PUC@1234");
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        // 4. Consulta SQL de Admin
        $stmt = $pdo->prepare("
            SELECT 
                p.id AS pedido_id,
                p.id_usuario,
                c.nome AS nome_cliente, -- Pega o NOME da tabela 'clientes' (alias 'c')
                p.nome_carro,
                p.cor,
                p.preco,
                p.imagem,
                p.data_pedido
            FROM pedidos p
            -- Junta (LEFT JOIN) com a tabela 'clientes' (c)
            -- para podermos pegar o nome de quem fez o pedido
            LEFT JOIN clientes c ON c.id = p.id_usuario
            ORDER BY p.data_pedido DESC
        ");
        
        // 5. Note a diferença: NÃO HÁ "WHERE p.id_usuario = ?"
        // Esta consulta pega TODOS os pedidos.
        
        $stmt->execute();
        $pedidos = $stmt->fetchAll(PDO::FETCH_ASSOC); // Pega todos os resultados
        
        // 6. Envia a lista COMPLETA de pedidos para o JS do admin
        echo json_encode([
            "sucesso" => true,
            "pedidos" => $pedidos
        ]);

    } catch (Exception $e) {
        // Captura a Exceção (ex: "Acesso negado")
        echo json_encode([
            "sucesso" => false,
            "mensagem" => $e->getMessage()
        ]);
    }
?>

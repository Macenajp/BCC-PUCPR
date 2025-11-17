<?php
    // Inicia a sessão (para pegar o ID do usuário logado)
    session_start();
    
    // Define a resposta como JSON
    header("Content-Type: application/json; charset=UTF-8");

    try {
        // --- Conexão via PDO ---
        // (PDO é outra forma de conectar ao MySQL, muito boa para "Transações")
        $pdo = new PDO("mysql:host=localhost:3306;dbname=stormmotors;charset=utf8", "root", "PUC@1234");
        // Configura o PDO para relatar erros como exceções
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        // Pega o objeto JSON que o `comprar.php` (JS) enviou
        $dados = json_decode(file_get_contents("php://input"), true);

        if (!$dados) {
            throw new Exception("Nenhum dado recebido");
        }

        // Pega o ID do usuário (salvo na sessão durante o login)
        $id_usuario = $_SESSION["usuario_id"] ?? null;
        if (!$id_usuario) {
            throw new Exception("Usuário não logado"); // Segurança: não permite pedido sem dono
        }

        // Pega os dados do pedido
        $nome_carro = $dados["modelo"] ?? "";
        $cor = $dados["cor"] ?? "";
        $preco = $dados["valor"] ?? ""; 
        $imagem = $dados["imagem"] ?? "";

        // --- Bloco de Transação (CRUCIAL!) ---
        // Inicia a transação. Isso garante que todos os comandos SQL abaixo
        // ou funcionam JUNTOS, ou falham JUNTOS. (Atomicidade)
        $pdo->beginTransaction();

        // 1. Insere o pedido principal na tabela 'pedidos'
        $stmt = $pdo->prepare("INSERT INTO pedidos (id_usuario, nome_carro, cor, preco, imagem) VALUES (?, ?, ?, ?, ?)");
        $stmt->execute([
            $id_usuario,
            $nome_carro,
            $cor,
            $preco,
            $imagem
        ]);

        // 2. Pega o ID do pedido que acabou de ser criado
        $id_pedido = $pdo->lastInsertId();

        // 3. Insere o status inicial ('Em Processamento') na tabela 'status_pedidos'
        $stmtStatus = $pdo->prepare("INSERT INTO status_pedidos (id_pedido, status) VALUES (?, ?)");
        $stmtStatus->execute([
            $id_pedido,
            "Em Processamento"
        ]);

        // 4. Insere o registro de pagamento na tabela 'pagamentos'
        $stmtPagamento = $pdo->prepare("INSERT INTO pagamentos (id_pedido, valor_pago) VALUES (?, ?)");
        $stmtPagamento->execute([
            $id_pedido,
            $preco 
        ]);

        // 5. Insere o registro de montagem na tabela 'montadora'
        $stmtMontadora = $pdo->prepare("INSERT INTO montadora (id_pedido) VALUES (?)");
        $stmtMontadora->execute([
            $id_pedido,
        ]);

        // Se todos os 5 comandos acima deram certo, CONFIRMA (commit) a transação
        // As mudanças agora são permanentes no banco.
        $pdo->commit();

        // Envia a resposta de sucesso final para o `comprar.php` (JS)
        echo json_encode([
            "sucesso" => true,
            "mensagem" => "Pedido, pagamento e montagem registrados com sucesso"
        ]);

    } catch (Exception $e) {
        // Se QUALQUER um dos 5 comandos falhar, o 'catch' é ativado
        if ($pdo->inTransaction()) {
            // DESFAZ (rollBack) todas as mudanças feitas dentro desta transação
            // Impede que um pedido seja criado sem um pagamento, por exemplo.
            $pdo->rollBack();
        }
        // Envia a mensagem de erro para o JavaScript
        echo json_encode([
            "sucesso" => false,
            "mensagem" => $e->getMessage()
        ]);
    }
?>

<?php
    session_start();
    header("Content-Type: application/json; charset=UTF-8");

    try {
        $pdo = new PDO("mysql:host=localhost:3306;dbname=stormmotors;charset=utf8", "root", "PUC@1234");
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $dados = json_decode(file_get_contents("php://input"), true);

        if (!$dados) {
            throw new Exception("Nenhum dado recebido");
        }

        $id_usuario = $_SESSION["usuario_id"] ?? null;
        if (!$id_usuario) {
            throw new Exception("Usuário não logado");
        }

        $nome_carro = $dados["modelo"] ?? "";
        $cor = $dados["cor"] ?? "";
        $preco = $dados["valor"] ?? ""; 
        $imagem = $dados["imagem"] ?? "";

        $pdo->beginTransaction();

        $stmt = $pdo->prepare("INSERT INTO pedidos (id_usuario, nome_carro, cor, preco, imagem) VALUES (?, ?, ?, ?, ?)");
        $stmt->execute([
            $id_usuario,
            $nome_carro,
            $cor,
            $preco,
            $imagem
        ]);

        $id_pedido = $pdo->lastInsertId();

        $stmtStatus = $pdo->prepare("INSERT INTO status_pedidos (id_pedido, status) VALUES (?, ?)");
        $stmtStatus->execute([
            $id_pedido,
            "Em Processamento"
        ]);

        $stmtPagamento = $pdo->prepare("INSERT INTO pagamentos (id_pedido, valor_pago) VALUES (?, ?)");
        $stmtPagamento->execute([
            $id_pedido,
            $preco 
        ]);

        $stmtMontadora = $pdo->prepare("INSERT INTO montadora (id_pedido) VALUES (?)");
        $stmtMontadora->execute([
            $id_pedido,
        ]);

        $pdo->commit();

        echo json_encode([
            "sucesso" => true,
            "mensagem" => "Pedido, pagamento e montagem registrados com sucesso"
        ]);

    } catch (Exception $e) {
        if ($pdo->inTransaction()) {
            $pdo->rollBack();
        }
        echo json_encode([
            "sucesso" => false,
            "mensagem" => $e->getMessage()
        ]);
    }
?>

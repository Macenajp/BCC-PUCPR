<?php
    session_start();
    header("Content-Type: application/json; charset=UTF-8");
    include "../bancoDeDados/conexaoBD.php";

    $dados = json_decode(file_get_contents("php://input"), true);

    $id_usuario = $_SESSION['usuario_id'] ?? null;
    if (!$id_usuario) {
        echo json_encode(['sucesso' => false, 'mensagem' => 'Usuário não logado']);
        exit;
    }

    $nome_carro = $dados['nome_carro'] ?? '';
    $valor = $dados['valor'] ?? '';

    if (!$nome_carro || !$valor) {
        echo json_encode(['sucesso' => false, 'mensagem' => 'Dados incompletos']);
        exit;
    }

    $sql = "INSERT INTO pre_vendas (id_usuario, nome_carro, valor) VALUES (?, ?, ?)";
    $stmt = $conexao->prepare($sql);

    if ($stmt->execute([$id_usuario, $nome_carro, $valor])) {
        echo json_encode(['sucesso' => true]);
    } else {
        echo json_encode(['sucesso' => false, 'mensagem' => 'Erro ao registrar pré-venda']);
    }
?>

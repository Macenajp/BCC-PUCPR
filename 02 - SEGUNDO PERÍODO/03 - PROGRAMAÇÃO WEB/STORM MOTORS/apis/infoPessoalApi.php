<?php
    session_start();
    include "../bancoDeDados/conexaoBD.php";
    header("Content-Type: application/json");

    if (!isset($_SESSION['usuario_id'])) {
        echo json_encode(["status" => "erro", "mensagem" => "Usuário não logado"]);
        exit;
    }

    $idUsuario = $_SESSION['usuario_id'];

    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        $sql = $conexao->prepare("SELECT nome, endereco, email, cpf, telefone FROM clientes WHERE id = ?");
        $sql->bind_param("i", $idUsuario);
        $sql->execute();
        $resultado = $sql->get_result();
        $usuario = $resultado->fetch_assoc();

        echo json_encode(["status" => "sucesso", "usuario" => $usuario]);
        exit;
    }

    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $dados = json_decode(file_get_contents("php://input"), true);

        if (!$dados) {
            echo json_encode(["status" => "erro", "mensagem" => "JSON inválido"]);
            exit;
        }

        $nome = $dados['nome'] ?? '';
        $endereco = $dados['endereco'] ?? '';
        $email = $dados['email'] ?? '';
        $cpf = $dados['cpf'] ?? '';
        $telefone = $dados['telefone'] ?? '';

        $sql = $conexao->prepare("UPDATE clientes SET nome=?, endereco=?, email=?, cpf=?, telefone=? WHERE id=?");
        $sql->bind_param("sssssi", $nome, $endereco, $email, $cpf, $telefone, $idUsuario);

        if ($sql->execute()) {
            echo json_encode(["status" => "sucesso", "mensagem" => "Dados atualizados com sucesso!"]);
        } else {
            echo json_encode(["status" => "erro", "mensagem" => "Erro ao atualizar os dados."]);
        }
        exit;
    }

    echo json_encode(["status" => "erro", "mensagem" => "Método inválido"]);
?>

<?php
    include "../bancoDeDados/conexaoBD.php"; 
    header("Content-Type: application/json"); 

    $json = file_get_contents("php://input");
    $dados = json_decode($json, true);

    if (empty($dados['nome']) || empty($dados['endereco']) || empty($dados['email']) || empty($dados['senha']) || empty($dados['telefone'])) {
        http_response_code(400);
        echo json_encode([
            "status" => "erro",
            "mensagem" => "Campos obrigatórios não preenchidos"
        ]);
        exit;
    }

    $senhaHash = password_hash($dados['senha'], PASSWORD_DEFAULT);

    $insert = $conexao->prepare("INSERT INTO clientes (nome, endereco, email, cpf, senha, telefone) VALUES (?, ?, ?, ?, ?, ?)");
    $insert->bind_param("ssssss",$dados['nome'],$dados['endereco'],$dados['email'],$dados['cpf'],$senhaHash,$dados['telefone']);

    if (!$insert) {
        http_response_code(500);
        echo json_encode([
            "status" => "erro",
            "mensagem" => "Erro ao preparar a query",
            "erro" => $conexao->error
        ]);
        exit;
    }

    $salvarNoBanco = $insert->execute();

    if ($salvarNoBanco) {
        echo json_encode([
            "status" => "sucesso",
            "mensagem" => "Usuário cadastrado com sucesso",
            "usuario" => [
                "nome" => $dados['nome'],
                "endereco" => $dados['endereco'],
                "email" => $dados['email'],
                "cpf" => $dados['cpf'],
                "telefone" => $dados['telefone']
            ]
        ]);
    } else {
        http_response_code(500);
        echo json_encode([
            "status" => "erro",
            "mensagem" => "Erro ao cadastrar usuário",
            "erro" => $insert->error
        ]);
    }
?>

<?php
    session_start();
    include "../bancoDeDados/conexaoBD.php"; 
    header("Content-Type: application/json");

    $dados = json_decode(file_get_contents("php://input"), true);
    $email = trim($dados['email'] ?? '');
    $senha = trim($dados['senha'] ?? '');

    if (!$email || !$senha) {
        echo json_encode(["status"=>"erro", "mensagem"=>"Email ou senha não preenchidos"]);
        exit;
    }

    function loginUsuario($conexao, $tabela, $tipo) {
        global $email, $senha;

        $query = $conexao->prepare("SELECT id, nome, senha FROM $tabela WHERE email=?");
        $query->bind_param("s", $email);
        $query->execute();
        $resultado = $query->get_result();

        if ($resultado->num_rows > 0) {
            $usuario = $resultado->fetch_assoc();
            if (password_verify($senha, $usuario['senha'])) {
                $_SESSION['usuario_id'] = $usuario['id'];
                $_SESSION['usuario_nome'] = $usuario['nome'];
                $_SESSION['usuario_tipo'] = $tipo;

                echo json_encode([
                    "status"=>"sucesso",
                    "mensagem"=>"Login efetuado com sucesso",
                    "usuario"=>["nome"=>$usuario['nome'], "email"=>$email, "tipo"=>$tipo]
                ]);
                exit;
            } else {
                echo json_encode(["status"=>"erro", "mensagem"=>"Senha incorreta"]);
                exit;
            }
        }
        return false;
    }

    loginUsuario($conexao, "administradores", "admin");

    loginUsuario($conexao, "clientes", "usuario");

    echo json_encode(["status"=>"erro","mensagem"=>"Usuário não encontrado"]);
    exit;
?>
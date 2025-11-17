<?php
    // --- Bloco de Sessão (CRUCIAL!) ---
    // `session_start()` DEVE ser a primeira coisa no script.
    // Ele inicia uma nova sessão ou retoma uma sessão existente (baseado no cookie do navegador).
    session_start();
    
    // Inclui a conexão com o banco
    include "../bancoDeDados/conexaoBD.php"; 
    
    // Define a resposta como JSON
    header("Content-Type: application/json");

    // Pega os dados (email, senha) que o JavaScript enviou
    $dados = json_decode(file_get_contents("php://input"), true);
    $email = trim($dados['email'] ?? '');
    $senha = trim($dados['senha'] ?? '');

    // Validação
    if (!$email || !$senha) {
        echo json_encode(["status"=>"erro", "mensagem"=>"Email ou senha não preenchidos"]);
        exit; // Para o script
    }

    // Função interna reutilizável para checar o login em diferentes tabelas
    function loginUsuario($conexao, $tabela, $tipo) {
        // `global` puxa as variáveis $email e $senha para dentro do escopo da função
        global $email, $senha;

        // Prepara a busca (Prepared Statement) para segurança
        $query = $conexao->prepare("SELECT id, nome, senha FROM $tabela WHERE email=?");
        $query->bind_param("s", $email); // Vincula o email ao "?"
        $query->execute();
        $resultado = $query->get_result();

        // Se encontrou um usuário com esse email (num_rows > 0)
        if ($resultado->num_rows > 0) {
            $usuario = $resultado->fetch_assoc(); // Pega os dados (id, nome, senha HASH)
            
            // --- Bloco de Segurança (CRUCIAL!) ---
            // `password_verify` compara a senha que o usuário digitou ($senha)
            // com o HASH seguro que está salvo no banco ($usuario['senha']).
            if (password_verify($senha, $usuario['senha'])) {
                
                // --- O LOGIN ACONTECE AQUI ---
                // Se as senhas batem, armazenamos os dados do usuário na SESSÃO PHP.
                // Esses dados ficarão disponíveis em todo o site (em arquivos com session_start()).
                $_SESSION['usuario_id'] = $usuario['id'];
                $_SESSION['usuario_nome'] = $usuario['nome'];
                $_SESSION['usuario_tipo'] = $tipo; // 'admin' ou 'usuario'

                // Envia a resposta de sucesso para o JavaScript
                echo json_encode([
                    "status"=>"sucesso",
                    "mensagem"=>"Login efetuado com sucesso",
                    "usuario"=>["nome"=>$usuario['nome'], "email"=>$email, "tipo"=>$tipo]
                ]);
                exit; // Para o script. Login feito com sucesso.
            } else {
                // Senha não bate com o hash
                echo json_encode(["status"=>"erro", "mensagem"=>"Senha incorreta"]);
                exit;
            }
        }
        return false; // Usuário não encontrado nesta tabela
    }

    // 1. Tenta logar como administrador
    loginUsuario($conexao, "administradores", "admin");

    // 2. Se a função não deu 'exit', tenta logar como cliente
    loginUsuario($conexao, "clientes", "usuario");

    // 3. Se passou pelas duas e não deu 'exit', o email não foi encontrado
    echo json_encode(["status"=>"erro","mensagem"=>"Usuário não encontrado"]);
    exit;
?>

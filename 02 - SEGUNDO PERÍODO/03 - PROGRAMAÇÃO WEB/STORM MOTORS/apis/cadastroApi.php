<?php
    // Inclui o arquivo de conexão com o banco de dados
    // Traz a variável $conexao para este script
    include "../bancoDeDados/conexaoBD.php"; 
    
    // Informa ao cliente (JavaScript/Navegador) que a resposta será no formato JSON
    header("Content-Type: application/json"); 

    // Pega os dados brutos (raw data) enviados pelo `fetch` no "body" da requisição
    $json = file_get_contents("php://input");
    
    // Converte (decodifica) a string JSON para um array associativo PHP
    // O `true` faz virar um array (ex: $dados['nome']), senão viraria um objeto
    $dados = json_decode($json, true);

    // Validação de back-end (importante por segurança)
    // Verifica se algum dos campos obrigatórios está vazio
    if (empty($dados['nome']) || empty($dados['endereco']) || empty($dados['email']) || empty($dados['senha']) || empty($dados['telefone'])) {
        // Retorna um código de erro HTTP (400 = Bad Request)
        http_response_code(400);
        // Envia uma resposta JSON de erro
        echo json_encode([
            "status" => "erro",
            "mensagem" => "Campos obrigatórios não preenchidos"
        ]);
        exit; // Para a execução do script
    }

    // --- Bloco de Segurança: Hashing de Senha ---
    // NUNCA salve senhas em texto puro!
    // `password_hash` cria uma criptografia (hash) segura da senha.
    $senhaHash = password_hash($dados['senha'], PASSWORD_DEFAULT);

    // --- Bloco de Segurança: Prepared Statements ---
    // Prepara o comando SQL com marcadores (?) para evitar SQL Injection
    $insert = $conexao->prepare("INSERT INTO clientes (nome, endereco, email, cpf, senha, telefone) VALUES (?, ?, ?, ?, ?, ?)");
    
    // Vincula (bind) as variáveis do PHP aos marcadores (?)
    // "ssssss" informa ao MySQL que todos os 6 parâmetros são strings
    $insert->bind_param("ssssss",
        $dados['nome'],
        $dados['endereco'],
        $dados['email'],
        $dados['cpf'],
        $senhaHash, // Salva o HASH seguro, não a senha original
        $dados['telefone']
    );

    // Executa o comando SQL preparado no banco de dados
    $salvarNoBanco = $insert->execute();

    // Verifica se a execução foi bem-sucedida
    if ($salvarNoBanco) {
        // Envia uma resposta JSON de sucesso para o JavaScript
        echo json_encode([
            "status" => "sucesso",
            "mensagem" => "Usuário cadastrado com sucesso",
            "usuario" => [ // (Opcional) Retorna os dados cadastrados
                "nome" => $dados['nome'],
                "email" => $dados['email'],
            ]
        ]);
    } else {
        // Se `execute()` falhar (ex: email duplicado)
        http_response_code(500); // Erro interno do servidor
        echo json_encode([
            "status" => "erro",
            "mensagem" => "Erro ao cadastrar usuário",
            "erro" => $insert->error // Retorna a mensagem de erro específica do MySQL
        ]);
    }
?>

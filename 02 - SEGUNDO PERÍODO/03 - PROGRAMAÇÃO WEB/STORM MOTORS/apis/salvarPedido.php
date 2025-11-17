<?php
    // Inicia a SESSÃO. Este arquivo SÓ mexe com a sessão.
    session_start();
    
    // Define a resposta como JSON
    header("Content-Type: application/json; charset=UTF-8");

    // Pega o objeto 'pedido' (JSON) que o `personalizar.php` (JS) enviou
    $dados = json_decode(file_get_contents("php://input"), true);

    if (!$dados) {
        echo json_encode(["erro" => "Nenhum dado recebido."]);
        exit;
    }

    // --- AÇÃO PRINCIPAL ---
    // Armazena o objeto 'pedido' completo (com as escolhas do usuário)
    // dentro da variável de SESSÃO PHP.
    // Isso funciona como um "carrinho de compras" temporário.
    // O pedido NÃO está no banco de dados ainda.
    $_SESSION["pedido_atual"] = $dados;

    // Envia uma resposta de sucesso para o `personalizar.php` (JS)
    echo json_encode(["sucesso" => true]);
?>

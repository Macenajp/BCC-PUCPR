<?php
    session_start();
    header("Content-Type: application/json; charset=UTF-8");

    $dados = json_decode(file_get_contents("php://input"), true);

    if (!$dados) {
        echo json_encode(["erro" => "Nenhum dado recebido."]);
        exit;
    }

    $_SESSION["pedido_atual"] = $dados;

    echo json_encode(["sucesso" => true]);
?>

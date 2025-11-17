<?php
    session_start();
    header("Content-Type: application/json");
    include "../bancoDeDados/conexaoBD.php";

    $query = $conexao->query("SELECT * FROM carros WHERE id IN (1, 13, 25)");

    if (!$query) {
        echo json_encode(["status"=>"erro", "mensagem"=>$conexao->error]);
        exit;
    }

    $carros = $query->fetch_all(MYSQLI_ASSOC);
    echo json_encode($carros);
?>

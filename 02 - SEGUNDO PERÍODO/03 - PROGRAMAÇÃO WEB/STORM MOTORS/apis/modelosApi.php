<?php
    // Inicia a sessão (boa prática, caso precise futuramente)
    session_start();
    
    // Informa que a resposta é JSON
    header("Content-Type: application/json");
    
    // Inclui a conexão com o banco
    include "../bancoDeDados/conexaoBD.php";

    // Executa uma consulta SQL (Query)
    // Seleciona TODOS os campos (*) da tabela `carros`
    // ONDE (WHERE) o ID do carro seja 1, 13, OU 25.
    $query = $conexao->query("SELECT * FROM carros WHERE id IN (1, 13, 25)");

    // Se a consulta falhar
    if (!$query) {
        echo json_encode(["status"=>"erro", "mensagem"=>$conexao->error]);
        exit;
    }

    // Coleta TODOS os resultados (as 3 linhas de carros) em um array
    $carros = $query->fetch_all(MYSQLI_ASSOC);
    
    // Envia o array de carros (em formato JSON) de volta para o JavaScript
    echo json_encode($carros);
?>

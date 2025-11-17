<?php
    // Define a resposta como JSON
    header("Content-Type: application/json; charset=UTF-8");
    
    // Inclui a conexão com o banco
    include "../bancoDeDados/conexaoBD.php";

    // Pega o parâmetro "modelo" da URL (enviado via GET pelo fetch)
    // Ex: ...?modelo=Bugatti%20Chiron
    $modelo = $_GET["modelo"] ?? null;

    if (!$modelo) {
        // Se o JS não enviar o modelo, retorna erro
        echo json_encode(["erro" => "Modelo não informado"]);
        exit;
    }

    // Prepara a consulta para buscar os dados base do carro
    $stmt = $conexao->prepare("SELECT * FROM carros WHERE modelo = ?");
    if (!$stmt) {
        echo json_encode(["erro" => "Erro ao preparar SQL", "detalhes" => $conexao->error]);
        exit;
    }

    $stmt->bind_param("s", $modelo); // Vincula o nome do modelo ao "?"
    $stmt->execute();
    $resultado = $stmt->get_result();

    // Pega os resultados (as várias versões V8/V10/V12 desse modelo)
    $carros = $resultado->fetch_all(MYSQLI_ASSOC);

    if (empty($carros)) {
        echo json_encode(["erro" => "Nenhum carro encontrado para este modelo."]);
        exit;
    }

    // Envia os dados dos carros (em JSON) de volta para o `personalizar.php` (JS)
    echo json_encode($carros, JSON_UNESCAPED_UNICODE);
?>

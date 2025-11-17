<?php
    header("Content-Type: application/json; charset=UTF-8");
    include "../bancoDeDados/conexaoBD.php";

    $modelo = $_GET["modelo"] ?? null;

    if (!$modelo) {
        echo json_encode(["erro" => "Modelo não informado"]);
        exit;
    }

    $stmt = $conexao->prepare("SELECT * FROM carros WHERE modelo = ?");
    if (!$stmt) {
        echo json_encode(["erro" => "Erro ao preparar SQL", "detalhes" => $conexao->error]);
        exit;
    }

    $stmt->bind_param("s", $modelo);
    $stmt->execute();
    $resultado = $stmt->get_result();

    if (!$resultado) {
        echo json_encode(["erro" => "Erro na execução do SQL", "detalhes" => $conexao->error]);
        exit;
    }

    $carros = $resultado->fetch_all(MYSQLI_ASSOC);

    if (empty($carros)) {
        echo json_encode(["erro" => "Nenhum carro encontrado para este modelo."]);
        exit;
    }

    echo json_encode($carros, JSON_UNESCAPED_UNICODE);
?>

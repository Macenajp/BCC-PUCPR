<?php
session_start(); // MUITO IMPORTANTE que fique no topo

// Conexão
$dbHost = 'localhost:3306';
$dbUsername = 'root';
$dbSenha = '8676';
$dbName = 'banco_de_dados';
$conexao = new mysqli($dbHost, $dbUsername, $dbSenha, $dbName);

$erro1 = '';
$erro2 = '';

if (isset($_POST['submit'])) {
    $email = ($_POST['email']);
    $senha = ($_POST['senha']);

    if (empty($email) || empty($senha)) {
        $erro1 = "Por favor, preencha email e senha!";
    } else {
        $sql = "SELECT * FROM cliente WHERE email='$email' AND senha='$senha'";
        $result = $conexao->query($sql);

        if ($result && $result->num_rows > 0) {
            $usuario = $result->fetch_assoc();
            $_SESSION['id'] = $usuario['id'];
            $_SESSION['nome'] = $usuario['nome'];
            $_SESSION['email'] = $usuario['email'];

            header("Location: inicio.php"); // Redireciona
            exit();
        } else {
            $erro2 = "Email ou senha incorretos!";
        }
    }
}
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="login.css">
    <link href="https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap" rel="stylesheet">
    <title>Login</title>
</head>     
<body>
    <div class="container">
        <div class="titulo">
            <h1>INÍCIO DE SESSÃO</h1>
            <h1 id="titulo-smt">SMT ID</h1>
            <h2>Não tem um SMT ID? Registre-se <a href="cadastro.php">aqui</a> </h2>
        </div>
        <form method="POST">
            <label for="email">Email</label>
            <input type="email" id="email" name="email">
            <label for="senha">Senha</label>
            <input type="password" id="senha" name="senha">
            
            <?php
                if(!empty($erro1)) {
                    echo "<p>$erro1</p>";
                }
            ?>

            <?php
                if (!empty($erro2)) {
                echo "<p>$erro2</p>";
                }
            ?>
            
            <button type="submit" name="submit">Continuar</button>
        </form>
    </div>

    <div class="container2">
        <img src="logo-smt.png" id="logo" width="115px" height="115px">
        <div class="box">
            <img src="carro4.jpg" width="1270px" height="720px">
        </div>
    </div>
</body>
</html>
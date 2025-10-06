<?php
session_start();
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="inicio.css">
    <link href="https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap" rel="stylesheet">
    <title>Início</title>
</head>
<body>
    <div class="container">
        <nav class="nav-bar">
            <a href="#inicio">Início</a>
            <a href="#cars">Modelos</a>
            <a href="#modificar">Personalização</a>
            <img src="logo-smt.png" width="100px" height="100px">
            <a href="">Pedidos</a>
            <a href="">Suporte</a>
            <div class="user">
                <div class="circle"> <img src="piloto.jpg" width="32px" height="32px"> </div>
                <p>Olá, <?php echo ($_SESSION['nome']); ?> </p>
            </div>
        </nav>
    </div>
    <div class="funcoes">
        <div class="concept-car">
                <h1>KOENIGSEGG</h1>
                <h1 id="jesko">JESKO</h1>
                <button>SAIBA MAIS</button>
            </div>
        <div class="video" id="inicio">
            <video src="concept-smt.mp4" autoplay loop muted></video>
        </div>
        <div class="cars" id="cars">
            <div class="img1"> <a href="#modificar"><img src="carro1.JPG" width="100%" height="100%" id="carro1"></a></div>
            <div class="img2"> <a href="#modificar"><img src="carro2.JPG" width="100%" height="100%" id="carro2"></a></div>
            <div class="img3"> <a href="#modificar"><img src="carro3.JPG" width="100%" height="100%" id="carro3"></a></div>
        </div>
    </div>
    <div class="modificar" id="modificar">
        <div class="box-modificar">
            <label for="carro-selecionado">PERSONALIZAR</label>
            <div class="carro-modificar"> <img id="carro-selecionado" src="carro1.JPG"> </div>
        </div>
            <div class="box-personalizar">
                <h1>MODELOS</h1>
                <div class="botoes-modelos">
                    <button id="carro-botao1">Bugatti Chiron</button>
                    <button id="carro-botao2">McLaren Senna</button>
                    <button id="carro-botao3">Range Rover</button>
                </div>
                <h1>PINTURA</h1>
                <div class="botoes-pinturas">
                    <button>Azul</button>
                    <button>Vermelho</button>
                    <button>Preto</button>
                </div>
                <h1>MOTORES</h1>
                <div class="botoes-motor">
                    <div class="motor1"> <img src=""> </div>
                    <div class="motor2"> <img src=""> </div>
                    <div class="motor3"> <img src=""> </div>
                </div>
                <h1>R$1.098.432</h1>
                <button id="comprar" type="submit" name="submit">Comprar</button>
            </div>
    </div>
    <script src="inicio.js"></script>
</body>
</html>
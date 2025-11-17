<?php
    // 1. Inicia a SESSÃO PHP
    session_start();
    
    // 2. Pega o nome do usuário (salvo na sessão durante o login)
    $nomeUsuario = $_SESSION['usuario_nome'];
    
    // 3. Pega o "carrinho" (pedido temporário) que a API `salvarPedido.php` guardou
    $pedido = $_SESSION["pedido_atual"];
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <title>Comprar</title>
</head>
<body>
    <div class="container">
        <nav class="nav-bar">
            <div class="user">
                <p>Olá, <?php echo ($_SESSION["usuario_nome"]) ?></p>
            </div>
        </nav>
    </div>
    <div class="main">
        <div class="quadrado-compra">
            <h1>COMPRAR</h1>
            <div class="infos-compra">
                <div class="quadrado-imagem">
                    <img src="<?php echo $pedido["imagem"]; ?>" ... >
                </div>
                <div class="info-produto">
                    <p><strong>Modelo:</strong> <?= htmlspecialchars($pedido['modelo']) ?></p>
                    <p><strong>Cor:</strong> <?= htmlspecialchars($pedido['cor']) ?></p>
                    <p><strong>Motor:</strong> <?= htmlspecialchars($pedido['motor']) ?></p>
                    <p><strong>Ano:</strong> <?= htmlspecialchars($pedido['ano']) ?></p>
                    <p><strong>Câmbio:</strong> <?= htmlspecialchars($pedido['cambio']) ?></p>
                    <p><strong>Combustível:</strong> <?= htmlspecialchars($pedido['combustivel']) ?></p>
                    <p><strong>Preço:</strong> <?= htmlspecialchars($pedido['valor']) ?></p>
                </div>
            </div>
            <button id="comprar">Comprar</button>
        </div>
    </div>

    <div class="overlay" id="popupOverlay">
        <div class="popup">
            <h2>Compra Concluída!</h2>
            <p>Obrigado por comprar com a SMT Motors, <?php echo ($_SESSION["usuario_nome"]); ?>.</p>
            <p>Seu pedido será processado em breve.</p>
            <button class="botao-ok" id="botaoOk">OK</button>
        </div>
    </div>

<script>
    // ... (lógica da navbar e seleção de botões de pagamento) ...

    // Seleciona os elementos do HTML
    const botaoComprar = document.getElementById('comprar'); // Botão "Comprar" final
    const popupOverlay = document.getElementById('popupOverlay'); // O popup
    const botaoOk = document.getElementById('botaoOk'); // Botão "OK" do popup

    // 9. "Escuta" o clique no botão "Comprar" final (PASSO 2 DO CHECKOUT)
    botaoComprar.addEventListener('click', async () => {
    try {
        // Monta o objeto 'pedido' em JavaScript
        // Ele lê os dados que o PHP injetou DIRETAMENTE no script
        // `addslashes` é usado pelo PHP para garantir que aspas (") não quebrem a string JS
        const pedido = {
            modelo: "<?= addslashes($pedido['modelo']) ?>",
            cor: "<?= addslashes($pedido['cor']) ?>",
            motor: "<?= addslashes($pedido['motor']) ?>",
            ano: "<?= addslashes($pedido['ano']) ?>",
            cambio: "<?= addslashes($pedido['cambio']) ?>",
            combustivel: "<?= addslashes($pedido['combustivel']) ?>",
            valor: "<?= addslashes($pedido['valor']) ?>",
            imagem: "<?= addslashes($pedido['imagem']) ?>",
            usuario: "<?= addslashes($nomeUsuario) ?>"
        };

        // 10. Chama a API FINAL (registrarPedido.php)
        // Esta API vai salvar o pedido no BANCO DE DADOS
        const resposta = await fetch('apis/registrarPedido.php', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(pedido) // Envia o objeto 'pedido'
        });

        const resultado = await resposta.json();

        // 11. Se a API (do banco) confirmar o sucesso...
        if (resultado.sucesso) {
            popupOverlay.style.display = 'flex'; // Mostra o popup "Compra Concluída"
        } else {
            // Se a API do banco retornar um erro
            alert('Erro ao registrar pedido: ' + (resultado.mensagem || 'Erro desconhecido'));
        }

    } catch (erro) {
        // Se houver um erro de rede
        alert('Falha ao conectar com o servidor: ' + erro);
    }
    });

    // 12. "Escuta" o clique no botão "OK" do popup
    botaoOk.addEventListener('click', () => {
        popupOverlay.style.display = 'none'; // Esconde o popup
        window.location.href = 'pedidos.php'; // Redireciona o usuário para "Meus Pedidos"
    });
</script>
</body>
</html>

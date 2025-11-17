<?php
    // Inicia a sessão
    session_start();
    
    // --- Bloco de Segurança (GATEKEEPER) ---
    // Verifica se a variável 'usuario_tipo' NÃO existe na sessão
    // OU se o tipo NÃO É 'admin'
    if (!isset($_SESSION['usuario_tipo']) || $_SESSION['usuario_tipo'] !== 'admin') {
        // Se não for admin, redireciona para a página inicial
        header("Location: inicio.php"); 
        exit; // Para a execução do script. O HTML abaixo não será renderizado.
}
?>

<!DOCTYPE html>
<html lang="pt-br">
<body>
    <div class="geral">
        <div class="quadrado">
            <h1>Histórico de Compras</h1>
            <div id="lista-compras"></div>
        </div>
    </div>


<script>
    // ... (código do scroll) ...

    // Função assíncrona para buscar o histórico (de TODOS)
    async function buscarHistorico() {
    try {
        // 1. Chama a API de administrador (apis/historicoComprasAdmApi.php)
        const resposta = await fetch('apis/historicoComprasAdmApi.php');
        if (!resposta.ok) throw new Error(`Erro na requisição: ${resposta.status}`);
        
        const dados = await resposta.json();

        // 2. A API de admin também tem uma verificação de segurança,
        // ela pode retornar {sucesso: false}
        if (!dados.sucesso) {
            console.error('Erro na API:', dados.mensagem); // Ex: "Acesso negado"
            return;
        }

        // 3. Seleciona a div de lista
        const lista = document.getElementById('lista-compras');
        lista.innerHTML = ''; 

        // 4. Itera sobre TODOS os pedidos de TODOS os clientes
        dados.pedidos.forEach(pedido => {
            const div = document.createElement('div');
            div.classList.add('pedido-item');
            
            // 5. Monta o HTML, incluindo o NOME DO CLIENTE (vinda da API)
            div.innerHTML = `
                <h3>Pedido #${pedido.pedido_id} - ${pedido.nome_cliente}</h3>
                ${pedido.imagem ? `<img src="${pedido.imagem}" alt="Imagem do pedido" width="200">` : ''}
                <p>Produto: ${pedido.nome_carro}</p>
                <p>Cor: ${pedido.cor}</p>
                <p>Preço: R$ ${pedido.preco}</p>
                <p>Data do Pedido: ${pedido.data_pedido}</p>
                <hr>
            `;
            // Adiciona o HTML na página
            lista.appendChild(div);
        });

    } catch (erro) {
        console.error('Erro ao buscar histórico:', erro);
    }
}

// 6. Chama a função ao carregar a página
buscarHistorico();
</script>
</body>
</html>

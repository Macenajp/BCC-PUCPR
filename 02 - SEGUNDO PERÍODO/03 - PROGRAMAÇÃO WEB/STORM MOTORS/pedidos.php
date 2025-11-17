<script>
    // ... (código do scroll da navbar) ...

    // Função assíncrona para buscar os pedidos do usuário
    async function buscarPedidos() {
    try {
        // 1. Chama a API (via GET)
        // A API `pedidosApi.php` vai olhar a SESSÃO PHP para saber
        // qual `id_usuario` está logado e buscará os pedidos dele.
        const resposta = await fetch('apis/pedidosApi.php');
        if (!resposta.ok) throw new Error(`Erro na requisição: ${resposta.status}`);
        
        // 2. Converte a resposta JSON (que contém a lista de pedidos)
        const dados = await resposta.json();

        // 3. Seleciona os locais no HTML onde os dados serão inseridos
        const listaPedidos = document.getElementById('lista-pedidos'); 
        const statusPedidos = document.getElementById('quadradinho4'); 

        // 4. Limpa o conteúdo "placeholder"
        listaPedidos.innerHTML = ''; 
        statusPedidos.innerHTML = '<h1>Status do Pedido</h1>'; 

        // 5. Itera sobre a lista de pedidos recebida da API
        dados.pedidos.forEach(pedido => {
            
            // 6. Cria o HTML dinâmico para as "Informações do Pedido"
            const divPedido = document.createElement('div');
            divPedido.classList.add('pedido');
            // Template string (``) para montar o HTML
            divPedido.innerHTML = `
                <h3>Pedido #${pedido.id}</h3>
                ${pedido.imagem ? `<img src="${pedido.imagem}" alt="Imagem do pedido" width="200">` : ''}
                <p>Produto: ${pedido.nome_carro}</p>
                <p>Cor: ${pedido.cor}</p>
                <p>Preço: R$ ${pedido.preco}</p>
                <p>Data de Compra: ${pedido.data_pedido}</p>
                <hr>
            `;
            // Adiciona o HTML criado à página
            listaPedidos.appendChild(divPedido);

            // 7. Verifica se este pedido tem uma lista de 'status' (vinda da API)
            if (pedido.status.length > 0) {
                // Cria o HTML dinâmico para o "Status do Pedido"
                const divStatus = document.createElement('div');
                divStatus.classList.add('status-pedido');

                let statusHTML = `<h3>Status do Pedido #${pedido.id}</h3><ul>`;
                
                // Itera sobre a lista de status de CADA pedido
                pedido.status.forEach(s => {
                    // Adiciona cada status como um item de lista (<li>)
                    statusHTML += `<li>${s.status} - ${new Date(s.data_status).toLocaleString()}</li>`;
                });
                statusHTML += '</ul>';

                divStatus.innerHTML = statusHTML;
                // Adiciona o HTML de status à página
                statusPedidos.appendChild(divStatus);
            }
        });

    } catch (erro) {
        console.error('Erro ao buscar pedidos:', erro);
    }
}

// 8. Chama a função para buscar os pedidos assim que a página carrega
buscarPedidos();
</script>

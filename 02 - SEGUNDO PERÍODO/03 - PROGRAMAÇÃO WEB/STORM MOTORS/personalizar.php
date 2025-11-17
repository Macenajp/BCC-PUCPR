<script>
    // Seleciona elementos do HTML
    const navbar = document.querySelector('.container');
    const imagemPrincipal = document.getElementById('imagem-principal');

    // Variáveis de "estado" (guardam as escolhas do usuário)
    let carroAtual = null; // Guarda os dados base (preço, ano...) do modelo selecionado
    let corAtual = 'Azul'; // Cor padrão inicial
    let motorAtual = null; // Motor (V8, V10, V12) ainda não selecionado

    // Adiciona 'ouvinte' de scroll na navbar
    window.addEventListener('scroll', () => {
        navbar.classList.toggle('scroll', window.scrollY > 50);
    });

    // 1. OUVINTE: Botões de MODELO de Carro
    document.querySelectorAll('.botao-carro').forEach(botao => {
        botao.addEventListener('click', async () => {
            // Pega os dados 'data-modelo' e 'data-id' do botão HTML
            const modelo = botao.dataset.modelo; // Ex: "Bugatti Chiron"
            const id = botao.dataset.id; // Ex: "1"

            // Remove a classe 'active' de outros botões (feedback visual)
            document.querySelectorAll('.botao-carro').forEach(b => b.classList.remove('active'));
            botao.classList.add('active'); // Adiciona 'active' ao botão clicado

            try {
                // Chama a API (via GET) para buscar os dados base deste modelo
                // `encodeURIComponent` formata o nome para a URL (ex: "Bugatti%20Chiron")
                const resposta = await fetch(`apis/personalizarApi.php?modelo=${encodeURIComponent(modelo)}`);
                const dados = await resposta.json();

                if (dados.erro) {
                    alert(dados.erro);
                    return;
                }

                // Armazena os dados base (preço, ano...) na variável global
                carroAtual = dados[0]; 

                // Chama a função para preencher o painel de informações
                atualizarInfos();

                // Define a cor padrão (Azul) se nenhuma tiver sido escolhida
                if (!corAtual) corAtual = 'Azul';

                // Atualiza a imagem principal
                atualizarImagem(id, corAtual);

            } catch (erro) {
                console.error("Erro ao buscar dados:", erro);
            }
        });
    });

    // 2. OUVINTE: Botões de COR
    document.querySelectorAll('.botao-cor').forEach(botao => {
        botao.addEventListener('click', () => {
            corAtual = botao.dataset.cor; // Atualiza a variável de estado 'corAtual'
            if (carroAtual) { // Só atualiza a imagem se um modelo já foi escolhido
                // Pega o ID do modelo ativo
                const id = document.querySelector('.botao-carro.active')?.dataset.id || carroAtual.id;
                atualizarImagem(id, corAtual); // Atualiza a imagem
                document.getElementById('cor').textContent = corAtual; // Atualiza o texto da cor
            }
        });
    });

    // 3. OUVINTE: Botões de MOTOR
    document.querySelectorAll('.botao-motor').forEach(botao => {
        botao.addEventListener('click', () => {
            motorAtual = botao.dataset.motor; // Atualiza a variável de estado 'motorAtual'
            document.getElementById('motor').textContent = motorAtual; // Atualiza o texto do motor
        });
    });

    // Função interna para montar o nome da imagem e trocá-la
    function atualizarImagem(id, cor) {
        // Formata o nome da cor (ex: "azul" -> "Azul")
        const corFormatada = cor.charAt(0).toUpperCase() + cor.slice(1).toLowerCase();
        // Monta o nome do arquivo de imagem (ex: "carro1AzulEstendido.JPG")
        const nomeImagem = `carro${id}${corFormatada}Estendido.JPG`;
        // Define o `src` (fonte) da imagem no HTML
        imagemPrincipal.src = `midias/${nomeImagem}`;
    }

    // Função interna para preencher o painel de "info-carro"
    function atualizarInfos() {
        document.getElementById('modelo').textContent = carroAtual.modelo;
        document.getElementById('cor').textContent = carroAtual.cor; // (cor base)
        document.getElementById('motor').textContent = carroAtual.motor; // (motor base)
        document.getElementById('ano').textContent = carroAtual.ano;
        document.getElementById('cambio').textContent = carroAtual.cambio;
        document.getElementById('combustivel').textContent = carroAtual.combustivel;
        document.getElementById('valor').textContent = carroAtual.valor;
    }

    // OUVINTE: Carregamento da Página (window "load")
    // (Carrega um carro padrão, Bugatti Chiron, quando a página abre)
    window.addEventListener("load", async () => {
        try {
            // Define os valores padrão
            const modeloPadrao = "Bugatti Chiron"; 
            const idPadrao = 1; 
            const corPadrao = "Azul"; 

            // Busca os dados do modelo padrão
            const resposta = await fetch(`apis/personalizarApi.php?modelo=${encodeURIComponent(modeloPadrao)}`);
            const dados = await resposta.json();

            // Se os dados vieram corretamente
            if (dados && !dados.erro) {
                carroAtual = dados[0]; // Define o estado
                corAtual = corPadrao; // Define o estado
                atualizarInfos(); // Preenche o painel
                atualizarImagem(idPadrao, corPadrao); // Mostra a imagem
            }
        } catch (erro) {
            console.error("Erro ao carregar imagem padrão:", erro);
        }
    });

    // 4. OUVINTE: Botão "Comprar" (PASSO 1 DO CHECKOUT)
    const botaoComprar = document.getElementById('botao-comprar');
    botaoComprar.addEventListener('click', async () => {
        
        // Validação: Garante que o usuário escolheu todas as opções
        if (!carroAtual || !corAtual || !motorAtual) {
            alert("Por favor, selecione o modelo, a cor e o motor antes de comprar!");
            return;
        }

        // Monta o objeto 'pedido' final com base nas variáveis de estado
        const pedido = {
            modelo: carroAtual.modelo,
            cor: corAtual, // A cor que o usuário escolheu
            motor: motorAtual, // O motor que o usuário escolheu
            ano: carroAtual.ano,
            cambio: carroAtual.cambio,
            combustivel: carroAtual.combustivel,
            valor: carroAtual.valor,
            imagem: imagemPrincipal.src // A URL da imagem que está sendo exibida
        };

        // Chama a API "salvarPedido.php" (via POST) para guardar este objeto
        // na SESSÃO PHP (como um "carrinho de compras" temporário)
        const resposta = await fetch("apis/salvarPedido.php", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(pedido) // Envia o objeto 'pedido'
        });

        const resultado = await resposta.json();

        // Se a API confirmar que salvou na sessão...
        if (resultado.sucesso) {
            // Redireciona o usuário para a página de confirmação (checkout)
            window.location.href = "comprar.php";
        } else {
            alert("Erro ao salvar o pedido.");
        }
    });
</script>

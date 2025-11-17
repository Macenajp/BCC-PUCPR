<script>
    // Seleciona a barra de navegação
    const navbar = document.querySelector('.container');

    // Adiciona um "ouvinte" ao evento de 'scroll' (rolar a página)
    window.addEventListener('scroll', () => {
        // Se o usuário rolou mais de 50 pixels para baixo
        if (window.scrollY > 50) {  
            navbar.classList.add('scroll'); // Adiciona a classe CSS 'scroll' (muda o fundo)
        } else {
            navbar.classList.remove('scroll'); // Remove a classe (fundo transparente)
        }
    });

   // Função assíncrona para carregar os dados dos carros
   async function carregarCarros() {
    try {
        // Chama a API (via GET) para buscar a lista de carros
        const resposta = await fetch("apis/modelosApi.php");
        
        // Converte a resposta JSON da API em um array de objetos JS
        // Ex: [ {modelo: "Bugatti..."}, {modelo: "McLaren..."} ]
        const carros = await resposta.json();

        // Seleciona os três "quadrados" do HTML onde os dados serão mostrados
        const quadrados = [
            document.querySelector(".quadrado1"),
            document.querySelector(".quadrado2"),
            document.querySelector(".quadrado3")
        ];

        // Itera sobre a lista de carros (forEach)
        // `carro` é o objeto (ex: {modelo: "Bugatti..."})
        // `index` é a posição (0, 1, ou 2)
        carros.forEach((carro, index) => {
            const quadrado = quadrados[index]; // Pega o "quadrado" HTML correspondente
            if (quadrado) {
                // Lista dos campos que queremos preencher
                const campos = ["modelo", "cor", "motor", "ano", "cambio", "combustivel", "valor"];
                
                // Itera sobre a lista de campos
                campos.forEach(campo => {
                    // Seleciona o <span> com a classe correspondente DENTRO do "quadrado"
                    // Ex: quadrado.querySelector(".modelo")
                    const span = quadrado.querySelector(`.${campo}`);
                    if (span) {
                        // --- Injeção Dinâmica de HTML ---
                        // Define o texto do <span> para o valor vindo da API
                        // Ex: span.textContent = carro["modelo"] (que é "Bugatti Chiron")
                        span.textContent = carro[campo];
                    }
                });
            }
        });
    } catch (error) {
        // Captura erros de rede ou se a API falhar
        console.error("Erro ao carregar carros:", error);
    }
}
// Chama a função imediatamente para carregar os carros assim que a página abrir
carregarCarros();
</script>

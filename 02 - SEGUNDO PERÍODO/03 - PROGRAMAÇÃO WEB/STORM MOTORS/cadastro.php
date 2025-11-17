<script>
    // Seleciona o elemento <form> do HTML pelo seu ID
    const form = document.getElementById("formCadastro");
    
    // Define a URL da API (arquivo PHP) que receberá os dados
    const url = "apis/cadastroApi.php";
    
    // Seleciona o elemento <p> onde as mensagens de erro serão exibidas
    const erroElemento = document.getElementById("erro");

    // Adiciona um "ouvinte" ao formulário que "escuta" pelo evento "submit" (envio)
    form.addEventListener("submit", chamarApi);

    // Função assíncrona (async) que é chamada quando o formulário é enviado
    async function chamarApi(event) {
        // Impede o comportamento padrão do formulário (que é recarregar a página)
        event.preventDefault(); 
        
        // Coleta todos os dados preenchidos nos campos do formulário
        const dadosForm = new FormData(form);
        
        // Converte os dados do formulário em um objeto JavaScript (ex: {nome: "...", email: "..."})
        const dados = Object.fromEntries(dadosForm.entries()); 

        try {
            // `fetch` é a função que faz a chamada de rede para a API
            // `await` pausa a função até que a chamada seja concluída
            const resposta = await fetch(url, {
                method: "POST", // Método HTTP: "POST" é usado para ENVIAR dados
                headers: { "Content-Type": "application/json" }, // Avisa a API que estamos enviando dados no formato JSON
                body: JSON.stringify(dados) // Converte o objeto JS em uma string JSON para envio
            });

            // Pega a resposta da API (que é texto)
            const texto = await resposta.text();
            let objeto;

            // Tenta converter o texto da resposta (JSON) de volta para um objeto JS
            try {
                objeto = JSON.parse(texto);
                console.log(objeto); // Mostra o objeto no console (bom para debug)
            } catch (e) {
                console.log("Erro: resposta da API inválida");
                return; // Para a execução se a resposta não for JSON
            }

            // Verifica o campo "status" da resposta da API
            if (objeto.status === "erro") {
                erroElemento.textContent = objeto.mensagem; // Mostra a mensagem de erro (vinda da API) no HTML
                erroElemento.style.color = "red";
                return; // Para a execução
            }

            // Se a API respondeu com "sucesso"...
            if (objeto.status === "sucesso") {
                erroElemento.textContent = ""; // Limpa a mensagem de erro
                form.reset(); // Limpa os campos do formulário
                window.location.href = "login.php"; // Redireciona o usuário para a página de login
            }

        } catch (error) {
            // Captura erros de rede (ex: API offline ou URL errada)
            console.error("Erro na requisição:", error);
        }
    }
</script>

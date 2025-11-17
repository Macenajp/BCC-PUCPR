<script>
    // Seleciona o formulário de login pelo ID
    const formLogin = document.getElementById("formLogin");
    
    // URL da API de login
    const urlLogin = "apis/loginApi.php"; 

    // Elemento <p> para exibir erros
    const erroElemento = document.getElementById("erro");

    // "Escuta" o evento de envio (submit) do formulário
    formLogin.addEventListener("submit", async (event) => {
        event.preventDefault(); // Impede o recarregamento da página

        // Coleta os dados do formulário (email, senha)
        const dadosForm = new FormData(formLogin);
        const dados = Object.fromEntries(dadosForm.entries());

        erroElemento.textContent = ""; // Limpa erros antigos

        try {
            // Chama a API de login, enviando os dados (email, senha) via POST
            const resposta = await fetch(urlLogin, {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(dados)
            });

            let objeto;

            // Tenta decodificar a resposta JSON da API
            try {
                objeto = await resposta.json();
                console.log(objeto); // Loga a resposta no console (para debug)
            } catch (e) {
                erroElemento.textContent = "Resposta inválida da API.";
                return;
            }

            // Se a API responder com status "erro"
            if (objeto.status === "erro") {
                erroElemento.textContent = objeto.mensagem; // Ex: "Senha incorreta"
                erroElemento.style.color = "red";
            }

            // Se a API responder com status "sucesso"
            if (objeto.status === "sucesso") {
                formLogin.reset(); // Limpa os campos de email e senha
                // Redireciona o usuário para a página inicial
                // Ele está "logado" agora, pois a API criou uma Sessão PHP
                window.location.href = "inicio.php";
            }
        } catch (error) {
            // Captura erros de rede
            console.error("Erro:", error);
        }
    });
</script>

const navbar = document.querySelector('.container');

window.addEventListener('scroll', () => {
    if (window.scrollY > 50) {  
        navbar.classList.add('scroll');
    } else {
        navbar.classList.remove('scroll');
    }
});

const carros = document.querySelectorAll("#carro1, #carro2, #carro3");
const exibir = document.getElementById("carro-selecionado");

carros.forEach(carro => {
    carro.addEventListener("click", () => {
        exibir.src = carro.src; 
        exibir.style.display = "block"; 
    });
});

const carrosBotao = document.querySelectorAll("#carro-botao1, #carro-botao2, #carro-botao3");
const exibicao = document.getElementById("carro-selecionado");

carrosBotao.forEach(carroBotao => {
    carroBotao.addEventListener("click", () => {
        if(carroBotao.id === "carro-botao1") {
            exibicao.src = "carro1.JPG";
        } else if(carroBotao.id === "carro-botao2") {
            exibicao.src = "carro2.JPG";
        } else if(carroBotao.id === "carro-botao3") {
            exibicao.src = "carro3.JPG";
        }
        exibicao.style.display = "block";
    });
});

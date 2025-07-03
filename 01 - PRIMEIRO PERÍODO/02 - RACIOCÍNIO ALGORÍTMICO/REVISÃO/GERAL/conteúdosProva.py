# Funções:

#1) Crie uma função que retorna o(s) nome(es) com idade igual ou superior a 18 (x >= 18):
nomes = ["Ana", "Carlos", "Bruna", "Diego"]
idades = [17, 20, 15, 22]

def maiorIdade(nomes, idades):
    resultado = []
    for i in range(len(nomes)):
        if idades[i] >= 18:
            resultado.append(nomes[i])
    return resultado

print(maiorIdade(nomes, idades))

#2) Crie uma função, onde, daado um valor máximo, retorna nomes das frutas com preço menor ou igual:
def frutas_ate(preco_maximo, frutas, precos):
    resultado = []
    for i in range(len(frutas)):
        if precos[i] <= preco_maximo:
            resultado.append(frutas[i])
    return resultado

frutas = ["maca", "banana", "uva", "abacaxi", "laranja"]
preços = [2.5, 1.2, 3.0, 4.0, 2.2]

print(frutas_ate(2.5, frutas, preços))  # valor máximo: 2.5

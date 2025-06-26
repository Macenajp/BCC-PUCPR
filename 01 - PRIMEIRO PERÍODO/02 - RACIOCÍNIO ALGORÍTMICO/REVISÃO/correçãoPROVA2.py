"""
==================
QUESTÃO 1 DA PROVA
==================
"""
lista = [10, 20, 30, 40]

lista.append("bola")
print(lista)
# Resposta: [10, 20, 30, 40, 'bola']

lista.remove(30)
print(lista)
# Resposta: [10, 20, 40, 'bola']

lista.insert(2, 50)
print(lista)
# Resposta: [10, 20, 50, 40, 'bola']

lista.reverse()
print(lista)
# Resposta: ['bola', 40, 50, 20, 10]

lista.insert(2,10)
print(lista, "\n\n")
# Resposta: ['bola', 40, 10, 50, 20, 10]


"""
==================
QUESTÃO 2 DA PROVA
==================
"""
def função1(x):
    return x + 10
def função2(x):
    return x * 2
def função3(x):
    return x / 2

#a) Resposta: 75
função1(10) + função2(20) + função3(30)

#b) Resposta: 30
função1(função2(10))

#c) Resposta: 20
função1(função3(20))

#d) Resposta: 40
função3(função2(função1(30)))


"""
==================
QUESTÃO 3 DA PROVA
==================
"""
def função4(x):
    s = 0
    for i in range(5):
        s += função2(função1(i * x))
    return função3(s)

print(função4(2))
print(função4(6))
print(função4(8))
print(função4(10),"\n\n")


"""
==================
QUESTÃO 4 DA PROVA
==================
"""
def cria_matriz(lin, col, valor):
    m = []
    for i in range(lin):
        linha = []
        for j in range(col):
            linha.append(valor)
        m.append(linha)
    return m

print(cria_matriz(2, 2, 10), "\n\n")


"""
==================
QUESTÃO 5 DA PROVA
==================
"""
cidades = ["Curitiba", "Florianópolis", "Porto Alegre", "São Paulo", "Rio de Janeiro"]
distancias = [[0, 310, 716, 408, 852],
              [310, 0, 470, 705, 1144],
              [716, 470, 0, 1119, 1553],
              [408, 705, 1119, 0, 429],
              [852, 1144, 1553, 429, 0]]

def cidadeDistancia(cidade, raio):
    resultado = []
    if cidade in cidades:
        pos = cidades.index(cidade)
        for cid in range(len(distancias[pos])):
            if distancias[pos][cid] <= raio:
                resultado.append(cidades[cid])
    else:
        print("Cidade inexistente.")
    return resultado
print(cidadeDistancia("Curitiba", 500))

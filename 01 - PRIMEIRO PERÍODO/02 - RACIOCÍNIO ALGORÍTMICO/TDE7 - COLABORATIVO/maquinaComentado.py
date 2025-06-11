# =============================
# 📦 IMPORTAÇÃO DE MÓDULOS
# =============================
from time import sleep  # Importa a função sleep para simular tempo de espera

# =============================
# 📋 DADOS INICIAIS (ESTOQUE E PRODUTOS)
# =============================

# Lista com ID, preço e quantidade de cada produto
valores_e_quantidades = [
    [1, 3.75, 2],     # Produto 1: Coca-Cola
    [2, 3.67, 5],     # Produto 2: Pepsi
    [3, 9.96, 1],     # Produto 3: Monster
    [4, 1.25, 100],   # Produto 4: Café
    [5, 13.99, 2],    # Produto 5: Redbull
]

# Lista com nomes dos produtos
produtos = ['Coca-Cola', 'Pepsi', 'Monster', 'Café', 'Redbull']

# Dicionário com o estoque de moedas e cédulas para troco
estoque_troco = {
    100: 2, 50: 3, 20: 5, 10: 5, 5: 5, 2: 10,
    1: 20, 0.5: 30, 0.25: 40, 0.10: 50, 0.05: 50, 0.01: 100
}

# =============================
# 💰 FUNÇÃO: Calcular e Dar Troco
# =============================
def calcular_troco(produto_selecionado, fazendo_pagamento):
    print('-=' * 20)
    troco = fazendo_pagamento - valores_e_quantidades[produto_selecionado][1]  # Valor do troco
    troco_centavos = int(round(troco * 100))  # Conversão para centavos para evitar erros de ponto flutuante
    troco_usado = {}  # Dicionário com as moedas/cédulas usadas

    for moeda in sorted(estoque_troco, reverse=True):  # Ordena moedas/cédulas do maior para o menor
        moeda_centavos = int(round(moeda * 100))
        quantidade_necessaria = troco_centavos // moeda_centavos  # Quantidade necessária dessa moeda
        quantidade_usada = min(quantidade_necessaria, estoque_troco[moeda])  # Quantidade que pode ser usada

        if quantidade_usada > 0:
            troco_usado[moeda] = quantidade_usada
            troco_centavos -= quantidade_usada * moeda_centavos

    if troco_centavos > 0:  # Se não conseguiu dar o troco completo
        print("Não há troco suficiente no estoque! Venda cancelada.")
        return None

    for moeda, qtd in troco_usado.items():  # Atualiza estoque de troco
        estoque_troco[moeda] -= qtd

    print(f'Seu troco é: R$ {troco:.2f}')
    for moeda, qtd in troco_usado.items():
        tipo = "cédula(s)" if moeda >= 1 else "moeda(s)"
        print(f'{qtd} {tipo} de R$ {moeda:.2f}')

# =============================
# 💰 FUNÇÃO: Selecionar Modo de Operação
# =============================
def seleção_de_modo():
    print('-=' * 20)
    print('Bem-vindo à Máquina de Bebidas! \n1 -> Modo Administrador \n2 -> Comprar')
    return int(input('Selecione o modo desejado: '))  # Retorna o modo escolhido

# =============================
# 🔧 FUNÇÃO: Modo Administrador
# =============================
def modo_administrador():
    print('-=' * 20)
    print('Você está no modo administrador!')
    print('1 -> Cadastrar Produto \n2 -> Editar Produto \n3 -> Remover Produto')
    return int(input('Selecione a opção desejada: '))

# =============================
# 🛍️ FUNÇÃO: Escolher Produto
# =============================
def escolher_produto():
    print('-=' * 20)
    print('Você está no modo de compra!')
    for i in range(len(produtos)):
        print(f'{i} -> {produtos[i]} R$ {valores_e_quantidades[i][1]}')
    return int(input('Selecione o produto que você deseja comprar: '))

# =============================
# 🔍 FUNÇÃO: Verificar Disponibilidade
# =============================
def se_estiver_disponivel(produto_selecionado):
    print('-=' * 20)
    estoque = valores_e_quantidades[produto_selecionado][2]  # Quantidade em estoque
    if estoque > 0:
        print(f'Você escolheu: {produtos[produto_selecionado]}! Há {estoque} unidades!')
        return int(input('Você deseja comprar o produto? \n1 - Sim \n2 - Não \nSelecione a opção desejada: '))
    else:
        print(f'Você escolheu: {produtos[produto_selecionado]}, porém está indisponível =(')
        return 2

# =============================
# 💳 FUNÇÃO: Realizar Pagamento
# =============================
def pagamento(produto_selecionado, deseja_comprar):
    print('-=' * 20)
    if deseja_comprar == 1:
        print('Boa escolha! É uma ótima bebida!')
        valor = valores_e_quantidades[produto_selecionado][1]
        print(f'O valor total é de: R$ {valor:.2f}')

        while True:
            pagamento = float(input('Insira o pagamento: '))
            if pagamento >= valor:
                return pagamento
            else:
                print('Valor insuficiente! Tente novamente!')
    else:
        print('Você pode escolher outra bebida se quiser!')
        print('Encerrando operação...')
        return None

# =============================
# ✅ FUNÇÃO: Confirmar Pagamento e Entregar Produto
# =============================
def conferindo_pagamento(produto_selecionado, deseja_comprar, fazendo_pagamento):
    print('-=' * 20)
    if fazendo_pagamento >= valores_e_quantidades[produto_selecionado][1]:
        print('Pagamento efetuado com sucesso!')
        print('Retirando sua bebida...')
        sleep(2)  # Simula o tempo de entrega da bebida
        print(f'Pegue seu/sua {produtos[produto_selecionado]}! \nObrigado pela preferência!')
    else:
        print('Dinheiro insuficiente =( \nVocê pode tentar outra bebida!')

# =============================
# 🔁 LOOP PRINCIPAL DO SISTEMA
# =============================
while True:
    escolha = seleção_de_modo()  # Seleciona modo de operação

    if escolha == 1:  # Modo administrador
        modos = modo_administrador()

        if modos == 1:  # Cadastrar novo produto
            novo_nome = input('Digite o nome do novo produto: ')
            novo_preço = float(input('Digite o preço do novo produto: '))
            qtd_produto = int(input('Digite a quantidade em estoque: '))
            novo_id = len(valores_e_quantidades) + 1

            produtos.append(novo_nome)
            valores_e_quantidades.append([novo_id, novo_preço, qtd_produto])
            print(f'Produto "{novo_nome}" cadastrado com sucesso!')

        elif modos == 2:  # Editar produto existente
            produto_id = int(input('Digite o ID do produto que deseja editar: '))
            editar_nome = input('Digite o novo nome do produto: ')
            editar_preço = float(input('Digite o novo preço do produto: '))
            editar_qtd = int(input('Digite a nova quantidade em estoque: '))

            produtos[produto_id] = editar_nome
            valores_e_quantidades[produto_id][1] = editar_preço
            valores_e_quantidades[produto_id][2] = editar_qtd
            print('Produto editado com sucesso!')

        elif modos == 3:  # Remover produto
            remover_produto = int(input('Digite o ID do produto que deseja remover: '))
            nome_removido = produtos[remover_produto]
            del produtos[remover_produto]
            del valores_e_quantidades[remover_produto]
            print(f'Produto "{nome_removido}" removido com sucesso!')

    elif escolha == 2:  # Modo de compra
        produto_selecionado = escolher_produto()
        if produto_selecionado < 0 or produto_selecionado >= len(produtos):
            print('ID inválido!')
            continue

        deseja_comprar = se_estiver_disponivel(produto_selecionado)
        if deseja_comprar == 2:
            continue

        fazendo_pagamento = pagamento(produto_selecionado, deseja_comprar)
        if fazendo_pagamento is None:
            continue

        troco = calcular_troco(produto_selecionado, fazendo_pagamento)
        if troco is None:
            print('Venda cancelada devido à falta de troco.')
            continue

        valores_e_quantidades[produto_selecionado][2] -= 1  # Atualiza estoque do produto

        conferindo_pagamento(produto_selecionado, deseja_comprar, fazendo_pagamento)  # Entrega produto

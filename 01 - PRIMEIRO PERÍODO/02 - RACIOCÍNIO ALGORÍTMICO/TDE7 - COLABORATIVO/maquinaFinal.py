from time import sleep

valores_e_quantidades = [
    [1, 3.75, 2],
    [2, 3.67, 5],
    [3, 9.96, 1],
    [4, 1.25, 100],
    [5, 13.99, 2],
]

produtos = ['Coca-Cola', 'Pepsi', 'Monster', 'Café', 'Redbull']

estoque_troco = {
    100: 2,   # R$ 100,00
    50: 3,    # R$ 50,00
    20: 5,    # R$ 20,00
    10: 5,    # R$ 10,00
    5: 5,     # R$ 5,00
    2: 10,    # R$ 2,00
    1: 20,    # R$ 1,00
    0.5: 30,  # R$ 0,50
    0.25: 40, # R$ 0,25
    0.10: 50, # R$ 0,10
    0.05: 50, # R$ 0,05
    0.01: 100 # R$ 0,01
}

def calcular_troco(produto_selecionado, fazendo_pagamento):
    print('-=' * 20)
    troco = fazendo_pagamento - valores_e_quantidades[produto_selecionado][1]
    if troco < 0:
        print('Pagamento insuficiente! Venda cancelada.')
        return None
    elif troco == 0:
        print('Pagamento exato, sem troco.')
        return {}

    troco_centavos = int(round(troco * 100))
    troco_usado = {}

    for moeda in sorted(estoque_troco.keys(), reverse=True):
        moeda_centavos = int(round(moeda * 100))
        quantidade_necessaria = troco_centavos // moeda_centavos
        quantidade_usada = min(quantidade_necessaria, estoque_troco[moeda])
        if quantidade_usada > 0:
            troco_usado[moeda] = quantidade_usada
            troco_centavos -= quantidade_usada * moeda_centavos

    if troco_centavos > 0:
        print("Não há troco suficiente no estoque! Venda cancelada.")
        return None

    # Descontar do estoque de troco
    for moeda, qtd in troco_usado.items():
        estoque_troco[moeda] -= qtd

    print(f'Seu troco é: R$ {troco:.2f}')
    for moeda, qtd in troco_usado.items():
        if moeda >= 1:
            print(f'{qtd} cédula(s) de R$ {moeda:.2f}')
        else:
            print(f'{qtd} moeda(s) de R$ {moeda:.2f}')

    return troco_usado

def seleção_de_modo():
    print('-=' * 20)
    print('Bem-vindo a Máquina de Bebidas! \n1 -> Modo Administrador \n2 -> Comprar')
    return int(input('Selecione o modo desejado: '))

def modo_administrador():
    print('-=' * 20)
    print('Você está no modo administrador!')
    print('1 -> Cadastrar Produto \n2 -> Editar Produto \n3 -> Remover Produto')
    return int(input('Selecione a opção desejada: '))

def escolher_produto():
    print('-=' * 20)
    print('Você está no modo de compra!')
    for i in range(len(produtos)):
        print(f'{i} -> {produtos[i]} R$ {valores_e_quantidades[i][1]}')
    return int(input('Selecione o produto que você deseja comprar: '))

def se_estiver_disponivel(produto_selecionado):
    print('-=' * 20)
    if valores_e_quantidades[produto_selecionado][2] > 0:
        print(f'Você escolheu: {produtos[produto_selecionado]}! Há {valores_e_quantidades[produto_selecionado][2]} unidades!')
        return int(input('Você deseja comprar o produto? \n1 - Sim \n2 - Não \nSelecione a opção desejada: '))
    else:
        print(f'Você escolheu: {produtos[produto_selecionado]}, porém está indisponível =(')
        return 2  # Não deseja comprar

def pagamento(produto_selecionado, deseja_comprar):
    print('-=' * 20)
    if deseja_comprar == 1:
        print('Boa escolha! É uma ótima bebida!')
        print(f'O valor total é de: R$ {valores_e_quantidades[produto_selecionado][1]:.2f}')

        while True:
            pagamento = float(input('Insira o pagamento: '))
            if pagamento >= valores_e_quantidades[produto_selecionado][1]:
                return pagamento
            else:
                print('Valor insuficiente! Tente Novamente!')

    elif deseja_comprar == 2:
        print('Você pode escolher outra bebida se quiser!')
        print('Encerrando operação...')
        print('Operação encerrada!')
        return None

def conferindo_pagamento(produto_selecionado, deseja_comprar, fazendo_pagamento):
    print('-=' * 20)
    if fazendo_pagamento >= valores_e_quantidades[produto_selecionado][1]:
        print('Pagamento efetuado com sucesso!')
        print('Retirando sua bebida...')
        sleep(1)
        print(f'Pegue seu/sua {produtos[produto_selecionado]}! \nObrigado pela preferência! Tenha um ótimo dia!')
    else:
        print('Dinheiro insuficiente =( \nVocê pode tentar outra bebida!')

while True:
    escolha = seleção_de_modo()

    if escolha == 1:
        modos = modo_administrador()

        if modos == 1:
            print('-=' * 20)
            print('Você selecionou a opção cadastrar produto!')
            novo_nome = input('Insira o nome do novo produto: ')
            novo_preço = float(input('Insira o preço do novo produto: '))
            qtd_produto = int(input('Insira a quantidade disponível do novo produto: '))
            novo_id = len(valores_e_quantidades) + 1
            print('Cadastrando produto...')
            sleep(2)
            produtos.append(novo_nome)
            valores_e_quantidades.append([novo_id, novo_preço, qtd_produto])
            print('Produto cadastrado com sucesso!')

        elif modos == 2:
            print('-=' * 20)
            print('Você selecionou a opção editar produto!')
            for i in range(len(produtos)):
                print(f'{i} -> {produtos[i]} R$ {valores_e_quantidades[i][1]:.2f}')
            produto_id = int(input('Insira o ID do produto que você deseja editar: '))
            editar_nome = str(input('Edite o nome do produto:'))
            editar_preço = float(input('Insira o novo preço do produto: '))
            editar_qtd = int(input('Insira a nova quantidade do produto: '))
            print('Editando produto...')
            sleep(2)
            valores_e_quantidades[produto_id][1] = editar_preço
            valores_e_quantidades[produto_id][2] = editar_qtd
            produtos[produto_id] = editar_nome  
            print('Produto editado com sucesso!')

        elif modos == 3:
            print('-=' * 20)
            print('Você selecionou a opção remover produto!')
            for i in range(len(produtos)):
                print(f'{i} -> {produtos[i]} R$ {valores_e_quantidades[i][1]:.2f}')
            remover_produto = int(input('Insira o ID do produto que você deseja remover: '))
            print('Removendo produto...')
            sleep(2)
            produtos.remove(produtos[remover_produto])
            print('Produto removido com sucesso!')

    elif escolha == 2:
        produto_selecionado = escolher_produto()

        if produto_selecionado < 0 or produto_selecionado >= len(produtos):
            print('ID inválido! Selecione uma bebida válida!')
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

        valores_e_quantidades[produto_selecionado][2] -= 1
        conferindo_pagamento(produto_selecionado, deseja_comprar, fazendo_pagamento)

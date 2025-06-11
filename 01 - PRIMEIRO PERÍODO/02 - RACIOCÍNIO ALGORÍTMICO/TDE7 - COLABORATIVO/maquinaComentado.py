# Importação do módulo time para simular delays no processamento
from time import sleep

"""
Estrutura de dados principal para armazenar produtos:
Cada sublista representa [ID, preço, quantidade em estoque]
Nota técnica: Usar lista de listas permite fácil indexação e manipulação,
porém em sistemas reais, classes ou namedtuples seriam mais apropriados
"""
valores_e_quantidades = [
    [1, 3.75, 2],   # ID 1, R$ 3.75, 2 unidades
    [2, 3.67, 5],    # ID 2, R$ 3.67, 5 unidades
    [3, 9.96, 1],    # ID 3, R$ 9.96, 1 unidade
    [4, 1.25, 100],  # ID 4, R$ 1.25, 100 unidades
    [5, 13.99, 2],   # ID 5, R$ 13.99, 2 unidades
]

# Lista de nomes dos produtos (índices correspondem a valores_e_quantidades)
produtos = ['Coca-Cola', 'Pepsi', 'Monster', 'Café', 'Redbull']

"""
Dicionário de estoque de troco:
- Chaves: valores monetários (float)
- Valores: quantidade disponível (int)
Observação técnica: Trabalhar com valores monetários como floats pode causar
problemas de arredondamento. Em produção, usar Decimal ou trabalhar com centavos
(inteiros) seria mais adequado.
"""
estoque_troco = {
    100: 2,   # 2 cédulas de R$ 100
    50: 3,    # 3 cédulas de R$ 50
    20: 5,    # 5 cédulas de R$ 20
    10: 5,    # 5 cédulas de R$ 10
    5: 5,     # 5 cédulas de R$ 5
    2: 10,    # 10 moedas de R$ 2
    1: 20,    # 20 moedas de R$ 1
    0.5: 30,  # 30 moedas de R$ 0,50
    0.25: 40, # 40 moedas de R$ 0,25
    0.10: 50, # 50 moedas de R$ 0,10
    0.05: 50, # 50 moedas de R$ 0,05
    0.01: 100 # 100 moedas de R$ 0,01
}

def calcular_troco(produto_selecionado, fazendo_pagamento):
    """
    Função para cálculo e distribuição ótima de troco
    Complexidade: O(n) onde n é o número de tipos de moedas/cédulas
    
    Args:
        produto_selecionado (int): Índice do produto selecionado
        fazendo_pagamento (float): Valor inserido pelo cliente
    
    Returns:
        dict: Dicionário com o troco calculado ou None em caso de erro
    """
    print('-=' * 20)  # Separador visual
    
    # Cálculo básico do troco
    troco = fazendo_pagamento - valores_e_quantidades[produto_selecionado][1]
    
    # Validações iniciais
    if troco < 0:
        print('Pagamento insuficiente! Venda cancelada.')
        return None
    elif troco == 0:
        print('Pagamento exato, sem troco.')
        return {}

    # Conversão para centavos para evitar problemas de arredondamento
    # Técnica: round() + int() é mais confiável que multiplicar por 100
    troco_centavos = int(round(troco * 100))
    troco_usado = {}

    # Algoritmo guloso para cálculo do troco
    # Ordena as moedas do maior para o menor valor
    for moeda in sorted(estoque_troco.keys(), reverse=True):
        moeda_centavos = int(round(moeda * 100))
        
        # Calcula quantas unidades desta moeda são necessárias
        quantidade_necessaria = troco_centavos // moeda_centavos
        
        # Não pode usar mais do que tem no estoque
        quantidade_usada = min(quantidade_necessaria, estoque_troco[moeda])
        
        if quantidade_usada > 0:
            troco_usado[moeda] = quantidade_usada
            troco_centavos -= quantidade_usada * moeda_centavos

    # Verifica se conseguiu dar todo o troco
    if troco_centavos > 0:
        print("Não há troco suficiente no estoque! Venda cancelada.")
        return None

    # Atualiza o estoque de moedas/cédulas
    for moeda, qtd in troco_usado.items():
        estoque_troco[moeda] -= qtd

    # Exibe o troco para o usuário
    print(f'Seu troco é: R$ {troco:.2f}')
    for moeda, qtd in troco_usado.items():
        if moeda >= 1:
            print(f'{qtd} cédula(s) de R$ {moeda:.2f}')
        else:
            print(f'{qtd} moeda(s) de R$ {moeda:.2f}')

    return troco_usado

def seleção_de_modo():
    """
    Função para seleção do modo de operação
    Retorna:
        int: 1 para administrador, 2 para compra
    """
    print('-=' * 20)
    print('Bem-vindo a Máquina de Bebidas! \n1 -> Modo Administrador \n2 -> Comprar')
    return int(input('Selecione o modo desejado: '))

def modo_administrador():
    """
    Interface do modo administrador
    Retorna:
        int: Opção selecionada (1-3)
    """
    print('-=' * 20)
    print('Você está no modo administrador!')
    print('1 -> Cadastrar Produto \n2 -> Editar Produto \n3 -> Remover Produto')
    return int(input('Selecione a opção desejada: '))

def escolher_produto():
    """
    Exibe lista de produtos disponíveis e captura escolha do usuário
    Retorna:
        int: Índice do produto selecionado
    """
    print('-=' * 20)
    print('Você está no modo de compra!')
    # Lista todos os produtos com formatação consistente
    for i in range(len(produtos)):
        print(f'{i} -> {produtos[i]} R$ {valores_e_quantidades[i][1]}')
    return int(input('Selecione o produto que você deseja comprar: '))

def se_estiver_disponivel(produto_selecionado):
    """
    Verifica disponibilidade e confirma intenção de compra
    Args:
        produto_selecionado (int): Índice do produto
    Retorna:
        int: 1 para sim, 2 para não
    """
    print('-=' * 20)
    if valores_e_quantidades[produto_selecionado][2] > 0:
        print(f'Você escolheu: {produtos[produto_selecionado]}! Há {valores_e_quantidades[produto_selecionado][2]} unidades!')
        return int(input('Você deseja comprar o produto? \n1 - Sim \n2 - Não \nSelecione a opção desejada: '))
    else:
        print(f'Você escolheu: {produtos[produto_selecionado]}, porém está indisponível =(')
        return 2  # Não deseja comprar

def pagamento(produto_selecionado, deseja_comprar):
    """
    Processa o pagamento do usuário
    Args:
        produto_selecionado (int): Índice do produto
        deseja_comprar (int): 1 para sim, 2 para não
    Retorna:
        float: Valor pago ou None se desistir
    """
    print('-=' * 20)
    if deseja_comprar == 1:
        print('Boa escolha! É uma ótima bebida!')
        print(f'O valor total é de: R$ {valores_e_quantidades[produto_selecionado][1]:.2f}')

        # Loop até receber pagamento suficiente
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
    """
    Finaliza a compra e entrega o produto
    Args:
        produto_selecionado (int): Índice do produto
        deseja_comprar (int): 1 para sim, 2 para não
        fazendo_pagamento (float): Valor pago
    """
    print('-=' * 20)
    if fazendo_pagamento >= valores_e_quantidades[produto_selecionado][1]:
        print('Pagamento efetuado com sucesso!')
        print('Retirando sua bebida...')
        sleep(1)  # Simula tempo de processamento
        print(f'Pegue seu/sua {produtos[produto_selecionado]}! \nObrigado pela preferência! Tenha um ótimo dia!')
    else:
        print('Dinheiro insuficiente =( \nVocê pode tentar outra bebida!')

# Loop principal da aplicação
while True:
    escolha = seleção_de_modo()

    # Modo Administrador
    if escolha == 1:
        modos = modo_administrador()

        # Cadastrar novo produto
        if modos == 1:
            print('-=' * 20)
            print('Você selecionou a opção cadastrar produto!')
            novo_nome = input('Insira o nome do novo produto: ')
            novo_preço = float(input('Insira o preço do novo produto: '))
            qtd_produto = int(input('Insira a quantidade disponível do novo produto: '))
            novo_id = len(valores_e_quantidades) + 1  # Auto-incremento do ID
            
            print('Cadastrando produto...')
            sleep(2)  # Simula tempo de processamento
            
            # Adiciona às estruturas de dados
            produtos.append(novo_nome)
            valores_e_quantidades.append([novo_id, novo_preço, qtd_produto])
            print('Produto cadastrado com sucesso!')

        # Editar produto existente
        elif modos == 2:
            print('-=' * 20)
            print('Você selecionou a opção editar produto!')
            # Lista produtos para seleção
            for i in range(len(produtos)):
                print(f'{i} -> {produtos[i]} R$ {valores_e_quantidades[i][1]:.2f}')
            
            produto_id = int(input('Insira o ID do produto que você deseja editar: '))
            editar_nome = str(input('Edite o nome do produto:'))
            editar_preço = float(input('Insira o novo preço do produto: '))
            editar_qtd = int(input('Insira a nova quantidade do produto: '))
            
            print('Editando produto...')
            sleep(2)
            
            # Atualiza os dados
            valores_e_quantidades[produto_id][1] = editar_preço
            valores_e_quantidades[produto_id][2] = editar_qtd
            produtos[produto_id] = editar_nome  
            print('Produto editado com sucesso!')

        # Remover produto
        elif modos == 3:
            print('-=' * 20)
            print('Você selecionou a opção remover produto!')
            # Lista produtos para seleção
            for i in range(len(produtos)):
                print(f'{i} -> {produtos[i]} R$ {valores_e_quantidades[i][1]:.2f}')
            
            remover_produto = int(input('Insira o ID do produto que você deseja remover: '))
            print('Removendo produto...')
            sleep(2)
            
            # Remove das estruturas de dados
            produtos.pop(remover_produto)
            valores_e_quantidades.pop(remover_produto)
            print('Produto removido com sucesso!')

    # Modo Compra
    elif escolha == 2:
        produto_selecionado = escolher_produto()

        # Valida ID do produto
        if produto_selecionado < 0 or produto_selecionado >= len(produtos):
            print('ID inválido! Selecione uma bebida válida!')
            continue  # Volta ao início do loop

        # Verifica disponibilidade
        deseja_comprar = se_estiver_disponivel(produto_selecionado)
        if deseja_comprar == 2:  # Não deseja comprar
            continue

        # Processa pagamento
        fazendo_pagamento = pagamento(produto_selecionado, deseja_comprar)
        if fazendo_pagamento is None:  # Desistiu
            continue

        # Calcula troco
        troco = calcular_troco(produto_selecionado, fazendo_pagamento)
        if troco is None:  # Problema no troco
            print('Venda cancelada devido à falta de troco.')
            continue

        # Atualiza estoque e finaliza compra
        valores_e_quantidades[produto_selecionado][2] -= 1  # Decrementa estoque
        conferindo_pagamento(produto_selecionado, deseja_comprar, fazendo_pagamento)
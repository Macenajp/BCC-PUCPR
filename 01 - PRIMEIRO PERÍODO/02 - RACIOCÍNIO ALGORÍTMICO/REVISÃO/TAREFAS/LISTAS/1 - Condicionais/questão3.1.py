print('Bem-vindos ao jogo de Par ou Ímpar!')

print('Jogador 1, faça sua escolha:')
escolhaDaJogada = int(input(f'1- Ímpar\n2- Par\n\nDigite a escolhida: '))

jogadaDoP1 = int(input('\nJogador 1, digite um valor entre 1 e 5: '))
jogadaDoP2 = int(input('Jogador 2, digite um valor entre 1 e 5: '))

if not (1 <= jogadaDoP1 <= 5 and 1 <= jogadaDoP2 <= 5):
    print('\nEsta rodada não valeu.')
else:
    soma = jogadaDoP1 + jogadaDoP2
    resultadoPar = soma % 2 == 0

    if resultadoPar:
        if escolhaDaJogada == 2:
            print('O jogador que venceu é o Jogador 1 -> Par venceu!')
        else:
            print('O jogador que venceu é o Jogador 2 -> Par venceu!')
    else:
        if escolhaDaJogada == 1:
            print('O jogador que venceu é o Jogador 1 -> Ímpar venceu!')
        else:
            print('O jogador que venceu é o Jogador 2 -> Ímpar venceu!')
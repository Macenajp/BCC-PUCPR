print('\nEscolha o destino da viagem:')
print('1- Região Norte \n2- Região Nordeste \n3- Região Centro-Oeste \n4- Região Sul')

destino = int(input('\nDigite o código do destino escolhido: '))
ida_e_volta = input('A viagem vai incluir ida e volta? (s/n): ').lower()

precoPassagem = 0

if destino == 1:
    if ida_e_volta == 's':
        precoPassagem = 900.00
    else:
        precoPassagem = 500.00
elif destino == 2:
    if ida_e_volta == 's':
        precoPassagem = 650.00
    else:
        precoPassagem = 350.00
elif destino == 3:
    if ida_e_volta == 's':
        precoPassagem = 600.00
    else:
        precoPassagem = 350.00
elif destino == 4:
    if ida_e_volta == 's':
        precoPassagem = 550.00
    else:
        precoPassagem = 300.00
else:
    print('Destino inválido.')

if precoPassagem > 0:
    print(f'O preço da passagem é R$ {precoPassagem:.2f}')
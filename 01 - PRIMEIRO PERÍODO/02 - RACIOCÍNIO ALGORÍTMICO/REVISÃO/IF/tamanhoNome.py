"""
Faça um programa que peça o primeiro nome do usuário. Se o nome tiver 4 letras ou
menos escreva "Seu nome é curto"; se tiver entre 5 e 6 letras, escreva
"Seu nome é normal"; maior que 6 escreva "Seu nome é muito grande".
"""
nome  = input('Insira o seu nome: ')
seuNome = int(len(nome))

if seuNome <= 4:
    print('Seu nome é curto. Possui', len(nome),'letras')

elif seuNome >=5 and seuNome <= 6:
    print('Seu nome possui um tamanho normal. Possui', len(nome),'letras')

elif seuNome >= 6:
    print('Seu nome é muito grande! Possui', len(nome), 'letras')
else:
    print("Nome inválido")

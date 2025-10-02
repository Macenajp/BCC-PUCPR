print('Muito bem, vamos calcular seu peso ideal!')
altura = float(input('Digite a sua altura: '))
genero = input(f'Analise as opões abaixo: \n1- Feminino\n2- Masculino\n\nEscolha (1/2): ')

if genero == '1':
    calculoF = (62.1 * altura) - 44.7
    print(f'Seu peso ideal é: {calculoF:.2f}')

elif genero == '2':
    calculoM = (72.7 * altura) - 58
    print(f'Seu peso ideal é: {calculoM:.2f}')

else:
    print('Valor inválido, tente novamente!')
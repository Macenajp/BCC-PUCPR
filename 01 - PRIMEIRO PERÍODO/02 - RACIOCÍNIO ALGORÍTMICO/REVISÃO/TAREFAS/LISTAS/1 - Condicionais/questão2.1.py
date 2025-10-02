print('Vamos calcular seu IMC!')
peso = float(input('Digite o seu peso: '))
altura = float(input('Digite a sua altura: '))

calculo = peso / (altura ** altura)

if calculo <= 18.5:
    print(f'Seu IMC é {calculo:.2f}. Você está abaixo do peso!')

elif 18.5 <= calculo <= 25:
    print(f'Seu IMC é: {calculo:.2f}. Você está com o peso normal!')

elif 25 <= calculo <= 30:
    print(f'Seu IMC é: {calculo:.2f}. Você está acima do peso!')

else:
    print(f'Seu IMC é: {calculo:.2f}. Você está obeso!')
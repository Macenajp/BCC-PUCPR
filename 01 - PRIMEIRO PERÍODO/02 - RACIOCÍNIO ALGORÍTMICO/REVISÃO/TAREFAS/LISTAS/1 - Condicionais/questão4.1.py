precoEtiqueta = float(input('Digite o preço normal de etiqueta do produto: R$ '))

print('\nEscolha a condição de pagamento:')
print('1- À vista em dinheiro ou cheque (10% de desconto) \n2- À vista no cartão de crédito (15% de desconto) \n3- Em duas vezes (preço normal de etiqueta) \n4- Em mais de duas vezes (10% de juros)')


condicaoPagamento = int(input('\nDigite o código da condição escolhida: '))

if condicaoPagamento == 1:
    valorFinal = precoEtiqueta * 0.90
    print(f'O valor final é R$ {valorFinal:.2f}')
elif condicaoPagamento == 2:
    valorFinal = precoEtiqueta * 0.85
    print(f'O valor final é R$ {valorFinal:.2f}')
elif condicaoPagamento == 3:
    valorFinal = precoEtiqueta
    print(f'O valor final é R$ {valorFinal:.2f} em 2x de R$ {valorFinal/2:.2f}')
elif condicaoPagamento == 4:
    valorFinal = precoEtiqueta * 1.10
    print(f'O valor final é R$ {valorFinal:.2f}')
else:
    print('Opção de pagamento inválida. Tente novamente.')
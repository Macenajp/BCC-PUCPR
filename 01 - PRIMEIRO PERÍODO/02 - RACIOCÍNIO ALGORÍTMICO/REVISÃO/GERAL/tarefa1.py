'''
anoDeNascimento = float(input('Insira o seu ano de nascimento: '))
validacao = input('Você já fez aniversário esse ano (s/n)? ')
anoAtual = 2025
if validacao == 'n':
   resultado = (anoAtual - 1) - anoDeNascimento
   print('Sua idade é:', resultado)
else:
   segundoResultado = anoAtual - anoDeNascimento
   print('Sua idade é:', segundoResultado)
'''




'''
nota1 = int(input('Informe a sua nota: '))
nota2 = int(input('Informe a sua nota: '))

media = (nota1 + nota2) / 2

if media >= 7:
    print('Você foi aprovado!')
else:
    print('Você foi reprovado!')

'''




'''
numero1 = int(input('Digite o primeiro número: '))
numero2 = int(input('Digite o primeiro número: '))
numero3 = int(input('Digite o primeiro número: '))

if numero2 > numero1 < numero3:
    print('O menor número é o primeiro: ', numero1)
if numero1 > numero2 < numero3:
    print('O menor número é o segundo: ', numero2)
if numero1 > numero3 < numero2:
    print('O menor número é o terceiro: ', numero3)

'''

"""
Faça um programa que pergunte a hora ao usuário e, baseando-se no horário
descrito, exiba a saudação apropriada. Ex. Bom dia 0-11, Boa tarde 12-17 
e Boa noite 18-23.
"""

horario = float(input('Que horas são agora? '))
if horario >= 0 and horario <= 11.59:
    print('Muito bem. Bom dia!')

elif horario >= 12 and horario <= 17.59:
    print('Muito bom. Boa tarde!')

elif horario >= 18 and horario <= 23.59:
    print('Muito bem então. Boa noite!')
    
else:
    print('Valor inválido!')

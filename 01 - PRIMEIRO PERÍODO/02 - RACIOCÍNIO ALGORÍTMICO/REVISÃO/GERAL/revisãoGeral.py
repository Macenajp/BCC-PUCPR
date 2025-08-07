primeiroNumero = int(input("Escolha o primeiro número para a soma: "))
segundoNumero = int(input("Escolha o segundo número para soma: "))
resultado = primeiroNumero + segundoNumero

print(resultado)

#=====================================================================
anoDeNascimento = int(input("Em que ano você nasceu? "))
idadeDoUsuario = 2025 - anoDeNascimento

print("A sua idade é:", idadeDoUsuario)

#=====================================================================
disciplina = input("Qual a disciplina escolhida? ")

primeiraNota = int(input("Escreva a nota do primeiro bimestre: "))
segundaNota = int(input("Escreva a nota do segundo bimestre: "))
terceiraNota = int(input("Escreva a nota do terceiro bimestre: "))
quartaNota = int(input("Escreva a nota do quarto bimestre: "))

mediaDasNotas = (primeiraNota + segundaNota + terceiraNota + quartaNota) / 4

print("Sua média geral da disciplina", disciplina, "é:", mediaDasNotas)

#=====================================================================
produto = input("Qual produto você quer comprar?" )
valor = float(input("Insira o valor do produto: "))
quantidade = int(input("Insira a quantidade que irá comprar: "))

valorFinal = valor * quantidade

print("O valor final de sua compra ficou:", valorFinal)

#=====================================================================	
produto = input("Qual produto você quer comprar?" )
valor = float(input("Insira o valor do produto: "))
quantidade = int(input("Insira a quantidade que irá comprar: "))

valorFinal = valor * quantidade

if valorFinal > 100:
	valorFinal * 0.15
else


print("O valor final de sua compra ficou:", valorFinal)









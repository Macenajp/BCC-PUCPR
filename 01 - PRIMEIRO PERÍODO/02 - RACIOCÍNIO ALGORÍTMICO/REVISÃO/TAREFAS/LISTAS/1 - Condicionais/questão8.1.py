print("Informe a data e hora inicial:\n")
ano = int(input("Ano (4 dígitos): "))
mes = int(input("Mês: "))
dia = int(input("Dia: "))
hora = int(input("Hora (0-23): "))
minuto = int(input("Minuto: "))
segundo = int(input("Segundo: "))

print("\nO que você quer acrescentar?")
print("1- Anos  2- Meses  3- Dias  4- Horas  5- Minutos  6- Segundos")

escolha = int(input("Escolha uma opção: "))
quantidade = int(input("Qual a quantidade? "))

if escolha == 1:
    ano += quantidade
elif escolha == 2:
    mes += quantidade
elif escolha == 3:
    dia += quantidade
elif escolha == 4:
    hora += quantidade
elif escolha == 5:
    minuto += quantidade
elif escolha == 6:
    segundo += quantidade

if segundo >= 60:
    minuto += segundo // 60
    segundo %= 60

if minuto >= 60:
    hora += minuto // 60
    minuto %= 60

if hora >= 24:
    dia += hora // 24
    hora %= 24

if mes > 12:
    ano += (mes - 1) // 12
    mes = (mes - 1) % 12 + 1

while True:
    confirmadoBissexto = False
    if ano % 4 == 0:
        if ano % 100 == 0:
            if ano % 400 == 0:
                confirmadoBissexto = True
        else:
            confirmadoBissexto = True

    diasNoMes = 31
    if mes == 2:
        if confirmadoBissexto:
            diasNoMes = 29
        else:
            diasNoMes = 28
    elif mes == 4 or mes == 6 or mes == 9 or mes == 11:
        diasNoMes = 30

    if dia <= diasNoMes:
        break

    dia -= diasNoMes
    mes += 1
    if mes > 12:
        mes = 1
        ano += 1

print("\nNova data:")
print(f"{dia:02}/{mes:02}/{ano} {hora:02}:{minuto:02}:{segundo:02}")
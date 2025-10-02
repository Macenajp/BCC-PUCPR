dia = int(input("Digite o dia do nascimento: "))
mes = int(input("Digite o mês do nascimento: "))
ano = int(input("Digite o ano do nascimento: "))

print("\n1–Simples  2–Abreviada  3–Completa")
formato = int(input("Digite o código do formato: "))

if not (1 <= mes <= 12):
    print("Mês inválido.")
elif formato == 1:
    print(f"{dia:02}/{mes:02}/{ano}")
elif formato == 2:
    meses = ("jan", "fev", "mar", "abr", "mai", "jun", "jul", "ago", "set", "out", "nov", "dez")
    print(f"{dia}/{meses[mes-1]}/{ano}")
elif formato == 3:
    meses = ("janeiro", "fevereiro", "março", "abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro")
    print(f"{dia} de {meses[mes-1]} de {ano}")
else:
    print("Escolha inválida.")
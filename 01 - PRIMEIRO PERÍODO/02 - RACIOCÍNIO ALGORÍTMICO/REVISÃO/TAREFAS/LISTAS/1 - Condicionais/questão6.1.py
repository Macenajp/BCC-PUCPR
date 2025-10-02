a = float(input("Digite o valor de A: "))
b = float(input("Digite o valor de B: "))
c = float(input("Digite o valor de C: "))

if a == 0:
    print("O valor de A não pode ser 0.")
else:
    delta = (b ** 2) - 4 * a * c

    if delta < 0:
        print("A equação não possui raízes reais.")
    elif delta == 0:
        x = -b / (2*a)
        print(f"A equação possui uma raiz real: {x}")
    else:
        raizDeDelta = delta ** 0.5
        x1 = (-b + raizDeDelta) / (2 * a)
        x2 = (-b - raizDeDelta) / (2 * a)
        print(f"A equação possui duas raízes reais, são elas: x1 = {x1} e x2 = {x2}")
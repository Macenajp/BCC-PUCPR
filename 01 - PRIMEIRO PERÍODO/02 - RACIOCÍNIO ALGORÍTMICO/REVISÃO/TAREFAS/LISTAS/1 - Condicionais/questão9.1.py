cpf = input("Digite os 11 dígitos do CPF (apenas números): ")

if not cpf.isdigit() or len(cpf) != 11:
    print("Entrada inválida. O CPF deve conter 11 dígitos numéricos.")
else:
    n1 = int(cpf[0])
    n2 = int(cpf[1])
    n3 = int(cpf[2])
    n4 = int(cpf[3])
    n5 = int(cpf[4])
    n6 = int(cpf[5])
    n7 = int(cpf[6])
    n8 = int(cpf[7])
    n9 = int(cpf[8])
    n10 = int(cpf[9])
    n11 = int(cpf[10])

    soma1 = (n1 * 10 + n2 * 9 + n3 * 8 + n4 * 7 + n5 * 6 + n6 * 5 + n7 * 4 + n8 * 3 + n9 * 2)

    resto1 = (soma1 * 10) % 11
    if resto1 == 10:
        resto1 = 0

    primeiroDigitoCorreto = (resto1 == n10)

    if not primeiroDigitoCorreto:
        print("CPF inválido.")
    else:
        soma2 = (n1 * 11 + n2 * 10 + n3 * 9 + n4 * 8 + n5 * 7 + n6 * 6 + n7 * 5 + n8 * 4 + n9 * 3 + n10 * 2)

        resto2 = (soma2 * 10) % 11
        if resto2 == 10:
            resto2 = 0

        segundoDigitoCorreto = (resto2 == n11)

        if not segundoDigitoCorreto:
            print("CPF inválido.")
        else:
            print("CPF válido.")
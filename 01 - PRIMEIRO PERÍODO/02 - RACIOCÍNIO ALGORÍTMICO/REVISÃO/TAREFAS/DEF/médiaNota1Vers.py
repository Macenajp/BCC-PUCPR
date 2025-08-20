def somaTotal(nota1, nota2, nota3):
    return nota1 + nota2 + nota3

nota1 = float(input('Insira sua primeira nota: '))
nota2 = float(input('Insira sua segunda nota: '))
nota3 = float(input('Insira sua terceira nota: '))

soma = somaTotal(nota1, nota2, nota3)
mediaGeral = soma / 3

print("A soma total de suas notas é:", nota1 + nota2 + nota3)
print(f"A sua média é de: {mediaGeral:.2f}")

if mediaGeral <= 4:
    print("Com está média, você está REPROVADO!")
elif mediaGeral >= 4 and mediaGeral <= 6.99:
    print("Com está média você terá que fazer RECUPERAÇÃO!")
elif mediaGeral >= 7 and mediaGeral <= 10:
    print("Parabéns. Com essa média você está APROVADO!")
else:
    print("Insira valores adequados!")

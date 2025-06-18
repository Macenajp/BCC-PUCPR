def soma_total(nota1, nota2, nota3):
    return nota1 + nota2 + nota3

def divisao_soma(soma):
    return soma / 3

def resultado_media(media):
    if media <= 4:
        print("Com essa média, você está REPROVADO!")
    elif 4 < media <= 6.99:
        print("Com essa média, você terá que fazer RECUPERAÇÃO!")
    elif 7 <= media <= 10:
        print("Parabéns! Com essa média, você está APROVADO!")
    else:
        print("Insira valores adequados!")

def main():
    try:
        nota1 = float(input('Insira sua primeira nota: '))
        nota2 = float(input('Insira sua segunda nota: '))
        nota3 = float(input('Insira sua terceira nota: '))

        if not (0 <= nota1 <= 10 and 0 <= nota2 <= 10 and 0 <= nota3 <= 10):
            print("As notas devem estar entre 0 e 10.")
            return

        soma = soma_total(nota1, nota2, nota3)
        media = divisao_soma(soma)

        print(f"\nA soma total de suas notas é: {soma}")
        print(f"Sua média é: {media:.2f}\n")

        resultado_media(media)

    except ValueError:
        print("Insira apenas números válidos.")
main()

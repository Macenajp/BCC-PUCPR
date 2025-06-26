# Bibliotecas que usei:
import random               # Vai ser usado para fazer as escolhas aleatórias para cada questão
from time import sleep      # Só por motivos estéticos

def jogo():
    acertos = 0

    for rodada in range(1, 6):
        sleep(0.8)
        print(f"\nRodada: {rodada}")

        P = random.choice([True, False])
        Q = random.choice([True, False])

        conectivos = ["and", "or", "not P", "not Q", "P -> Q", "P <-> Q"]
        operação = random.choice(conectivos)

        if operação == "and":
            resultado = P and Q
            expressãoLógica = f"{P} and {Q}"

        elif operação == "or":
            resultado = P or Q
            expressãoLógica = f"{P} or {Q}"

        elif operação == "not P":
            resultado = not P
            expressãoLógica = f"not {P}"

        elif operação == "not Q":
            resultado = not Q
            expressãoLógica = f"not {Q}"

        elif operação == "P -> Q":
            resultado = (not P) or Q
            expressãoLógica = f"{P} -> {Q}"

        elif operação == "P <-> Q":
            resultado = P == Q
            expressãoLógica = f"{P} <-> {Q}"

        while True:
            print("Analise a seguinte expressão e responda:")
            print(f"Expressão: {expressãoLógica}")
            respostaUsuário = input("Resposta (v / f): ")
            respostaCorreta = "v" if resultado else "f"

            if respostaUsuário not in ["v", "f"]:
                print("\n-> Tente novamente e digite apenas 'v' ou 'f'.")
                continue

            if respostaUsuário == respostaCorreta:
                print("Você acertou!")
                acertos += 1
            else:
                print("Você errou!")
            break

    print(f"\nO jogo acabou. Das cinco questões, você acertou: {acertos}.")
jogo()

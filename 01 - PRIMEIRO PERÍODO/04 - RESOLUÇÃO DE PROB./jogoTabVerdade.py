import random
from time import sleep

def jogo():
    acertos = 0

    for rodada in range(1, 6):
        sleep(0.8)
        print(f"\n========================================================== \nRodada: {rodada}")

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
            print("Analise a seguinte expressão e responda (use 'v' ou 'f'):")
            print(f"Expressão: {expressãoLógica}")
            respostaUsuário = input("Resposta: ")
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

    print(f"\n=========================================================="
          f"\n         O jogo acabou. Sua pontuação foi: {acertos}/5."
          f"\n==========================================================")
jogo()

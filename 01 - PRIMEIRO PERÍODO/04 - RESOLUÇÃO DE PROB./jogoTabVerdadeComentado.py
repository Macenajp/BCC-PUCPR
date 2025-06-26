# Bibliotecas que usei:
import random               # O uso do "random" é o que vai fazer o jogo funcionar como deve, visto que ele que vai escolher aleatoriamente como vão ser as expressões.
from time import sleep      # Usado mais por estética, ele vai gerar um "delay" antes de iniciar cada rodada, deixando o jogo mais fluido.


# Corpo do código:
def jogo():
    acertos = 0                         # Pontuação inicial que o usuário vai ter quando começar o jogo.

    for rodada in range(1, 6):          # Coloquei esse "1, 6" para a variável "rodada" não começar automaticamente em "0". Fazendo ela iniciar em 1 até 5 e não 0 até 4
        sleep(0.8)                      # Esse é o "delay".
        print(f"\n========================================================== \nRodada: {rodada}")

        # Uso da bibliotaca "random". Vai gerar um valor aleatório para as seguintes variáveis, sendo elas verdadeiras ou não:
        P = random.choice([True, False])
        Q = random.choice([True, False])

        # Criei uma lista para deixar todos os conectivos das expressões já salvas.
        conectivos = ["and", "or", "not P", "not Q", "P -> Q", "P <-> Q"]
        operação = random.choice(conectivos)

        # Vai montar a expressão e calcular o resultado correto se baseando na variável "operação".
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

        # O que o usuário vai ver e usar:
        while True:                                                              # O loop vai validadar a entrada ('v' ou 'f')
            print("Analise a seguinte expressão e responda (use 'v' ou 'f'):")
            print(f"Expressão: {expressãoLógica}")
            respostaUsuário = input("Resposta: ")
            respostaCorreta = "v" if resultado else "f"

            # Se a resposta do usuário for qualquer uma diferente das escolhidas ('v' e 'f'), vai retornar a questão e informar o seguinte:
            if respostaUsuário not in ["v", "f"]:
                print("\n-> Tente novamente e digite apenas 'v' ou 'f'.")       # Quando aparecer essa mensagem, logo em seguida vai aparecer "Analise a seguinte...".
                continue

            if respostaUsuário == respostaCorreta:
                print("Você acertou!")
                acertos += 1                                                    # Vai somar mais um ponto na pontuação se a resposta estiver correta.
            else:
                print("Você errou!")
            break                                                               # Encerra o loop caso o usuário use um dos caracteres válidos.

    print(f"\n=========================================================="
          f"\n         O jogo acabou. Sua pontuação foi: {acertos}/5."
          f"\n==========================================================")
jogo()

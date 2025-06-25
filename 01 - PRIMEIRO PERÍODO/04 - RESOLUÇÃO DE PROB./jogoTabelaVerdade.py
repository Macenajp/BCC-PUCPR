# Bibliotecas que usei:
import random               # Vai ser usado para fazer as escolhas aleatórias para cada questão
from time import sleep      # Só por motivos estéticos


# Variáveis e desenvolvimento geral:
acertos = 0

for rodada in range(5):
    pass


P = random.choice([True, False])
Q = random.choice([True, False])

operaçõesLógicas = ["and", "or", "not P", "not Q"]
operação = random.choice(operaçõesLógicas)

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


massaInicial = float(input("Digite a massa inicial do material (em gramas): "))

massaAtual = massaInicial
tempoTotal = 0

while massaAtual >= 0.5:
    massaAtual = massaAtual / 2

    tempoTotal = tempoTotal + 50

print("Resultado:\n")
print(f"Massa final: {massaAtual:.4f} gramas")
print(f"Tempo total: {tempoTotal} segundos")

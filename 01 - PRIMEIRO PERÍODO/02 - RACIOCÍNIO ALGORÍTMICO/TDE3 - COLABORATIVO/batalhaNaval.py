import random
import os
import time
from colorama import Fore, Style, init

init(autoreset=True)

TAMANHO = 8
NAVIOS = [2, 3, 3, 4]  # tamanhos dos navios

def criar_tabuleiro():
    return [['~' for _ in range(TAMANHO)] for _ in range(TAMANHO)]


def mostrar_tabuleiro(tabuleiro, ocultar=False):
    print("   " + " ".join(str(i) for i in range(TAMANHO)))
    for i, linha in enumerate(tabuleiro):
        print(f"{i} |", end=" ")
        for cel in linha:
            if ocultar and cel == 'N':
                print('~', end=" ")
            elif cel == 'X':
                print(Fore.RED + 'X' + Style.RESET_ALL, end=" ")
            elif cel == 'O':
                print(Fore.CYAN + 'O' + Style.RESET_ALL, end=" ")
            else:
                print(cel, end=" ")
        print()
    print()


def posicionar_navio(tabuleiro, tamanho_navio):
    while True:
        orientacao = random.choice(['H', 'V'])
        x = random.randint(0, TAMANHO - 1)
        y = random.randint(0, TAMANHO - 1)

        if orientacao == 'H' and y + tamanho_navio <= TAMANHO:
            if all(tabuleiro[x][y+i] == '~' for i in range(tamanho_navio)):
                for i in range(tamanho_navio):
                    tabuleiro[x][y+i] = 'N'
                break
        elif orientacao == 'V' and x + tamanho_navio <= TAMANHO:
            if all(tabuleiro[x+i][y] == '~' for i in range(tamanho_navio)):
                for i in range(tamanho_navio):
                    tabuleiro[x+i][y] = 'N'
                break


def atacar(tabuleiro, x, y):
    if tabuleiro[x][y] == 'N':
        tabuleiro[x][y] = 'X'
        print(Fore.RED + "🎯 Acertou um navio!" + Style.RESET_ALL)
        return True
    elif tabuleiro[x][y] == '~':
        tabuleiro[x][y] = 'O'
        print(Fore.CYAN + "💦 Água!" + Style.RESET_ALL)
        return False
    else:
        print("⚠️  Já tentou aqui!")
        return None


def fim_de_jogo(tabuleiro):
    for linha in tabuleiro:
        if 'N' in linha:
            return False
    return True


#  Montagem de jogo
tab_jogador = criar_tabuleiro()
tab_computador = criar_tabuleiro()

for tamanho in NAVIOS:
    posicionar_navio(tab_jogador, tamanho)
    posicionar_navio(tab_computador, tamanho)

# Loop Principal
while True:
    os.system('cls' if os.name == 'nt' else 'clear')

    print("--- BATALHA NAVAL ---\n")
    print("Seus Navios 🚢:")
    mostrar_tabuleiro(tab_jogador)
    print("Navios Inimigos 🚢:")
    mostrar_tabuleiro(tab_computador, ocultar=True)

    # Ataque do jogador
    try:
        x = int(input("Linha (0-7): "))
        y = int(input("Coluna (0-7): "))
        if x < 0 or y < 0 or x >= TAMANHO or y >= TAMANHO:
            print("Posição inválida!")
            time.sleep(1)
            continue
    except ValueError:
        print("Digite números válidos!")
        time.sleep(1)
        continue

    if atacar(tab_computador, x, y) is None:
        time.sleep(1)
        continue

    if fim_de_jogo(tab_computador):
        print(Fore.GREEN + "\n🏆 Você venceu! Todos os navios inimigos foram destruídos!" + Style.RESET_ALL)
        break

    # Ataque do computador
    print("\nVez do computador...")
    time.sleep(1)
    while True:
        cx = random.randint(0, TAMANHO - 1)
        cy = random.randint(0, TAMANHO - 1)
        if tab_jogador[cx][cy] not in ['X', 'O']:
            acertou = atacar(tab_jogador, cx, cy)
            break

    if fim_de_jogo(tab_jogador):
        print(Fore.RED + "\n💀 Você perdeu! O inimigo afundou todos os seus navios." + Style.RESET_ALL)
        break

    input("\nPressione ENTER para continuar...")

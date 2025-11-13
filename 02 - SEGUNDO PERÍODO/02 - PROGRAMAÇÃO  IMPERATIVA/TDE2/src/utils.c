#include "utils.h"
#include <string.h>
#include <ctype.h>

// ============================================================
// Módulo: utils.c
// Este módulo contém funções utilitárias genéricas utilizadas
// em várias partes do programa, especialmente para manipulação
// de strings lidas de arquivos ou entrada do usuário.
// ============================================================

// ------------------------------------------------------------
// Função: trim_newline
// Remove o caractere '\n' (nova linha) do final de uma string,
// normalmente inserido pela função fgets().
// Parâmetros:
//   - str: ponteiro para a string a ser modificada.
// Observações:
//   - A função verifica se o último caractere é '\n' e o substitui por '\0'.
//   - Evita problemas ao comparar strings lidas do teclado/arquivo.
// ------------------------------------------------------------
void trim_newline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

// ------------------------------------------------------------
// Função: str_to_upper
// Converte todos os caracteres de uma string para letras maiúsculas.
// Parâmetros:
//   - str: ponteiro para a string que será convertida.
// Observações:
//   - Usa a função toupper() da biblioteca <ctype.h>.
//   - Cada caractere é convertido individualmente.
// ------------------------------------------------------------
void str_to_upper(char* str) {
    for (int i = 0; str[i]; i++)
        str[i] = toupper((unsigned char) str[i]);
}

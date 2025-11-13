#ifndef UTILS_H
#define UTILS_H

// ---------------------------------------------------------------------------
// Função: trim_newline
// ---------------------------------------------------------------------------
// Descrição:
//  Remove o caractere '\n' (nova linha) que pode ser inserido por funções como
//  fgets() no final de uma string. Essa limpeza é útil antes de comparar ou
//  manipular textos lidos de arquivos ou entrada do usuário.
//
// Parâmetros:
//  - str: ponteiro para a string que será modificada.
//
// Retorno:
//  Nenhum. A string é alterada diretamente.
// ---------------------------------------------------------------------------
void trim_newline(char* str);

// ---------------------------------------------------------------------------
// Função: str_to_upper
// ---------------------------------------------------------------------------
// Descrição:
//  Converte todos os caracteres de uma string para letras maiúsculas.
//  Ideal para padronizar comparações entre textos.
//
// Parâmetros:
//  - str: ponteiro para a string que será convertida.
//
// Retorno:
//  Nenhum. A string é modificada diretamente.
// ---------------------------------------------------------------------------
void str_to_upper(char* str);

#endif

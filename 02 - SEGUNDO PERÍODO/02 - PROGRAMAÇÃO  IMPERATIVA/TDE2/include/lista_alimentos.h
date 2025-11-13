#ifndef LISTA_ALIMENTOS_H
#define LISTA_ALIMENTOS_H

#include "alimento.h"  // Inclui a definição da estrutura Alimento

// ---------------------------------------------------------------------------
// Estrutura: NoAlimento
// ---------------------------------------------------------------------------
// Descrição:
//  Representa um nó da lista encadeada de alimentos.
//  Cada nó contém um alimento (estrutura Alimento) e um ponteiro para o próximo nó.
//
// Campos:
//  - alimento: estrutura com os dados do alimento (número, descrição, energia etc.)
//  - prox: ponteiro para o próximo nó da lista
// ---------------------------------------------------------------------------
typedef struct NoAlimento {
    Alimento alimento;
    struct NoAlimento* prox;
} NoAlimento;

// ---------------------------------------------------------------------------
// Função: inserir_alimento_ordenado
// ---------------------------------------------------------------------------
// Descrição:
//  Insere um novo alimento na lista encadeada em ordem alfabética ou numérica,
//  de acordo com a lógica implementada na função. Retorna o ponteiro para o nó
//  recém-inserido.
//
// Parâmetros:
//  - lista: ponteiro para o ponteiro do primeiro nó da lista
//  - alimento: estrutura Alimento a ser inserida
//
// Retorno:
//  Ponteiro para o nó do alimento inserido
// ---------------------------------------------------------------------------
NoAlimento* inserir_alimento_ordenado(NoAlimento** lista, Alimento alimento);

// ---------------------------------------------------------------------------
// Função: remover_alimento
// ---------------------------------------------------------------------------
// Descrição:
//  Remove da lista o alimento cuja descrição (nome) corresponde ao texto informado.
//
// Parâmetros:
//  - lista: ponteiro para o ponteiro do primeiro nó da lista
//  - descricao: nome do alimento a ser removido
// ---------------------------------------------------------------------------
void remover_alimento(NoAlimento** lista, const char* descricao);

// ---------------------------------------------------------------------------
// Função: imprimir_lista_alimentos
// ---------------------------------------------------------------------------
// Descrição:
//  Percorre a lista encadeada e exibe na tela os dados de todos os alimentos.
//
// Parâmetros:
//  - lista: ponteiro constante para o primeiro nó da lista
// ---------------------------------------------------------------------------
void imprimir_lista_alimentos(const NoAlimento* lista);

// ---------------------------------------------------------------------------
// Função: liberar_lista_alimentos
// ---------------------------------------------------------------------------
// Descrição:
//  Libera toda a memória alocada pela lista encadeada de alimentos,
//  desalocando nó por nó até que toda a lista seja apagada.
//
// Parâmetros:
//  - lista: ponteiro para o ponteiro do primeiro nó da lista
// ---------------------------------------------------------------------------
void liberar_lista_alimentos(NoAlimento** lista);

#endif

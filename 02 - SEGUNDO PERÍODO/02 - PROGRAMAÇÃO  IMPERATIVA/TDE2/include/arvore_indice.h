#ifndef ARVORE_INDICE_H
#define ARVORE_INDICE_H

#include "alimento.h" // Inclui a definição da estrutura Alimento

// ---------------------------------------------------------------------------
// Estrutura: ArvoreIndice
// ---------------------------------------------------------------------------
// Representa um nó de uma árvore binária de busca usada para indexar alimentos
// com base em um valor numérico (como energia ou proteína).
// Cada nó armazena:
//  - chave: valor numérico usado para indexação (ex: energia ou proteína)
//  - ponteiro para um Alimento
//  - ponteiros para os nós da subárvore esquerda e direita
// ---------------------------------------------------------------------------
typedef struct ArvoreIndice {
    double chave;            // Valor usado como chave de ordenação (energia ou proteína)
    Alimento* alimento;      // Ponteiro para o alimento associado a esta chave
    struct ArvoreIndice* esquerda; // Ponteiro para o nó à esquerda (valores menores)
    struct ArvoreIndice* direita;  // Ponteiro para o nó à direita (valores maiores)
} ArvoreIndice;

// ---------------------------------------------------------------------------
// Função: inserir_no_arvore
// ---------------------------------------------------------------------------
// Insere um novo nó na árvore de índice, de forma ordenada pela chave.
// Parâmetros:
//  - raiz: ponteiro para o ponteiro da raiz da árvore
//  - chave: valor numérico (energia/proteína) que define a posição na árvore
//  - alimento: ponteiro para o alimento a ser associado ao nó
// ---------------------------------------------------------------------------
void inserir_no_arvore(ArvoreIndice** raiz, double chave, Alimento* alimento);

// ---------------------------------------------------------------------------
// Função: imprimir_decrescente
// ---------------------------------------------------------------------------
// Percorre a árvore em ordem decrescente (direita → raiz → esquerda),
// exibindo as informações dos alimentos.
// Parâmetros:
//  - raiz: ponteiro para o nó raiz da árvore
// ---------------------------------------------------------------------------
void imprimir_decrescente(ArvoreIndice* raiz);

// ---------------------------------------------------------------------------
// Função: listar_intervalo
// ---------------------------------------------------------------------------
// Percorre a árvore e lista apenas os alimentos cuja chave está
// dentro do intervalo [min, max].
// Parâmetros:
//  - raiz: nó raiz da árvore
//  - min: valor mínimo do intervalo
//  - max: valor máximo do intervalo
// ---------------------------------------------------------------------------
void listar_intervalo(ArvoreIndice* raiz, double min, double max);

// ---------------------------------------------------------------------------
// Função: liberar_arvore
// ---------------------------------------------------------------------------
// Libera toda a memória alocada pela árvore de índice.
// Recebe ponteiro duplo para permitir que o ponteiro raiz seja definido como NULL.
// Parâmetros:
//  - raiz: ponteiro para o ponteiro da raiz da árvore
// ---------------------------------------------------------------------------
void liberar_arvore(ArvoreIndice** raiz);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "arvore_indice.h"
#include "alimento.h"

// ---------------------------------------------------------------------------
// Função: inserir_no_arvore
// ---------------------------------------------------------------------------
// Descrição:
//  Insere um novo nó na árvore binária de índices de alimentos,
//  usando o valor da chave (energia ou proteína) como critério.
//
// Parâmetros:
//  - raiz: ponteiro duplo para o nó raiz da árvore.
//  - chave: valor de energia ou proteína usado como índice.
//  - alimento: ponteiro para o alimento associado a essa chave.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - Se a árvore estiver vazia, o nó é criado como raiz.
//  - Chaves iguais são inseridas sempre à direita (mantendo consistência).
//  - A função é recursiva.
//  - Em caso de falha na alocação de memória, o programa é encerrado.
// ---------------------------------------------------------------------------
void inserir_no_arvore(ArvoreIndice** raiz, double chave, Alimento* alimento) {
    if (raiz == NULL) return;

    // Caso base: posição onde o novo nó será inserido
    if (*raiz == NULL) {
        *raiz = (ArvoreIndice*)malloc(sizeof(ArvoreIndice));
        if (*raiz == NULL) {
            printf("Erro: falha ao alocar nó da árvore.\n");
            exit(1);
        }
        (*raiz)->chave = chave;
        (*raiz)->alimento = alimento;
        (*raiz)->esquerda = (*raiz)->direita = NULL;
        return;
    }

    // Inserção recursiva: esquerda ou direita conforme o valor da chave
    if (chave < (*raiz)->chave)
        inserir_no_arvore(&(*raiz)->esquerda, chave, alimento);
    else
        inserir_no_arvore(&(*raiz)->direita, chave, alimento);
}

// ---------------------------------------------------------------------------
// Função: imprimir_decrescente
// ---------------------------------------------------------------------------
// Descrição:
//  Percorre e imprime todos os nós da árvore em ordem decrescente
//  de acordo com a chave (energia ou proteína).
//
// Parâmetros:
//  - raiz: ponteiro para o nó raiz da árvore.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - A ordem decrescente é obtida percorrendo: direita → nó → esquerda.
//  - Caso o alimento do nó seja nulo, ele é ignorado.
// ---------------------------------------------------------------------------
void imprimir_decrescente(ArvoreIndice* raiz) {
    if (raiz == NULL) return;

    imprimir_decrescente(raiz->direita);  // Primeiro os maiores valores

    if (raiz->alimento)                   // Exibe o alimento do nó atual
        imprimir_alimento(raiz->alimento);

    imprimir_decrescente(raiz->esquerda); // Depois os menores valores
}

// ---------------------------------------------------------------------------
// Função: listar_intervalo
// ---------------------------------------------------------------------------
// Descrição:
//  Imprime os alimentos cuja chave está dentro do intervalo [min, max].
//
// Parâmetros:
//  - raiz: ponteiro para a raiz da árvore.
//  - min: limite inferior do intervalo.
//  - max: limite superior do intervalo.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - A função utiliza busca recursiva para otimizar o percurso,
//    evitando percorrer ramos desnecessários.
// ---------------------------------------------------------------------------
void listar_intervalo(ArvoreIndice* raiz, double min, double max) {
    if (raiz == NULL) return;

    // Se há possibilidade de encontrar valores maiores que 'min' à esquerda
    if (raiz->chave > min)
        listar_intervalo(raiz->esquerda, min, max);

    // Se o valor do nó está dentro do intervalo, imprime
    if (raiz->chave >= min && raiz->chave <= max && raiz->alimento)
        imprimir_alimento(raiz->alimento);

    // Se há possibilidade de encontrar valores menores que 'max' à direita
    if (raiz->chave < max)
        listar_intervalo(raiz->direita, min, max);
}

// ---------------------------------------------------------------------------
// Função: liberar_arvore
// ---------------------------------------------------------------------------
// Descrição:
//  Libera toda a memória alocada pela árvore binária.
//
// Parâmetros:
//  - raiz: ponteiro duplo para a raiz da árvore.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - A função é recursiva.
//  - Após liberar, o ponteiro da raiz é setado para NULL no chamador,
//    garantindo que não fique um ponteiro “pendurado” (dangling pointer).
// ---------------------------------------------------------------------------
void liberar_arvore(ArvoreIndice** raiz) {
    if (raiz == NULL || *raiz == NULL) return;

    liberar_arvore(&(*raiz)->esquerda);
    liberar_arvore(&(*raiz)->direita);

    free(*raiz);
    *raiz = NULL;
}

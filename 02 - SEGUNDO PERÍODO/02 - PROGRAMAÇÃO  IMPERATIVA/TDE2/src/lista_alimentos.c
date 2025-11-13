#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_alimentos.h"

//
// Função: inserir_alimento_ordenado
// -------------------------------------------------------------
// Descrição:
//  Insere um novo alimento em uma lista encadeada de forma ordenada
//  alfabeticamente pelo campo "descricao".
//
// Parâmetros:
//  - lista: ponteiro duplo para o início da lista encadeada.
//  - alimento: estrutura do tipo Alimento a ser inserida.
//
// Retorno:
//  Retorna o ponteiro para o nó recém-inserido.
//
// Observações:
//  Caso a lista esteja vazia ou o alimento deva ser inserido no início,
//  o novo nó se torna a nova cabeça da lista.
//
NoAlimento* inserir_alimento_ordenado(NoAlimento** lista, Alimento alimento) {
    // Aloca memória para o novo nó
    NoAlimento* novo = (NoAlimento*)malloc(sizeof(NoAlimento));
    if (!novo) {
        printf("Erro: falha ao alocar nó de alimento.\n");
        exit(1);
    }

    // Copia os dados do alimento para o nó
    novo->alimento = alimento;
    novo->prox = NULL;

    // Caso a lista esteja vazia ou o novo alimento venha antes do primeiro
    if (*lista == NULL || strcmp(alimento.descricao, (*lista)->alimento.descricao) < 0) {
        novo->prox = *lista;  // novo aponta para o antigo primeiro
        *lista = novo;        // atualiza o início da lista
        return novo;
    }

    // Percorre a lista até encontrar a posição correta de inserção
    NoAlimento* atual = *lista;
    while (atual->prox != NULL && strcmp(alimento.descricao, atual->prox->alimento.descricao) > 0) {
        atual = atual->prox;
    }

    // Insere o novo nó entre "atual" e "atual->prox"
    novo->prox = atual->prox;
    atual->prox = novo;

    return novo;
}

//
// Função: remover_alimento
// -------------------------------------------------------------
// Descrição:
//  Remove um alimento da lista encadeada com base na sua descrição.
//
// Parâmetros:
//  - lista: ponteiro duplo para o início da lista.
//  - descricao: string com a descrição do alimento a ser removido.
//
// Observações:
//  Caso o alimento não exista, nenhuma modificação é feita.
//
void remover_alimento(NoAlimento** lista, const char* descricao) {
    if (lista == NULL || *lista == NULL) return;

    NoAlimento* atual = *lista;
    NoAlimento* anterior = NULL;

    // Percorre até encontrar o alimento correspondente
    while (atual != NULL && strcmp(atual->alimento.descricao, descricao) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // Caso o alimento não tenha sido encontrado, sai da função
    if (atual == NULL) {
        return;
    }

    // Remove o nó do início ou do meio/fim
    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    // Libera a memória do nó removido
    free(atual);
}

//
// Função: imprimir_lista_alimentos
// -------------------------------------------------------------
// Descrição:
//  Percorre e imprime todos os alimentos da lista encadeada,
//  utilizando a função auxiliar imprimir_alimento().
//
// Parâmetros:
//  - lista: ponteiro constante para o início da lista.
//
void imprimir_lista_alimentos(const NoAlimento* lista) {
    const NoAlimento* atual = lista;
    while (atual != NULL) {
        imprimir_alimento(&atual->alimento); // imprime dados do alimento
        atual = atual->prox;                 // avança para o próximo
    }
}

//
// Função: liberar_lista_alimentos
// -------------------------------------------------------------
// Descrição:
//  Libera toda a memória alocada pela lista encadeada,
//  desalocando cada nó da estrutura.
//
// Parâmetros:
//  - lista: ponteiro duplo para o início da lista.
//
void liberar_lista_alimentos(NoAlimento** lista) {
    NoAlimento* atual = *lista;
    while (atual != NULL) {
        NoAlimento* temp = atual; // guarda o nó atual
        atual = atual->prox;      // avança para o próximo
        free(temp);               // libera o nó atual
    }

    // Após liberar todos, define o ponteiro inicial como NULL
    *lista = NULL;
}

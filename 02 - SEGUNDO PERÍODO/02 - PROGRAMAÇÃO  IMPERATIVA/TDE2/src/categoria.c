#include <stdio.h>
#include <stdlib.h>
#include "categoria.h"

// ---------------------------------------------------------------------------
// Função: inserir_categoria_ordenada
// ---------------------------------------------------------------------------
// Descrição:
//  Insere uma nova categoria na lista encadeada de categorias,
//  mantendo a ordem crescente conforme o valor do enum (CategoriaEnum).
//
// Parâmetros:
//  - lista: ponteiro duplo para o início da lista de categorias.
//  - tipo: tipo de categoria (valor do enum CategoriaEnum) a ser inserido.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - Caso a lista esteja vazia ou o tipo seja menor que o primeiro, 
//    a categoria é inserida no início.
//  - Cada categoria inicializa suas listas e árvores vazias.
//  - Em caso de erro de alocação, o programa é encerrado.
// ---------------------------------------------------------------------------
void inserir_categoria_ordenada(Categoria** lista, CategoriaEnum tipo) {
    Categoria* nova = (Categoria*)malloc(sizeof(Categoria));
    if (nova == NULL) {
        printf("Erro ao alocar memória para categoria.\n");
        exit(1);
    }

    // Inicialização dos campos da nova categoria
    nova->tipo = tipo;
    nova->alimentos = NULL;
    nova->arvoreEnergia = NULL;
    nova->arvoreProteina = NULL;
    nova->prox = NULL;

    // Inserção no início ou entre elementos, mantendo a ordem
    if (*lista == NULL || tipo < (*lista)->tipo) {
        nova->prox = *lista;
        *lista = nova;
        return;
    }

    // Percorre até encontrar a posição correta
    Categoria* atual = *lista;
    while (atual->prox != NULL && atual->prox->tipo < tipo) {
        atual = atual->prox;
    }

    // Insere a nova categoria entre dois nós
    nova->prox = atual->prox;
    atual->prox = nova;
}

// ---------------------------------------------------------------------------
// Função: buscar_categoria
// ---------------------------------------------------------------------------
// Descrição:
//  Procura uma categoria na lista encadeada com base no tipo (enum).
//
// Parâmetros:
//  - lista: ponteiro para o início da lista de categorias.
//  - tipo: valor do enum CategoriaEnum a ser buscado.
//
// Retorno:
//  - Ponteiro para a categoria correspondente, se encontrada.
//  - NULL, caso contrário.
// ---------------------------------------------------------------------------
Categoria* buscar_categoria(Categoria* lista, CategoriaEnum tipo) {
    Categoria* atual = lista;
    while (atual != NULL) {
        if (atual->tipo == tipo)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

// ---------------------------------------------------------------------------
// Função: remover_categoria
// ---------------------------------------------------------------------------
// Descrição:
//  Remove uma categoria específica da lista encadeada,
//  liberando toda a memória associada a ela (lista de alimentos e árvores).
//
// Parâmetros:
//  - lista: ponteiro duplo para a lista de categorias.
//  - tipo: valor do enum CategoriaEnum da categoria a remover.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - Caso a categoria não exista, nada é feito.
//  - Libera recursivamente todos os elementos associados.
// ---------------------------------------------------------------------------
void remover_categoria(Categoria** lista, CategoriaEnum tipo) {
    if (*lista == NULL) return;

    Categoria* atual = *lista;
    Categoria* anterior = NULL;

    // Busca pela categoria desejada
    while (atual != NULL && atual->tipo != tipo) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se não encontrada, encerra
    if (atual == NULL) return;

    // Ajusta o encadeamento da lista
    if (anterior == NULL)
        *lista = atual->prox;
    else
        anterior->prox = atual->prox;

    // Libera todos os recursos associados à categoria
    liberar_lista_alimentos(&atual->alimentos);
    liberar_arvore(&atual->arvoreEnergia);
    liberar_arvore(&atual->arvoreProteina);
    free(atual);
}

// ---------------------------------------------------------------------------
// Função: imprimir_categorias
// ---------------------------------------------------------------------------
// Descrição:
//  Percorre e imprime o nome de todas as categorias da lista.
//
// Parâmetros:
//  - lista: ponteiro para o início da lista de categorias.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - Utiliza a função 'obter_nome_categoria' para converter o enum em texto.
// ---------------------------------------------------------------------------
void imprimir_categorias(Categoria* lista) {
    Categoria* atual = lista;
    while (atual != NULL) {
        printf("%s\n", obter_nome_categoria(atual->tipo));
        atual = atual->prox;
    }
}

// ---------------------------------------------------------------------------
// Função: liberar_categorias
// ---------------------------------------------------------------------------
// Descrição:
//  Libera toda a memória alocada para a lista de categorias e seus dados.
//
// Parâmetros:
//  - lista: ponteiro duplo para o início da lista de categorias.
//
// Retorno:
//  Nenhum (void).
//
// Observações:
//  - Chama as funções de liberação das listas de alimentos e árvores.
//  - Após a execução, o ponteiro da lista é setado para NULL.
// ---------------------------------------------------------------------------
void liberar_categorias(Categoria** lista) {
    Categoria* atual = *lista;

    while (atual != NULL) {
        Categoria* temp = atual;

        liberar_lista_alimentos(&temp->alimentos);
        liberar_arvore(&temp->arvoreEnergia);
        liberar_arvore(&temp->arvoreProteina);

        atual = atual->prox;
        free(temp);
    }

    *lista = NULL;
}

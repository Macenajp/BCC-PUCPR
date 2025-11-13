#ifndef CATEGORIA_H
#define CATEGORIA_H

#include "lista_alimentos.h"  // Define a lista encadeada de alimentos
#include "arvore_indice.h"    // Define as árvores de índice (por energia e proteína)
#include "tipos_enum.h"       // Define o enum CategoriaEnum com os tipos de categoria

// ---------------------------------------------------------------------------
// Estrutura: Categoria
// ---------------------------------------------------------------------------
// Representa uma categoria de alimentos (ex: CARNES, FRUTAS, LATICÍNIOS, etc).
// Cada categoria mantém:
//  - tipo: enum identificando o nome da categoria
//  - alimentos: lista encadeada contendo os alimentos pertencentes a essa categoria
//  - arvoreEnergia: árvore binária de busca ordenada pelo valor de energia dos alimentos
//  - arvoreProteina: árvore binária de busca ordenada pelo valor de proteína
//  - prox: ponteiro para a próxima categoria na lista de categorias
// ---------------------------------------------------------------------------
typedef struct Categoria {
    CategoriaEnum tipo;             // Tipo da categoria (enum)
    NoAlimento* alimentos;          // Lista encadeada de alimentos desta categoria
    ArvoreIndice* arvoreEnergia;    // Árvore de índice ordenada pela energia
    ArvoreIndice* arvoreProteina;   // Árvore de índice ordenada pela proteína
    struct Categoria* prox;         // Ponteiro para a próxima categoria na lista
} Categoria;

// ---------------------------------------------------------------------------
// Função: inserir_categoria_ordenada
// ---------------------------------------------------------------------------
// Insere uma nova categoria na lista de categorias de forma ordenada
// (normalmente em ordem alfabética pelo tipo de categoria).
// Parâmetros:
//  - lista: ponteiro para o ponteiro da lista de categorias
//  - tipo: tipo da categoria (enum) a ser inserida
// ---------------------------------------------------------------------------
void inserir_categoria_ordenada(Categoria** lista, CategoriaEnum tipo);

// ---------------------------------------------------------------------------
// Função: buscar_categoria
// ---------------------------------------------------------------------------
// Busca uma categoria específica na lista pelo tipo informado.
// Parâmetros:
//  - lista: ponteiro para a primeira categoria
//  - tipo: tipo da categoria a ser encontrada
// Retorno:
//  - ponteiro para a categoria encontrada, ou NULL se não existir
// ---------------------------------------------------------------------------
Categoria* buscar_categoria(Categoria* lista, CategoriaEnum tipo);

// ---------------------------------------------------------------------------
// Função: remover_categoria
// ---------------------------------------------------------------------------
// Remove uma categoria inteira da lista, liberando todos os alimentos e árvores
// associadas a ela.
// Parâmetros:
//  - lista: ponteiro para o ponteiro da lista de categorias
//  - tipo: tipo da categoria a ser removida
// ---------------------------------------------------------------------------
void remover_categoria(Categoria** lista, CategoriaEnum tipo);

// ---------------------------------------------------------------------------
// Função: imprimir_categorias
// ---------------------------------------------------------------------------
// Exibe na tela todas as categorias existentes e suas respectivas informações.
// Parâmetros:
//  - lista: ponteiro para o início da lista de categorias
// ---------------------------------------------------------------------------
void imprimir_categorias(Categoria* lista);

// ---------------------------------------------------------------------------
// Função: liberar_categorias
// ---------------------------------------------------------------------------
// Libera toda a memória alocada para a lista de categorias, incluindo
// listas de alimentos e árvores de índice.
// Parâmetros:
//  - lista: ponteiro para o ponteiro da lista de categorias
// ---------------------------------------------------------------------------
void liberar_categorias(Categoria** lista);

#endif

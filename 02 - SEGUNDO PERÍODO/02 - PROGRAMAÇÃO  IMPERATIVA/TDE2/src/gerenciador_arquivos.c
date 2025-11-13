#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciador_arquivos.h"
#include "tipos_enum.h"
#include "alimento.h"
#include "lista_alimentos.h"
#include "categoria.h"
#include "arvore_indice.h"
#include "utils.h"

// ---------------------------------------------------------------------------
// Função: converter_csv_para_bin
// ---------------------------------------------------------------------------
// Descrição:
//  Lê um arquivo CSV contendo informações de alimentos e grava os dados
//  em um arquivo binário (dados.bin) no formato da estrutura Alimento.
//
// Parâmetros:
//  - nome_csv: nome do arquivo CSV de entrada (ex: "alimentos.csv").
//  - nome_bin: nome do arquivo binário de saída (ex: "dados.bin").
//
// Funcionamento:
//  1. Abre o arquivo CSV para leitura.
//  2. Abre (ou cria) o arquivo binário para escrita binária.
//  3. Ignora a primeira linha (cabeçalho).
//  4. Para cada linha restante, faz o parse dos campos:
//      • número do alimento
//      • descrição
//      • energia (kcal)
//      • proteína (g)
//      • nome da categoria
//  5. Converte o nome da categoria em um valor do enum (CategoriaEnum).
//  6. Escreve cada estrutura Alimento no arquivo binário.
// ---------------------------------------------------------------------------
void converter_csv_para_bin(const char* nome_csv, const char* nome_bin) {
    FILE* fin = fopen(nome_csv, "r");
    if (fin == NULL) {
        printf("Erro: não foi possível abrir o CSV '%s'.\n", nome_csv);
        exit(1);
    }

    FILE* fout = fopen(nome_bin, "wb");
    if (fout == NULL) {
        printf("Erro: não foi possível criar '%s'.\n", nome_bin);
        fclose(fin);
        exit(1);
    }

    char linha[512];
    // Ignora a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), fin) == NULL) {
        printf("CSV vazio.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    // Lê cada linha e converte para estrutura Alimento
    while (fgets(linha, sizeof(linha), fin) != NULL) {
        trim_newline(linha);
        if (strlen(linha) == 0) continue; // pula linhas vazias

        int numero = 0;
        char descricao[128] = {0};
        double energia = 0.0;
        double proteina = 0.0;
        char nomeCategoria[128] = {0};

        // Lê campos separados por vírgula
        int lidos = sscanf(linha, "%d,%127[^,],%lf,%lf,%127[^\n]",
                           &numero, descricao, &energia, &proteina, nomeCategoria);
        if (lidos < 5) continue;

        // Converte categoria de string para enum
        CategoriaEnum cat = obter_enum_categoria(nomeCategoria);

        // Monta a estrutura Alimento
        Alimento a;
        a.numero = numero;
        strncpy(a.descricao, descricao, sizeof(a.descricao) - 1);
        a.energia = energia;
        a.proteina = proteina;
        a.categoria = cat;

        // Escreve no arquivo binário
        fwrite(&a, sizeof(Alimento), 1, fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Arquivo binário '%s' gerado.\n", nome_bin);
}

// ---------------------------------------------------------------------------
// Função: carregar_dados_binarios
// ---------------------------------------------------------------------------
// Descrição:
//  Lê o arquivo binário (dados.bin) e popula a lista de categorias e seus
//  respectivos alimentos em memória.
//
// Parâmetros:
//  - nome_bin: nome do arquivo binário a ser carregado.
//  - listaCategorias: ponteiro duplo para a lista de categorias a preencher.
//
// Funcionamento:
//  1. Abre o arquivo binário para leitura.
//  2. Para cada alimento lido:
//      • Busca a categoria correspondente.
//      • Caso a categoria ainda não exista, cria e insere ordenada.
//      • Insere o alimento na lista encadeada da categoria.
//      • Atualiza as árvores de energia e proteína.
// ---------------------------------------------------------------------------
void carregar_dados_binarios(const char* nome_bin, Categoria** listaCategorias) {
    FILE* f = fopen(nome_bin, "rb");
    if (f == NULL) {
        // O arquivo pode não existir — não é considerado erro fatal.
        return;
    }

    Alimento a;
    // Lê cada alimento do arquivo binário
    while (fread(&a, sizeof(Alimento), 1, f) == 1) {
        // Verifica se a categoria já existe
        Categoria* cat = buscar_categoria(*listaCategorias, a.categoria);
        if (cat == NULL) {
            // Se não existir, cria nova categoria e insere na lista
            inserir_categoria_ordenada(listaCategorias, a.categoria);
            cat = buscar_categoria(*listaCategorias, a.categoria);
        }

        // Insere o alimento na lista da categoria
        NoAlimento* nodo = inserir_alimento_ordenado(&cat->alimentos, a);

        // Insere nas árvores de índice (energia e proteína)
        if (nodo) {
            inserir_no_arvore(&cat->arvoreEnergia, nodo->alimento.energia, &nodo->alimento);
            inserir_no_arvore(&cat->arvoreProteina, nodo->alimento.proteina, &nodo->alimento);
        }
    }

    fclose(f);
}

// ---------------------------------------------------------------------------
// Função: salvar_dados_binarios
// ---------------------------------------------------------------------------
// Descrição:
//  Salva todos os alimentos da lista de categorias no arquivo binário,
//  sobrescrevendo seu conteúdo anterior.
//
// Parâmetros:
//  - nome_bin: nome do arquivo binário de saída (ex: "dados.bin").
//  - listaCategorias: ponteiro para o início da lista de categorias.
//
// Funcionamento:
//  1. Abre o arquivo binário em modo de escrita binária ("wb").
//  2. Percorre todas as categorias e seus alimentos.
//  3. Escreve cada estrutura Alimento no arquivo.
// ---------------------------------------------------------------------------
void salvar_dados_binarios(const char* nome_bin, Categoria* listaCategorias) {
    FILE* f = fopen(nome_bin, "wb");
    if (f == NULL) {
        printf("Erro: não foi possível abrir '%s' para escrita.\n", nome_bin);
        return;
    }

    // Percorre todas as categorias e escreve seus alimentos
    Categoria* c = listaCategorias;
    while (c != NULL) {
        NoAlimento* atual = c->alimentos;
        while (atual != NULL) {
            fwrite(&atual->alimento, sizeof(Alimento), 1, f);
            atual = atual->prox;
        }
        c = c->prox;
    }

    fclose(f);
    printf("Arquivo '%s' salvo.\n", nome_bin);
}

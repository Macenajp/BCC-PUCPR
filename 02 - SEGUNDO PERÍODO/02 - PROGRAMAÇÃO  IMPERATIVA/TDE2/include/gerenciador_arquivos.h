#ifndef GERENCIADOR_ARQUIVOS_H
#define GERENCIADOR_ARQUIVOS_H

#include "lista_alimentos.h"  // Define estruturas e funções para manipulação de listas de alimentos
#include "categoria.h"        // Define estruturas e funções para manipulação de categorias

// ---------------------------------------------------------------------------
// Função: converter_csv_para_bin
// ---------------------------------------------------------------------------
// Descrição:
//  Lê um arquivo de texto no formato CSV (por exemplo, "alimentos.csv") contendo
//  os dados dos alimentos e converte todas as informações para o formato binário,
//  salvando o resultado em um arquivo binário (ex: "dados.bin").
//
// Parâmetros:
//  - nome_csv: nome do arquivo CSV de entrada
//  - nome_bin: nome do arquivo binário de saída
// ---------------------------------------------------------------------------
void converter_csv_para_bin(const char* nome_csv, const char* nome_bin);

// ---------------------------------------------------------------------------
// Função: carregar_dados_binarios
// ---------------------------------------------------------------------------
// Descrição:
//  Lê o arquivo binário (ex: "dados.bin") contendo os alimentos previamente
//  salvos e reconstrói em memória a estrutura completa de categorias e listas
//  encadeadas de alimentos, populando o ponteiro passado por referência.
//
// Parâmetros:
//  - nome_bin: nome do arquivo binário de onde os dados serão lidos
//  - listaCategorias: ponteiro para o ponteiro da lista de categorias que será preenchida
// ---------------------------------------------------------------------------
void carregar_dados_binarios(const char* nome_bin, Categoria** listaCategorias);

// ---------------------------------------------------------------------------
// Função: salvar_dados_binarios
// ---------------------------------------------------------------------------
// Descrição:
//  Percorre todas as categorias e suas respectivas listas de alimentos em memória,
//  salvando os dados novamente em formato binário (ex: "dados.bin").
//  Essa função é usada para atualizar o arquivo após inserções ou remoções.
//
// Parâmetros:
//  - nome_bin: nome do arquivo binário de saída
//  - listaCategorias: ponteiro para a lista de categorias que será salva no arquivo
// ---------------------------------------------------------------------------
void salvar_dados_binarios(const char* nome_bin, Categoria* listaCategorias);

#endif

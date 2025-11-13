#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alimento.h"
#include "categoria.h"
#include "lista_alimentos.h"
#include "gerenciador_arquivos.h"
#include "tipos_enum.h"
#include "utils.h"  // Necessário para trim_newline()

//
// Programa: P2 - Manipulação de Dados Binários de Alimentos
// -----------------------------------------------------------------------------
// Descrição:
//   Este programa lê os dados do arquivo binário "dados.bin" (gerado pelo P1)
//   e oferece um menu interativo para o usuário visualizar, filtrar e remover
//   informações sobre alimentos e categorias.
//
//   Os dados são carregados em estruturas de lista encadeada e árvores binárias,   
//   permitindo consultas rápidas e organizadas por energia e proteína.
//
// Dependências:
//   - P1 deve ter sido executado previamente para gerar "dados.bin".
//   - Todas as estruturas e funções auxiliares (categoria, alimento, etc.).
//
// Autor: (adicione seu nome)
// Disciplina: (adicione o nome da disciplina)
// Data: (adicione a data)
//
// -----------------------------------------------------------------------------
// Funcionalidades do Menu:
//   1. Listar todas as categorias
//   2. Listar alimentos de uma categoria
//   3. Listar alimentos por energia (decrescente)
//   4. Listar alimentos por proteína (decrescente)
//   5. Filtrar alimentos por faixa de energia
//   6. Filtrar alimentos por faixa de proteína
//   7. Remover uma categoria completa
//   8. Remover um alimento específico
//   9. Encerrar o programa
//
// Observações:
//   - Após remoções, as árvores de índice são recriadas automaticamente.
//   - Ao sair, se houver modificações, o arquivo "dados.bin" é atualizado.
//
void menu() {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1. Listar todas as categorias\n");
    printf("2. Listar alimentos de uma categoria\n");
    printf("3. Listar alimentos por energia (decrescente)\n");
    printf("4. Listar alimentos por proteína (decrescente)\n");
    printf("5. Filtrar alimentos por faixa de energia\n");
    printf("6. Filtrar alimentos por faixa de proteína\n");
    printf("7. Remover categoria\n");
    printf("8. Remover alimento\n");
    printf("9. Encerrar programa\n");
    printf("===========================\n");
}

int main() {
    Categoria* listaCategorias = NULL;

    // Carrega todos os dados do arquivo binário gerado pelo P1
    carregar_dados_binarios("dados.bin", &listaCategorias);

    int opcao;
    int modificou = 0; // Flag usada para saber se houve alterações

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // consome '\n' pendente do buffer

        // --- Opção 1: listar categorias ---
        if (opcao == 1) {
            imprimir_categorias(listaCategorias);
        }
        // --- Opção 2: listar alimentos de uma categoria ---
        else if (opcao == 2) {
            char nome[100];
            printf("Digite o nome da categoria: ");
            fgets(nome, 100, stdin);
            trim_newline(nome);
            CategoriaEnum cat = obter_enum_categoria(nome);
            Categoria* c = buscar_categoria(listaCategorias, cat);
            if (c) imprimir_lista_alimentos(c->alimentos);
            else printf("Categoria não encontrada.\n");
        }
        // --- Opção 3: listar por energia (decrescente) ---
        else if (opcao == 3) {
            char nome[100];
            printf("Categoria: ");
            fgets(nome, 100, stdin);
            trim_newline(nome);
            CategoriaEnum cat = obter_enum_categoria(nome);
            Categoria* c = buscar_categoria(listaCategorias, cat);
            if (c && c->arvoreEnergia) imprimir_decrescente(c->arvoreEnergia);
            else printf("Categoria não encontrada ou sem dados.\n");
        }
        // --- Opção 4: listar por proteína (decrescente) ---
        else if (opcao == 4) {
            char nome[100];
            printf("Categoria: ");
            fgets(nome, 100, stdin);
            trim_newline(nome);
            CategoriaEnum cat = obter_enum_categoria(nome);
            Categoria* c = buscar_categoria(listaCategorias, cat);
            if (c && c->arvoreProteina) imprimir_decrescente(c->arvoreProteina);
            else printf("Categoria não encontrada ou sem dados.\n");
        }
        // --- Opção 5: filtro por faixa de energia ---
        else if (opcao == 5) {
            char nome[100];
            double min, max;
            printf("Categoria: ");
            fgets(nome, 100, stdin);
            trim_newline(nome);
            printf("Energia mínima e máxima: ");
            scanf("%lf %lf", &min, &max);
            CategoriaEnum cat = obter_enum_categoria(nome);
            Categoria* c = buscar_categoria(listaCategorias, cat);
            if (c && c->arvoreEnergia) listar_intervalo(c->arvoreEnergia, min, max);
            else printf("Categoria não encontrada.\n");
        }
        // --- Opção 6: filtro por faixa de proteína ---
        else if (opcao == 6) {
            char nome[100];
            double min, max;
            printf("Categoria: ");
            fgets(nome, 100, stdin);
            trim_newline(nome);
            printf("Proteína mínima e máxima: ");
            scanf("%lf %lf", &min, &max);
            CategoriaEnum cat = obter_enum_categoria(nome);
            Categoria* c = buscar_categoria(listaCategorias, cat);
            if (c && c->arvoreProteina) listar_intervalo(c->arvoreProteina, min, max);
            else printf("Categoria não encontrada.\n");
        }
        // --- Opção 7: remover categoria ---
        else if (opcao == 7) {
            char nome[100];
            printf("Remover categoria: ");
            fgets(nome, 100, stdin);
            trim_newline(nome);
            CategoriaEnum cat = obter_enum_categoria(nome);
            remover_categoria(&listaCategorias, cat);
            modificou = 1;
            printf("Categoria removida.\n");
        }
        // --- Opção 8: remover alimento ---
        else if (opcao == 8) {
            char nomeCat[100], desc[100];
            printf("Categoria: ");
            fgets(nomeCat, 100, stdin);
            trim_newline(nomeCat);
            printf("Descrição do alimento: ");
            fgets(desc, 100, stdin);
            trim_newline(desc);

            CategoriaEnum cat = obter_enum_categoria(nomeCat);
            Categoria* c = buscar_categoria(listaCategorias, cat);
            if (c) {
                remover_alimento(&c->alimentos, desc);

                // Recria árvores após a remoção para manter consistência
                liberar_arvore(&c->arvoreEnergia);
                liberar_arvore(&c->arvoreProteina);

                NoAlimento* atual = c->alimentos;
                while (atual != NULL) {
                    inserir_no_arvore(&c->arvoreEnergia, atual->alimento.energia, &atual->alimento);
                    inserir_no_arvore(&c->arvoreProteina, atual->alimento.proteina, &atual->alimento);
                    atual = atual->prox;
                }

                modificou = 1;
                printf("Alimento removido.\n");
            } else printf("Categoria não encontrada.\n");
        }

    } while (opcao != 9); // Sai do menu apenas se o usuário escolher encerrar

    // Se houveram alterações, salva novamente no arquivo binário
    if (modificou)
        salvar_dados_binarios("dados.bin", listaCategorias);

    // Libera toda a memória antes de encerrar o programa
    liberar_categorias(&listaCategorias);
    printf("Programa encerrado.\n");
    return 0;
}

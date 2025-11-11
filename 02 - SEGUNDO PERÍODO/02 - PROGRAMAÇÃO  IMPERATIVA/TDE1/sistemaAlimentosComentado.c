#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#define MAX_ALIMENTOS 1000
#define MAX_TEXTO 100
#define MAX_CATEGORIAS 100

// Estrutura principal dos dados
typedef struct {
    int numero;
    char descricao[MAX_TEXTO];
    float umidade;
    int energia;
    float proteina;
    float carboidrato;
    char categoria[MAX_TEXTO];
} Alimento;

// ============================================================================
// FUNÇÕES DE COMPARAÇÃO (Para o qsort)
// ============================================================================

// (qsort) Ordem alfabética
int cmp_descricao(const void *a, const void *b) {
    return strcmp((*(Alimento**)a)->descricao, (*(Alimento**)b)->descricao);
}

// (qsort) Ordem decrescente
int cmp_energia(const void *a, const void *b) {
    return (*(Alimento**)b)->energia - (*(Alimento**)a)->energia;
}

// (qsort) Ordem decrescente (float)
int cmp_umidade(const void *a, const void *b) {
    Alimento *al1 = *(Alimento**)a;
    Alimento *al2 = *(Alimento**)b;
    if (al2->umidade > al1->umidade) return 1;
    if (al2->umidade < al1->umidade) return -1;
    return 0;
}

// (qsort) Ordem decrescente (float)
int cmp_proteina(const void *a, const void *b) {
    Alimento *al1 = *(Alimento**)a;
    Alimento *al2 = *(Alimento**)b;
    if (al2->proteina > al1->proteina) return 1;
    if (al2->proteina < al1->proteina) return -1;
    return 0;
}

// (qsort) Ordem decrescente (float)
int cmp_carboidrato(const void *a, const void *b) {
    Alimento *al1 = *(Alimento**)a;
    Alimento *al2 = *(Alimento**)b;
    if (al2->carboidrato > al1->carboidrato) return 1;
    if (al2->carboidrato < al1->carboidrato) return -1;
    return 0;
}

// (qsort) Cálculo da relação (com proteção)
int cmp_energia_proteina(const void *a, const void *b) {
    Alimento *al1 = *(Alimento**)a;
    Alimento *al2 = *(Alimento**)b;
    float rel1 = (al1->proteina > 0.0) ? al1->energia / al1->proteina : 0.0;
    float rel2 = (al2->proteina > 0.0) ? al2->energia / al2->proteina : 0.0;
    if (rel2 > rel1) return 1;
    if (rel2 < rel1) return -1;
    return 0;
}

// (qsort) Cálculo da relação (com proteção)
int cmp_energia_carboidrato(const void *a, const void *b) {
    Alimento *al1 = *(Alimento**)a;
    Alimento *al2 = *(Alimento**)b;
    float rel1 = (al1->carboidrato > 0.0) ? al1->energia / al1->carboidrato : 0.0;
    float rel2 = (al2->carboidrato > 0.0) ? al2->energia / al2->carboidrato : 0.0;
    if (rel2 > rel1) return 1;
    if (rel2 < rel1) return -1;
    return 0;
}

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

// Helper p/ evitar categorias duplicadas
int categoria_existe(char categorias[][MAX_TEXTO], int total, const char *nova) {
    for (int i = 0; i < total; i++)
        if (strcmp(categorias[i], nova) == 0) return 1;
    return 0;
}

void carregar_alimentos(Alimento alimentos[], int *total) {
    FILE *arquivo = fopen("alimentos.csv", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[512];
    fgets(linha, sizeof(linha), arquivo);             // ignora cabeçalho

    while (fgets(linha, sizeof(linha), arquivo) && *total < MAX_ALIMENTOS) {
        linha[strcspn(linha, "\r\n")] = 0;
        char *token = strtok(linha, ",");            
        if (!token) continue;

        Alimento a;
        a.numero = atoi(token); 

        token = strtok(NULL, ",");
        strncpy(a.descricao, token ? token : "", MAX_TEXTO);

        token = strtok(NULL, ",");
        a.umidade = token ? atof(token) : 0; 

        token = strtok(NULL, ",");
        a.energia = token ? atoi(token) : 0; 

        token = strtok(NULL, ",");
        a.proteina = token ? atof(token) : 0; 

        token = strtok(NULL, ",");
        a.carboidrato = token ? atof(token) : 0; 

        token = strtok(NULL, "\n");
        strncpy(a.categoria, token ? token : "", MAX_TEXTO);

        alimentos[(*total)++] = a; // Armazena no vetor principal
    }
    fclose(arquivo);
}

void listar_categorias(Alimento alimentos[], int total) {
    char categorias[MAX_CATEGORIAS][MAX_TEXTO];
    int totalCategorias = 0;

    for (int i = 0; i < total; i++) {
        // Usa a função helper
        if (!categoria_existe(categorias, totalCategorias, alimentos[i].categoria)) {
            strncpy(categorias[totalCategorias++], alimentos[i].categoria, MAX_TEXTO);
        }
    }

    printf("\nCategorias encontradas (%d):\n", totalCategorias);
    for (int i = 0; i < totalCategorias; i++) {
        printf(" - %s\n", categorias[i]);
    }
}

void processar_categoria_com_n(Alimento alimentos[], int total, int (*comparar)(const void*, const void*), const char *titulo) {
    char categoriaBusca[MAX_TEXTO];
    int n;

    printf("\nDigite o nome exato da categoria: ");
    scanf("%s", categoriaBusca);
    printf("Digite a quantidade de alimentos a listar (N): ");
    scanf("%d", &n);

    // A. Filtra (vetor de ponteiros)
    Alimento *filtrados[MAX_ALIMENTOS];
    int totalFiltrados = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(alimentos[i].categoria, categoriaBusca) == 0)
            filtrados[totalFiltrados++] = &alimentos[i]; // Salva o endereço
    }

    if (totalFiltrados == 0) {
        printf("Nenhum alimento encontrado para a categoria '%s'.\n", categoriaBusca);
        return;
    }

    // B. Ordena (qsort)
    qsort(filtrados, totalFiltrados, sizeof(Alimento*), comparar); 
    if (n > totalFiltrados) n = totalFiltrados;

    // C. Lista (Top N)
    printf("\n%s '%s':\n", titulo, categoriaBusca);
    for (int i = 0; i < n; i++) {
        Alimento *a = filtrados[i];
        printf(" - %s (E:%d kcal, P:%.2fg, C:%.2fg, U:%.1f%%)\n",
               a->descricao, a->energia, a->proteina, a->carboidrato, a->umidade);
    }
}

void processar_categoria_sem_n(Alimento alimentos[], int total, int (*comparar)(const void*, const void*), const char *titulo) {
    char categoriaBusca[MAX_TEXTO];

    printf("\nDigite o nome exato da categoria: ");
    scanf("%s", categoriaBusca);

    // A. Filtra (vetor de ponteiros)
    Alimento *filtrados[MAX_ALIMENTOS];
    int totalFiltrados = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(alimentos[i].categoria, categoriaBusca) == 0)
            filtrados[totalFiltrados++] = &alimentos[i];
    }

    if (totalFiltrados == 0) {
        printf("Nenhum alimento encontrado para a categoria '%s'.\n", categoriaBusca);
        return;
    }

    // B. Ordena (qsort)
    qsort(filtrados, totalFiltrados, sizeof(Alimento*), comparar); 

    // C. Lista (TODOS)
    printf("\n%s '%s':\n", titulo, categoriaBusca);
    for (int i = 0; i < totalFiltrados; i++) {
        Alimento *a = filtrados[i];
        printf(" - %s (E:%d kcal, P:%.2fg, C:%.2fg, U:%.1f%%)\n",
               a->descricao, a->energia, a->proteina, a->carboidrato, a->umidade);
    }
}

// Menu de opções
void menu() {
    printf("\n=== MENU ===\n");
    printf("a. Listar todas as categorias\n");
    printf("b. Listar alimentos por ordem alfabetica\n");
    printf("c. Listar alimentos por energia (decrescente)\n");
    printf("d. Top N alimentos com maior umidade\n");
    printf("e. Top N alimentos com maior energia\n");
    printf("f. Top N alimentos com maior proteina\n");
    printf("g. Top N alimentos com maior carboidrato\n");
    printf("h. Top N alimentos com maior relacao energia/proteina\n");
    printf("i. Top N alimentos com maior relacao energia/carboidrato\n");
    printf("j. Sair\n");
    printf("Escolha uma opcao: ");
}

// ============================================================================
// MAIN (Função Principal)
// ============================================================================

int main() {
    Alimento alimentos[MAX_ALIMENTOS];
    int totalAlimentos = 0;

    // 1. Carga inicial dos dados
    carregar_alimentos(alimentos, &totalAlimentos);
    printf("Carregados %d alimentos\n", totalAlimentos);

    char opcao;
    // 2. Loop do menu
    do {
        menu();
        scanf(" %c", &opcao);

        // 3. Chamadas das funções
        switch (opcao) {
            case 'a':listar_categorias(alimentos, totalAlimentos);break;
            case 'b':processar_categoria_sem_n(alimentos, totalAlimentos, cmp_descricao, "Alimentos em ordem alfabética");break;
            case 'c':processar_categoria_sem_n(alimentos, totalAlimentos, cmp_energia, "Alimentos por energia decrescente");break;
            case 'd':processar_categoria_com_n(alimentos, totalAlimentos, cmp_umidade, "Top alimentos com maior umidade");break;
            case 'e':processar_categoria_com_n(alimentos, totalAlimentos, cmp_energia, "Top alimentos com maior energia");break;
            case 'f':processar_categoria_com_n(alimentos, totalAlimentos, cmp_proteina, "Top alimentos com maior proteina");break;
            case 'g':processar_categoria_com_n(alimentos, totalAlimentos, cmp_carboidrato, "Top alimentos com maior carboidrato");break;
            case 'h':processar_categoria_com_n(alimentos, totalAlimentos, cmp_energia_proteina, "Top alimentos com maior relacao energia/proteina");break;
            case 'i':processar_categoria_com_n(alimentos, totalAlimentos, cmp_energia_carboidrato, "Top alimentos com maior relacao energia/carboidrato");break;
            case 'j':printf("Encerrando o programa...\n");break;
            default:printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 'j');

    return 0;
}

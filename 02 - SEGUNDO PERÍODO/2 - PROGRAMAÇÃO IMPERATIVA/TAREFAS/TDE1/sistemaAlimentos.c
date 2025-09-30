#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_ALIMENTOS 100
#define MAX_DESC 100

typedef enum {
    CEREAIS, VEGETAIS, FRUTAS, GORDURAS, PESCADOS, 
    CARNES, LATICINIOS, BEBIDAS, OVOS, ACUCARES, OUTROS
} Categoria;

typedef struct {
    int numero;
    char descricao[MAX_DESC];
    float umidade, energia, proteina, carboidrato;
    Categoria categoria;
} Alimento;

typedef struct {
    float valor;
    Alimento* alimento;
} ItemOrdenacao;

// Funções iniciais:
void trim(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && isspace(str[i])) str[i--] = '\0';
}

Categoria str_para_cat(const char* cat_str) {
    if (!cat_str || strlen(cat_str) == 0) return OUTROS;
    
    char lower[100];
    for (int i = 0; cat_str[i] && i < 99; i++) 
        lower[i] = tolower(cat_str[i]);
    lower[strlen(cat_str)] = '\0';
    
    if (strstr(lower, "cereal")) return CEREAIS;
    if (strstr(lower, "verdura") || strstr(lower, "hortali")) return VEGETAIS;
    if (strstr(lower, "fruta")) return FRUTAS;
    if (strstr(lower, "gordura") || strstr(lower, "óleo")) return GORDURAS;
    if (strstr(lower, "peixe") || strstr(lower, "pescado")) return PESCADOS;
    if (strstr(lower, "carne")) return CARNES;
    if (strstr(lower, "leite") || strstr(lower, "queijo")) return LATICINIOS;
    if (strstr(lower, "bebida")) return BEBIDAS;
    if (strstr(lower, "ovo")) return OVOS;
    if (strstr(lower, "açúcar") || strstr(lower, "doce") || strstr(lower, "acucar")) return ACUCARES;
    return OUTROS;
}

const char* cat_para_str(Categoria cat) {
    char* categorias[] = {
        "CEREAIS", "VEGETAIS", "FRUTAS", "GORDURAS", "PESCADOS",
        "CARNES", "LATICINIOS", "BEBIDAS", "OVOS", "ACUCARES", "OUTROS"
    };
    return categorias[cat];
}

void bubble_sort(ItemOrdenacao arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j].valor < arr[j+1].valor) {
                ItemOrdenacao temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

// Função para ler o .CSV
int carregar_arquivo(const char* filename, Alimento alimentos[]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro: Arquivo '%s' não encontrado!\n", filename);
        return 0;
    }

    char linha[500];
    int count = 0;
    
    // Aqui pula o cabeçalho, se houver:
    if (fgets(linha, sizeof(linha), file)) {
        if (!isdigit(linha[0]) && strstr(linha, "numero")) {
            printf("Pulando cabeçalho...\n");
        } else {
            fseek(file, 0, SEEK_SET);
        }
    }
    
    while (fgets(linha, sizeof(linha), file) && count < MAX_ALIMENTOS) {
        // Remove a quebra de linha:
        linha[strcspn(linha, "\n")] = 0;
        
        if (strlen(linha) == 0) continue;

        // Processamento manual da .CSV:
        char temp[500];
        strcpy(temp, linha);
        
        int campo_atual = 0;
        char *inicio = temp;
        char *fim = temp;
        int entre_aspas = 0;
        
        char numero_str[20], descricao[200], umidade_str[20], energia_str[20];
        char proteina_str[20], carboidrato_str[20], categoria_str[100];
        
        // Inicializa as strings: 
        strcpy(descricao, "");
        strcpy(categoria_str, "");
        
        for (int i = 0; temp[i] != '\0'; i++) {
            if (temp[i] == '\"') {
                entre_aspas = !entre_aspas;
            } else if (temp[i] == ',' && !entre_aspas) {
                temp[i] = '\0';
                
                switch(campo_atual) {
                    case 0: strcpy(numero_str, inicio); break;
                    case 1: strcpy(descricao, inicio); break;
                    case 2: strcpy(umidade_str, inicio); break;
                    case 3: strcpy(energia_str, inicio); break;
                    case 4: strcpy(proteina_str, inicio); break;
                    case 5: strcpy(carboidrato_str, inicio); break;
                }
                
                campo_atual++;
                inicio = temp + i + 1;
            }
        }
        
        // Último campo - 'Categoria':
        if (campo_atual == 6) {
            strcpy(categoria_str, inicio);
        }
        
        // Para remover as aspas da descrição e categoria:
        char desc_limpa[200], cat_limpa[100];
        strcpy(desc_limpa, descricao);
        strcpy(cat_limpa, categoria_str);
        
        // Remove as aspas:
        for (int i = 0; desc_limpa[i]; i++) {
            if (desc_limpa[i] == '\"') {
                for (int j = i; desc_limpa[j]; j++) {
                    desc_limpa[j] = desc_limpa[j+1];
                }
                i--;
            }
        }
        for (int i = 0; cat_limpa[i]; i++) {
            if (cat_limpa[i] == '\"') {
                for (int j = i; cat_limpa[j]; j++) {
                    cat_limpa[j] = cat_limpa[j+1];
                }
                i--;
            }
        }
        
        trim(desc_limpa);
        trim(cat_limpa);
        
        // Converte os valores:
        if (campo_atual >= 6) {
            alimentos[count].numero = atoi(numero_str);
            strcpy(alimentos[count].descricao, desc_limpa);
            
            // Substitui o 'TR' por 0:
            alimentos[count].umidade = (strstr(umidade_str, "Tr")) ? 0.0 : atof(umidade_str);
            alimentos[count].energia = (strstr(energia_str, "Tr")) ? 0.0 : atof(energia_str);
            alimentos[count].proteina = (strstr(proteina_str, "Tr")) ? 0.0 : atof(proteina_str);
            alimentos[count].carboidrato = (strstr(carboidrato_str, "Tr")) ? 0.0 : atof(carboidrato_str);
            
            alimentos[count].categoria = str_para_cat(cat_limpa);
            count++;
        }
    }
    
    fclose(file);
    printf("Carregados %d alimentos com sucesso!\n", count);
    return count;
}

// Funções do 'Menu':
void listar_cats(Alimento alimentos[], int total) {
    printf("\n=== CATEGORIAS ===\n");
    Categoria cats[20];
    int count = 0;
    
    for (int i = 0; i < total; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (cats[j] == alimentos[i].categoria) found = 1;
        }
        if (!found) cats[count++] = alimentos[i].categoria;
    }
    
    for (int i = 0; i < count; i++) 
        printf("%d. %s\n", i + 1, cat_para_str(cats[i]));
}

Categoria escolher_categoria(Alimento alimentos[], int total) {
    listar_cats(alimentos, total);
    
    Categoria cats[20];
    int count = 0;
    for (int i = 0; i < total; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (cats[j] == alimentos[i].categoria) found = 1;
        }
        if (!found) cats[count++] = alimentos[i].categoria;
    }
    
    int op;
    printf("\nEscolha a categoria: ");
    scanf("%d", &op);
    
    return (op >= 1 && op <= count) ? cats[op-1] : OUTROS;
}

void listar_alfabetico(Alimento alimentos[], int total) {
    Categoria cat = escolher_categoria(alimentos, total);
    if (cat == OUTROS) {
        printf("Categoria inválida!\n");
        return;
    }
    
    Alimento* itens[MAX_ALIMENTOS];
    int count = 0;
    
    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == cat) {
            itens[count++] = &alimentos[i];
        }
    }
    
    // Coloca em ordem alfabética:
    for (int i = 0; i < count-1; i++) {
        for (int j = i+1; j < count; j++) {
            if (strcmp(itens[i]->descricao, itens[j]->descricao) > 0) {
                Alimento* temp = itens[i];
                itens[i] = itens[j];
                itens[j] = temp;
            }
        }
    }
    
    printf("\n%s (ordem alfabética):\n", cat_para_str(cat));
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, itens[i]->descricao);
    }
}

void listar_por_energia(Alimento alimentos[], int total) {
    Categoria cat = escolher_categoria(alimentos, total);
    if (cat == OUTROS) {
        printf("Categoria inválida!\n");
        return;
    }
    
    ItemOrdenacao itens[MAX_ALIMENTOS];
    int count = 0;
    
    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == cat) {
            itens[count].valor = alimentos[i].energia;
            itens[count].alimento = &alimentos[i];
            count++;
        }
    }
    
    bubble_sort(itens, count);
    
    printf("\n%s (por energia):\n", cat_para_str(cat));
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %.1f kcal\n", i + 1, 
               itens[i].alimento->descricao, itens[i].alimento->energia);
    }
}

void top_N(Alimento alimentos[], int total, int criterio) {
    Categoria cat = escolher_categoria(alimentos, total);
    if (cat == OUTROS) {
        printf("Categoria inválida!\n");
        return;
    }
    
    int N;
    printf("Quantos alimentos: ");
    scanf("%d", &N);
    
    ItemOrdenacao itens[MAX_ALIMENTOS];
    int count = 0;
    
    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == cat) {
            switch(criterio) {
                case 1: itens[count].valor = alimentos[i].umidade; break;
                case 2: itens[count].valor = alimentos[i].energia; break;
                case 3: itens[count].valor = alimentos[i].proteina; break;
                case 4: itens[count].valor = alimentos[i].carboidrato; break;
                case 5: 
                    if (alimentos[i].proteina > 0) {
                        itens[count].valor = alimentos[i].energia / alimentos[i].proteina;
                    } else {
                        itens[count].valor = 0;
                    }
                    break;
                case 6: 
                    if (alimentos[i].carboidrato > 0) {
                        itens[count].valor = alimentos[i].energia / alimentos[i].carboidrato;
                    } else {
                        itens[count].valor = 0;
                    }
                    break;
            }
            itens[count].alimento = &alimentos[i];
            count++;
        }
    }
    
    if (N > count) N = count;
    bubble_sort(itens, count);
    
    char* nomes[] = {"umidade", "energia", "proteina", "carboidrato", 
                    "relacao energia/proteina", "relacao energia/carboidrato"};
    char* unidades[] = {"%%", " kcal", " g", " g", " kcal/g", " kcal/g"};
    
    printf("\nTop %d em %s:\n", N, nomes[criterio-1]);
    for (int i = 0; i < N; i++) {
        printf("%d. %s - %.1f%s\n", i + 1, itens[i].alimento->descricao, 
               itens[i].valor, unidades[criterio-1]);
    }
}

void menu() {
    printf("\n=== SISTEMA ALIMENTOS ===\n");
    printf("a. Listar categorias\n");
    printf("b. Listar por categoria (alfabética)\n");
    printf("c. Listar por categoria (energia)\n");
    printf("d. Top N em umidade\n");
    printf("e. Top N em energia\n");
    printf("f. Top N em proteina\n");
    printf("g. Top N em carboidrato\n");
    printf("h. Top N em relacao energia/proteina\n");
    printf("i. Top N em relacao energia/carboidrato\n");
    printf("j. Sair\n");
    printf("Opcao: ");
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    
    Alimento alimentos[MAX_ALIMENTOS];
    int total = carregar_arquivo("alimentos.csv", alimentos);
    
    if (total == 0) {
        printf("Nenhum alimento carregado! Verifique o arquivo alimentos.csv\n");
        return 1;
    }
    
    printf("Sistema pronto com %d alimentos!\n", total);
    
    char op;
    do {
        menu();
        scanf(" %c", &op);
        
        switch(op) {
            case 'a': listar_cats(alimentos, total); break;
            case 'b': listar_alfabetico(alimentos, total); break;
            case 'c': listar_por_energia(alimentos, total); break;
            case 'd': top_N(alimentos, total, 1); break;
            case 'e': top_N(alimentos, total, 2); break;
            case 'f': top_N(alimentos, total, 3); break;
            case 'g': top_N(alimentos, total, 4); break;
            case 'h': top_N(alimentos, total, 5); break;
            case 'i': top_N(alimentos, total, 6); break;
            case 'j': printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (op != 'j');
    
    return 0;
}

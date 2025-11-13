#include <string.h>
#include <ctype.h>
#include "tipos_enum.h"

// ============================================================
// Módulo responsável por mapear nomes de categorias de alimentos
// para seus respectivos enums e vice-versa.
// ============================================================

// Vetor contendo os nomes das categorias conforme aparecem no arquivo CSV.
// A posição no vetor corresponde ao valor do enum "CategoriaEnum".
static const char* nomes_categorias[TOTAL_CATEGORIAS] = {
    "Cereais_e_derivados",
    "Verduras_hortalicas_e_derivados",
    "Frutas_e_derivados",
    "Gorduras_e_oleos",
    "Pescados_e_frutos_do_mar",
    "Carnes_e_derivados",
    "Leite_e_derivados",
    "Bebidas",
    "Ovos_e_derivados",
    "Produtos_acucarados",
    "Miscelaneas",
    "Outros_alimentos_industrializados",
    "Alimentos_preparados",
    "Leguminosas_e_derivados",
    "Nozes_e_sementes"
};

// ------------------------------------------------------------
// Função: obter_nome_categoria
// Retorna o nome (string) correspondente a um valor do enum CategoriaEnum.
// Parâmetros:
//   - categoria: valor do enum CategoriaEnum.
// Retorno:
//   - ponteiro para string com o nome da categoria correspondente;
//   - "Categoria_desconhecida" se o valor for inválido.
// ------------------------------------------------------------
const char* obter_nome_categoria(CategoriaEnum categoria) {
    if (categoria >= 0 && categoria < TOTAL_CATEGORIAS)
        return nomes_categorias[categoria];
    return "Categoria_desconhecida";
}

// ------------------------------------------------------------
// Função: obter_enum_categoria
// Converte o nome textual de uma categoria (como aparece no CSV)
// para o valor correspondente no enum CategoriaEnum.
// A comparação é feita de forma insensível a maiúsculas e minúsculas.
// Parâmetros:
//   - nome: string contendo o nome da categoria a ser procurada.
// Retorno:
//   - valor do enum CategoriaEnum correspondente;
//   - TOTAL_CATEGORIAS (valor inválido) se não houver correspondência.
// ------------------------------------------------------------
CategoriaEnum obter_enum_categoria(const char* nome) {
    // Percorre todas as categorias conhecidas
    for (int i = 0; i < TOTAL_CATEGORIAS; i++) {
        int j = 0;
        const char* n1 = nomes_categorias[i];
        const char* n2 = nome;
        int igual = 1;

        // Compara caractere por caractere, ignorando maiúsculas/minúsculas
        while (n1[j] && n2[j]) {
            if (tolower((unsigned char)n1[j]) != tolower((unsigned char)n2[j])) {
                igual = 0;
                break;
            }
            j++;
        }

        // Se ambas as strings terminam ao mesmo tempo e são iguais
        if (igual && n1[j] == '\0' && n2[j] == '\0') {
            return (CategoriaEnum)i;  // retorna o enum correspondente
        }
    }

    // Caso nenhum nome corresponda, retorna valor inválido
    return TOTAL_CATEGORIAS;
}

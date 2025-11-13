#ifndef TIPOS_ENUM_H
#define TIPOS_ENUM_H

// ---------------------------------------------------------------------------
// Enum: CategoriaEnum
// ---------------------------------------------------------------------------
// Descrição:
//  Representa as categorias de alimentos presentes no arquivo CSV.
//  Cada valor corresponde a um grupo de alimentos definido na base de dados.
//
// Observação:
//  O último valor (TOTAL_CATEGORIAS) não representa uma categoria real,
//  mas sim o total de categorias — útil para loops e contagens.
// ---------------------------------------------------------------------------
typedef enum {
    CEREAIS_E_DERIVADOS,
    VERDURAS_HORTALICAS_E_DERIVADOS,
    FRUTAS_E_DERIVADOS,
    GORDURAS_E_OLEOS,
    PESCADOS_E_FRUTOS_DO_MAR,
    CARNES_E_DERIVADOS,
    LEITE_E_DERIVADOS,
    BEBIDAS,
    OVOS_E_DERIVADOS,
    PRODUTOS_ACUCARADOS,
    MISSELANEAS,
    OUTROS_ALIMENTOS_INDUSTRIALIZADOS,
    ALIMENTOS_PREPARADOS,
    LEGUMINOSAS_E_DERIVADOS,
    NOZES_E_SEMENTES,
    TOTAL_CATEGORIAS // marcador de quantidade total de categorias
} CategoriaEnum;

// ---------------------------------------------------------------------------
// Função: obter_nome_categoria
// ---------------------------------------------------------------------------
// Descrição:
//  Retorna o nome textual (string) correspondente a uma categoria do enum.
//  Exemplo: CEREAIS_E_DERIVADOS → "Cereais e Derivados"
//
// Parâmetros:
//  - categoria: valor do tipo CategoriaEnum
//
// Retorno:
//  Ponteiro para string com o nome da categoria
// ---------------------------------------------------------------------------
const char* obter_nome_categoria(CategoriaEnum categoria);

// ---------------------------------------------------------------------------
// Função: obter_enum_categoria
// ---------------------------------------------------------------------------
// Descrição:
//  Converte uma string (nome da categoria) em seu valor correspondente no enum.
//  Exemplo: "Frutas e Derivados" → FRUTAS_E_DERIVADOS
//
// Parâmetros:
//  - nome: string contendo o nome da categoria
//
// Retorno:
//  Valor correspondente do enum CategoriaEnum
// ---------------------------------------------------------------------------
CategoriaEnum obter_enum_categoria(const char* nome);

#endif

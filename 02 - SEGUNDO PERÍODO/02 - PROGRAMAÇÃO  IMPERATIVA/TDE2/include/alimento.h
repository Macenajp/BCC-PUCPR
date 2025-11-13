#ifndef ALIMENTO_H
#define ALIMENTO_H

#include "tipos_enum.h" // Inclui o tipo enumerado que define as categorias dos alimentos

// Estrutura que representa um alimento individual
typedef struct {
    int numero;                  // Número identificador do alimento
    char descricao[100];         // Nome ou descrição do alimento
    double energia;              // Valor energético em kcal
    double proteina;             // Quantidade de proteína em gramas
    CategoriaEnum categoria;     // Categoria do alimento (definida em tipos_enum.h)
} Alimento;

// Cria e inicializa dinamicamente um novo alimento com os dados informados
Alimento* criar_alimento(int numero, const char* descricao, double energia, double proteina, CategoriaEnum categoria);

// Exibe na tela as informações de um alimento formatadas
void imprimir_alimento(const Alimento* a);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alimento.h"
#include "tipos_enum.h"

// ---------------------------------------------------------------------------
// Função: criar_alimento
// ---------------------------------------------------------------------------
// Descrição:
//  Aloca dinamicamente e inicializa uma estrutura do tipo Alimento com os
//  dados informados como parâmetros.
//
// Parâmetros:
//  - numero: código identificador do alimento.
//  - descricao: texto descritivo do alimento (ex: "Arroz integral").
//  - energia: valor energético do alimento em Kcal.
//  - proteina: quantidade de proteína em gramas.
//  - categoria: valor do enum CategoriaEnum que identifica o grupo do alimento.
//
// Retorno:
//  Ponteiro para a estrutura Alimento criada. 
//  Retorna NULL em caso de falha na alocação de memória.
//
// Observações:
//  - A função utiliza strncpy para copiar a descrição com segurança.
// ---------------------------------------------------------------------------
Alimento* criar_alimento(int numero, const char* descricao, double energia, double proteina, CategoriaEnum categoria) {
    Alimento* a = (Alimento*)malloc(sizeof(Alimento));  // Alocação dinâmica
    if (!a) return NULL;  // Verifica se a alocação falhou

    a->numero = numero;
    strncpy(a->descricao, descricao, sizeof(a->descricao));  // Cópia segura da descrição
    a->descricao[sizeof(a->descricao) - 1] = '\0';  // Garante o término da string
    a->energia = energia;
    a->proteina = proteina;
    a->categoria = categoria;

    return a;
}

// ---------------------------------------------------------------------------
// Função: imprimir_alimento
// ---------------------------------------------------------------------------
// Descrição:
//  Exibe na tela as informações básicas de um alimento.
//
// Parâmetros:
//  - a: ponteiro para a estrutura Alimento a ser exibida.
//
// Retorno:
//  Nenhum.
//
// Observações:
//  - Caso o ponteiro seja NULL, nada é impresso.
//  - A categoria é exibida como um valor numérico (valor do enum).
// ---------------------------------------------------------------------------
void imprimir_alimento(const Alimento* a) {
    if (!a) return;  // Evita dereferenciar ponteiro nulo
    printf("%d - %s | Energia: %.2f kcal | Proteína: %.2f g | Categoria: %d\n",
           a->numero, a->descricao, a->energia, a->proteina, a->categoria);
}

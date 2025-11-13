#include <stdio.h>
#include "gerenciador_arquivos.h"

//
// Programa: P1 - Conversor CSV → Binário
// -------------------------------------------------------------
// Descrição:
//  Este programa lê um arquivo CSV contendo dados de alimentos
//  (número, descrição, energia, proteína e categoria) e converte
//  essas informações para um arquivo binário denominado "dados.bin".
//
//  O arquivo binário armazenará estruturas do tipo Alimento,
//  facilitando o carregamento posterior em outros programas.
//
// Dependências:
//  - gerenciador_arquivos.h
//  - alimentos.csv (de entrada)
//
// Autor: (adicione seu nome aqui)
// Disciplina: (adicione o nome da disciplina, se desejar)
// Data: (adicione a data)
// -------------------------------------------------------------
// Etapas executadas:
//  1. Define os nomes dos arquivos CSV e BIN.
//  2. Chama a função 'converter_csv_para_bin()'.
//  3. Exibe mensagens informativas no terminal.
// -------------------------------------------------------------
// Observações:
//  O arquivo "alimentos.csv" deve estar no mesmo diretório do programa.
//  O resultado será salvo em "dados.bin".
//
int main() {
    // Define os nomes dos arquivos de entrada e saída
    char nomeCSV[50] = "alimentos.csv";
    char nomeBIN[50] = "dados.bin";

    // Mensagem informativa para o usuário
    printf("Convertendo '%s' para '%s'...\n", nomeCSV, nomeBIN);

    // Realiza a conversão do CSV para o arquivo binário
    converter_csv_para_bin(nomeCSV, nomeBIN);

    // Mensagem de sucesso
    printf("Conversão concluída.\n");

    return 0;
}

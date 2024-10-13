#pragma once

#include "sorts.h"

//============== Auxiliares ==============//
int* cria_vetor(long int tam);
void gera_vetor(long int tam, int* vet);
void copy_vetor(long int tam, int* vet_origem, int* vet_destino);
void print_vetor(int* vet, long int tam);
void print_dados_sort(DadosSort dados);
void print_linha_tabela_dados_sort(DadosSort dados);
void print_file_dados_sort(FILE* file, DadosSort dados);

//============== Estatísticas ==============//
DadosSort calcula_estatisticas(DadosAmostra* dados, int tamAmostra);
#pragma once

typedef struct dados_da_amostra {
	double tempo_de_execucao;
	long long int num_trocas;
	long long int num_comparacoes;
} DadosAmostra;

typedef struct estatisticas {
	double media;
	double variancia;
	double desvio_padrao;
} Estatisticas;

typedef struct dados_sort {
	Estatisticas tempo_de_execucao;
	Estatisticas num_trocas;
	Estatisticas num_comparacoes;
} DadosSort;

//============== Sorts ==============//
//Insertion
void insertion_sort(int* vet, long int tam, DadosAmostra* dado);

//Selection
void selection_sort(int* vet, int long tam, DadosAmostra* dado);

//Merge
void merge_sort(int* vet, int comeco, int fim, DadosAmostra* dados);
void intercala(int* vet, int comeco, int meio, int fim, DadosAmostra* dados);

//Heap
void heap_sort(int* vet, long int tam, DadosAmostra* dados);
void max_heapify(int* vet, long int tam, int i, DadosAmostra* dados);

//Quick
void quick_sort(int* vet, int p, long int r, DadosAmostra* dados);
int partition(int* vet, int p, long int r, DadosAmostra* dados);

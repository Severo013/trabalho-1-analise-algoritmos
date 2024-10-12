#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "sorts.h"

//Insertion
void insertionSort(int* vet, long int tam, DadosAmostra* dado)
{
	int i, j, chave;
	clock_t tempo1, tempo2;

	printf("comps no insertion: %lld\n", dado->num_comparacoes);
	printf("trocas no insertion: %lld\n", dado->num_trocas);

	tempo1 = clock();

	for (i = 1; i < tam; i++) {
		chave = vet[i];
		j = i - 1;
		while (j >= 0 && vet[j] > chave) {
			vet[j + 1] = vet[j];
			j = j - 1;
			dado->num_trocas++;
			dado->num_comparacoes++;
		}

		dado->num_comparacoes++;
		vet[j + 1] = chave;
	}

	tempo2 = clock();

	dado->tempo_de_execucao = (double)(tempo2 - tempo1) / CLOCKS_PER_SEC;

	printf("comps no insertion: %lld\n", dado->num_comparacoes);
	printf("trocas no insertion: %lld\n", dado->num_trocas);
}

//Selection
void selectionSort(int* vet, int long tam, DadosAmostra* dado)
{
	int i, j, min, aux;
	clock_t tempo1, tempo2;

	tempo1 = clock();

	for (i = 0; i < tam - 1; i++) {
		min = i;
		for (j = i + 1; j < tam; j++) {
			dado->num_comparacoes++;
			if (vet[j] < vet[min]) {
				min = j;
			}
		}
		aux = vet[i];
		vet[i] = vet[min];
		vet[min] = aux;

		dado->num_trocas++;
	}

	tempo2 = clock();

	dado->tempo_de_execucao = (double)(tempo2 - tempo1) / CLOCKS_PER_SEC;
}

//Merge
void mergeSort(int* vet, int comeco, int fim, DadosAmostra* dados) {
	int meio = (fim + comeco) / 2;
	if (comeco < fim) {
		mergeSort(vet, comeco, meio, dados);
		mergeSort(vet, meio + 1, fim, dados);
		intercala(vet, comeco, meio, fim, dados);
	}

	dados->num_comparacoes++;
}

void intercala(int* vet, int comeco, int meio, int fim, DadosAmostra* dados) {
	int* temp = (int*)malloc(sizeof(fim - comeco + 1));
	int pos = 0, pos_comeco = comeco, pos_final = meio + 1;

	while (pos_comeco <= meio && pos_final <= fim) {
		if (vet[pos_comeco] < vet[pos_final]) {
			temp[pos++] = vet[pos_comeco++];
			dados->num_trocas++;
		}
		else {
			temp[pos++] = vet[pos_final++];
			dados->num_trocas++;
		}

		dados->num_comparacoes++;
	}

	while (pos_comeco <= meio) {
		temp[pos++] = vet[pos_comeco++];
		dados->num_trocas++;
	}

	while (pos_final <= fim) {
		temp[pos++] = vet[pos_final++];
		dados->num_trocas++;
	}

	int i;
	for (i = 0; i < pos; i++) {
		vet[i + comeco] = temp[i];
	}

	return;
}

//Heap
void heapSort(int* vet, long int tam, DadosAmostra* dados)
{
	int i, aux;

	for (i = tam / 2 - 1; i >= 0; i--) {
		maxHeapify(vet, tam, i, dados);
	}

	for (i = tam - 1; i >= 0; i--) {
		aux = vet[0];
		vet[0] = vet[i];
		vet[i] = aux;

		dados->num_trocas++;
		maxHeapify(vet, i, 0, dados);
	}
}

void maxHeapify(int* vet, long int tam, int i, DadosAmostra* dados)
{
	int aux;
	int maior = i;
	int e = 2 * i + 1;
	int d = 2 * i + 2;

	dados->num_comparacoes++;
	if (e < tam && vet[e] > vet[maior]) {
		maior = e;
	}

	dados->num_comparacoes++;
	if (d < tam && vet[d] > vet[maior]) {
		maior = d;
	}

	dados->num_comparacoes++;
	if (maior != i) {
		aux = vet[i];
		vet[i] = vet[maior];
		vet[maior] = aux;

		dados->num_trocas++;
		maxHeapify(vet, tam, maior, dados);
	}
}

//Quick
void quickSort(int* vet, int p, long int r, DadosAmostra* dados)
{
	int q;


	if (p < r) {
		q = partition(vet, p, r, dados);
		quickSort(vet, p, q - 1, dados);
		quickSort(vet, q + 1, r, dados);
	}
}

int partition(int* vet, int p, long int r, DadosAmostra* dados)
{
	int aux;
	int x = vet[r]; // pivo
	int i = p - 1, j;

	for (j = p; j <= r - 1; j++) {

		dados->num_comparacoes++;
		if (vet[j] < x) {
			i++;
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
			dados->num_trocas++;
		}
	}

	aux = vet[i + 1];
	vet[i + 1] = vet[r];
	vet[r] = aux;
	dados->num_trocas++;

	return i + 1;
}
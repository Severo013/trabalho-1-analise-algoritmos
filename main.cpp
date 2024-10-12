#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "sorts.h"

DadosSort calculaEstatisticas(DadosAmostra* dados, int tamAmostra)
{
	DadosSort estats;
	int i;
	for (i = 0; i < tamAmostra; i++) {
		printf("n_comp[%d]: %lld\n\n", i, dados[i].num_comparacoes);
	}

	estats.tempo_de_execucao.media = 0;
	estats.tempo_de_execucao.desvio_padrao = 0;
	estats.tempo_de_execucao.variancia = 0;
	estats.num_trocas.media = 0;
	estats.num_trocas.desvio_padrao = 0;
	estats.num_trocas.variancia = 0;
	estats.num_comparacoes.media = 0;
	estats.num_comparacoes.desvio_padrao = 0;
	estats.num_comparacoes.variancia = 0;

	for (i = 0; i < tamAmostra; i++) {
		/* ************ MEDIA ************* */
		//printf("dados[%d].")
		estats.tempo_de_execucao.media += dados[i].tempo_de_execucao;

		estats.num_trocas.media += dados[i].num_trocas;

		estats.num_comparacoes.media += dados[i].num_comparacoes;
	}

	estats.tempo_de_execucao.media /= tamAmostra;
	estats.num_trocas.media /= tamAmostra;
	estats.num_comparacoes.media /= tamAmostra;

	for (i = 0; i < tamAmostra; i++) {
		/* ************ VARIANCIA E DESVIO ************* */
		estats.tempo_de_execucao.variancia += pow((dados[i].tempo_de_execucao - estats.tempo_de_execucao.media), 2);

		estats.num_trocas.variancia += pow((dados[i].num_trocas - estats.num_trocas.media), 2);

		estats.num_comparacoes.variancia += pow((dados[i].num_comparacoes - estats.num_comparacoes.media), 2);
	}
	estats.tempo_de_execucao.variancia /= (tamAmostra - 1);
	estats.tempo_de_execucao.desvio_padrao = sqrt(estats.tempo_de_execucao.variancia);

	estats.num_trocas.variancia /= (tamAmostra - 1);
	estats.num_trocas.desvio_padrao = sqrt(estats.num_trocas.variancia);

	estats.num_comparacoes.variancia /= (tamAmostra - 1);
	estats.num_comparacoes.desvio_padrao = sqrt(estats.num_comparacoes.variancia);


	return estats;
}

void printaEstats(DadosSort dados)
{
	printf("[Tempo de exec]\n");
	printf("Media: %f\n", dados.tempo_de_execucao.media);
	printf("Variancia: %f\n", dados.tempo_de_execucao.variancia);
	printf("DP: %f\n", dados.tempo_de_execucao.desvio_padrao);

	printf("[N trocas]\n");
	printf("Media: %f\n", dados.num_trocas.media);
	printf("Variancia: %f\n", dados.num_trocas.variancia);
	printf("DP: %f\n", dados.num_trocas.desvio_padrao);

	printf("[N comparas]\n");
	printf("Media: %f\n", dados.num_comparacoes.media);
	printf("Variancia: %f\n", dados.num_comparacoes.variancia);
	printf("DP: %f\n", dados.num_comparacoes.desvio_padrao);

}

int main()
{
	int* vet;
	long int tam;

	clock_t tempo1_merge, tempo2_merge;
	clock_t tempo1_heap, tempo2_heap;
	clock_t tempo1_quick, tempo2_quick;

	srand(time(NULL));

	printf("Insira o tamanho do vetor: ");
	scanf("%ld", &tam);

	char filename_insertion[50];
	char filename_selection[50];
	char filename_merge[50];
	char filename_heap[50];
	char filename_quick[50];



	sprintf(filename_insertion, "insertion%d.txt", tam);
	sprintf(filename_selection, "selection%d.txt", tam);
	sprintf(filename_heap, "heap%d.txt", tam);
	sprintf(filename_merge, "merge%d.txt", tam);
	sprintf(filename_quick, "quick%d.txt", tam);

	FILE* fp_insertion = fopen(filename_insertion, "w+");
	FILE* fp_selection = fopen(filename_selection, "w+");
	FILE* fp_merge = fopen(filename_merge, "w+");
	FILE* fp_heap = fopen(filename_heap, "w+");
	FILE* fp_quick = fopen(filename_quick, "w+");

	int nAmostras;

	printf("Entre com o nÃºmero de amostras: ");
	scanf("%d", &nAmostras);

	int i;
	DadosAmostra* dados_insertion = (DadosAmostra*)malloc(sizeof(DadosAmostra) * nAmostras);
	for (i = 0; i < nAmostras; i++) {
		dados_insertion[i].num_comparacoes = 0;
		dados_insertion[i].num_trocas = 0;
		dados_insertion[i].tempo_de_execucao = 0;
	}

	DadosAmostra* dados_selection = (DadosAmostra*)malloc(sizeof(DadosAmostra) * nAmostras);
	for (i = 0; i < nAmostras; i++) {
		dados_selection[i].num_comparacoes = 0;
		dados_selection[i].num_trocas = 0;
		dados_selection[i].tempo_de_execucao = 0;
	}

	DadosAmostra* dados_merge = (DadosAmostra*)malloc(sizeof(DadosAmostra) * nAmostras);
	for (i = 0; i < nAmostras; i++) {
		dados_merge[i].num_comparacoes = 0;
		dados_merge[i].num_trocas = 0;
		dados_merge[i].tempo_de_execucao = 0;
	}
	DadosAmostra* dados_heap = (DadosAmostra*)malloc(sizeof(DadosAmostra) * nAmostras);
	for (i = 0; i < nAmostras; i++) {
		dados_heap[i].num_comparacoes = 0;
		dados_heap[i].num_trocas = 0;
		dados_heap[i].tempo_de_execucao = 0;
	}
	DadosAmostra* dados_quick = (DadosAmostra*)malloc(sizeof(DadosAmostra) * nAmostras);
	for (i = 0; i < nAmostras; i++) {
		dados_quick[i].num_comparacoes = 0;
		dados_quick[i].num_trocas = 0;
		dados_quick[i].tempo_de_execucao = 0;
	}

	for (i = 0; i < nAmostras; i++) {
		printf("Amostra %d\n", i + 1);
		//printf("\n **************** INSERTION **************** \n");
		vet = geraVetor(tam);
		printf("\n\nVetor gerado: ");
		//printaVetor(vet, tam);

		printf("Insertion comecou\n");

		insertionSort(vet, tam, &dados_insertion[i]);

		printf("\n\nVetor organizado: ");
		//printaVetor(vet, tam);
		printf("\n\ntempo: %f\nnum comp: %lld\ntrocas: %lld\n", dados_insertion[i].tempo_de_execucao, dados_insertion[i].num_comparacoes, dados_insertion[i].num_trocas);

		//printf("\n **************** SELECTION **************** \n");
		vet = geraVetor(tam);
		printf("\n\nVetor gerado: ");
		//printaVetor(vet, tam);

		printf("Selection comecou\n");

		selectionSort(vet, tam, &dados_selection[i]);

		printf("\n\nVetor organizado: ");
		//printaVetor(vet, tam);
		printf("\n\ntempo: %f\nnum comp: %lld\ntrocas: %lld\n", dados_selection[i].tempo_de_execucao, dados_selection[i].num_comparacoes, dados_selection[i].num_trocas);

		//printf("\n **************** MERGE **************** \n");
		vet = geraVetor(tam);
		printf("\n\nVetor gerado: ");
		//printaVetor(vet, tam);

		printf("Merge comecou\n");

		tempo1_merge = clock();
		mergeSort(vet, 0, tam - 1, &dados_merge[i]);
		tempo2_merge = clock();
		dados_merge[i].tempo_de_execucao = (double)(tempo2_merge - tempo1_merge) / CLOCKS_PER_SEC;

		printf("\n\nVetor organizado: ");
		//printaVetor(vet, tam);
		printf("\n\ntempo: %f\nnum comp: %lld\ntrocas: %lld\n", dados_merge[i].tempo_de_execucao, dados_merge[i].num_comparacoes, dados_merge[i].num_trocas);

		//printf("\n **************** HEAP **************** \n");
		vet = geraVetor(tam);
		printf("\n\nVetor gerado: ");
		//printaVetor(vet, tam);

		printf("Heap comecou\n");

		tempo1_heap = clock();
		heapSort(vet, tam, &dados_heap[i]);
		tempo2_heap = clock();
		dados_heap[i].tempo_de_execucao = (double)(tempo2_heap - tempo1_heap) / CLOCKS_PER_SEC;

		printf("\n\nVetor organizado: ");
		//printaVetor(vet, tam);
		printf("\n\ntempo: %f\nnum comp: %lld\ntrocas: %lld\n", dados_heap[i].tempo_de_execucao, dados_heap[i].num_comparacoes, dados_heap[i].num_trocas);

		//printf("\n **************** QUICK **************** \n");

		vet = geraVetor(tam);
		printf("\n\nVetor gerado: ");
		//printaVetor(vet, tam);

		printf("Quick comecou\n");
		tempo1_quick = clock();
		quickSort(vet, 0, tam - 1, &dados_quick[i]);
		tempo2_quick = clock();
		dados_quick[i].tempo_de_execucao = (double)(tempo2_quick - tempo1_quick) / CLOCKS_PER_SEC;

		printf("\n\nVetor organizado: ");
		//printaVetor(vet, tam);
		printf("\n\ntempo: %f\nnum comp: %lld\ntrocas: %lld\n", dados_quick[i].tempo_de_execucao, dados_quick[i].num_comparacoes, dados_quick[i].num_trocas);

	}

	for (i = 0; i < nAmostras; i++) {
		fprintf(fp_insertion, "[Amostra %d]\n", i + 1);
		fprintf(fp_insertion, "tempo: %f\nnum comp: %lld\ntrocas: %lld\n\n", dados_insertion[i].tempo_de_execucao, dados_insertion[i].num_comparacoes, dados_insertion[i].num_trocas);

		fprintf(fp_selection, "[Amostra %d]\n", i + 1);
		fprintf(fp_selection, "tempo: %f\nnum comp: %lld\ntrocas: %lld\n\n", dados_selection[i].tempo_de_execucao, dados_selection[i].num_comparacoes, dados_selection[i].num_trocas);

		fprintf(fp_merge, "[Amostra %d]\n", i + 1);
		fprintf(fp_merge, "tempo: %f\nnum comp: %lld\ntrocas: %lld\n\n", dados_merge[i].tempo_de_execucao, dados_merge[i].num_comparacoes, dados_merge[i].num_trocas);

		fprintf(fp_heap, "[Amostra %d]\n", i + 1);
		fprintf(fp_heap, "tempo: %f\nnum comp: %lld\ntrocas: %lld\n\n", dados_heap[i].tempo_de_execucao, dados_heap[i].num_comparacoes, dados_heap[i].num_trocas);

		fprintf(fp_quick, "[Amostra %d]\n", i + 1);
		fprintf(fp_quick, "tempo: %f\nnum comp: %lld\ntrocas: %lld\n\n", dados_quick[i].tempo_de_execucao, dados_quick[i].num_comparacoes, dados_quick[i].num_trocas);
	}

	//calcula estatisticas
	DadosSort estatisticas_insertion = calculaEstatisticas(dados_insertion, nAmostras);
	DadosSort estatisticas_selection = calculaEstatisticas(dados_selection, nAmostras);
	DadosSort estatisticas_merge = calculaEstatisticas(dados_merge, nAmostras);
	DadosSort estatisticas_heap = calculaEstatisticas(dados_heap, nAmostras);
	DadosSort estatisticas_quick = calculaEstatisticas(dados_quick, nAmostras);


	fprintf(fp_insertion, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_insertion.tempo_de_execucao.media, estatisticas_insertion.tempo_de_execucao.variancia, estatisticas_insertion.tempo_de_execucao.desvio_padrao);
	fprintf(fp_insertion, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_insertion.num_comparacoes.media, estatisticas_insertion.num_comparacoes.variancia, estatisticas_insertion.num_comparacoes.desvio_padrao);
	fprintf(fp_insertion, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_insertion.num_trocas.media, estatisticas_insertion.num_trocas.variancia, estatisticas_insertion.num_trocas.desvio_padrao);

	fprintf(fp_selection, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_selection.tempo_de_execucao.media, estatisticas_selection.tempo_de_execucao.variancia, estatisticas_selection.tempo_de_execucao.desvio_padrao);
	fprintf(fp_selection, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_selection.num_comparacoes.media, estatisticas_selection.num_comparacoes.variancia, estatisticas_selection.num_comparacoes.desvio_padrao);
	fprintf(fp_selection, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_selection.num_trocas.media, estatisticas_selection.num_trocas.variancia, estatisticas_selection.num_trocas.desvio_padrao);

	fprintf(fp_merge, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_merge.tempo_de_execucao.media, estatisticas_merge.tempo_de_execucao.variancia, estatisticas_merge.tempo_de_execucao.desvio_padrao);
	fprintf(fp_merge, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_merge.num_comparacoes.media, estatisticas_merge.num_comparacoes.variancia, estatisticas_merge.num_comparacoes.desvio_padrao);
	fprintf(fp_merge, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_merge.num_trocas.media, estatisticas_merge.num_trocas.variancia, estatisticas_merge.num_trocas.desvio_padrao);

	fprintf(fp_heap, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_heap.tempo_de_execucao.media, estatisticas_heap.tempo_de_execucao.variancia, estatisticas_heap.tempo_de_execucao.desvio_padrao);
	fprintf(fp_heap, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_heap.num_comparacoes.media, estatisticas_heap.num_comparacoes.variancia, estatisticas_heap.num_comparacoes.desvio_padrao);
	fprintf(fp_heap, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_heap.num_trocas.media, estatisticas_heap.num_trocas.variancia, estatisticas_heap.num_trocas.desvio_padrao);

	fprintf(fp_quick, "[Tempo de exec]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_quick.tempo_de_execucao.media, estatisticas_quick.tempo_de_execucao.variancia, estatisticas_quick.tempo_de_execucao.desvio_padrao);
	fprintf(fp_quick, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_quick.num_comparacoes.media, estatisticas_quick.num_comparacoes.variancia, estatisticas_quick.num_comparacoes.desvio_padrao);
	fprintf(fp_quick, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_quick.num_trocas.media, estatisticas_quick.num_trocas.variancia, estatisticas_quick.num_trocas.desvio_padrao);

	printf("\n\nInsertion:\n");
	printaEstats(estatisticas_insertion);

	printf("\nSelection:\n");
	printaEstats(estatisticas_selection);

	printf("\nMerge:\n");
	printaEstats(estatisticas_merge);

	printf("\nHeap:\n");
	printaEstats(estatisticas_heap);

	printf("\nQuick:\n");
	printaEstats(estatisticas_quick);

	fclose(fp_selection);
	fclose(fp_heap);
	fclose(fp_insertion);
	fclose(fp_quick);
	fclose(fp_merge);

	return 0;
}

int* geraVetor(long int tam)
{
	int i;
	int* vet = (int*)malloc(sizeof(int) * tam);

	for (i = 0; i < tam; i++)
		vet[i] = rand() % 100;

	return vet;
}

void printaVetor(int* vet, long int tam)
{
	int i;
	for (i = 0; i < tam; i++)
		printf("%d ", vet[i]);
}


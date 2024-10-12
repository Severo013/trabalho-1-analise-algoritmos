#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "sorts.h"
#include "auxiliar.h"

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

	printf("Entre com o numero de amostras: ");
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
		printf("\n **************** INSERTION **************** \n");
		vet = gera_vetor(tam);
		printf("\n\nVetor gerado: ");
		print_vetor(vet, tam);

		printf("\nInsertion comecou");

		insertion_sort(vet, tam, &dados_insertion[i]);

		printf("\n\nVetor organizado: ");
		print_vetor(vet, tam);
		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_insertion[i].tempo_de_execucao, dados_insertion[i].num_comparacoes, dados_insertion[i].num_trocas);

		printf("\n **************** SELECTION **************** \n");
		vet = gera_vetor(tam);
		printf("\n\nVetor gerado: ");
		print_vetor(vet, tam);

		printf("\nSelection comecou");

		selection_sort(vet, tam, &dados_selection[i]);

		printf("\n\nVetor organizado: ");
		print_vetor(vet, tam);
		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_selection[i].tempo_de_execucao, dados_selection[i].num_comparacoes, dados_selection[i].num_trocas);

		printf("\n **************** MERGE **************** \n");
		vet = gera_vetor(tam);
		printf("\n\nVetor gerado: ");
		print_vetor(vet, tam);

		printf("\nMerge comecou");

		tempo1_merge = clock();
		merge_sort(vet, 0, tam - 1, &dados_merge[i]);
		tempo2_merge = clock();
		dados_merge[i].tempo_de_execucao = (double)(tempo2_merge - tempo1_merge) / CLOCKS_PER_SEC;

		printf("\n\nVetor organizado: ");
		print_vetor(vet, tam);
		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_merge[i].tempo_de_execucao, dados_merge[i].num_comparacoes, dados_merge[i].num_trocas);

		printf("\n **************** HEAP **************** \n");
		vet = gera_vetor(tam);
		printf("\n\nVetor gerado: ");
		print_vetor(vet, tam);

		printf("\nHeap comecou");

		tempo1_heap = clock();
		heap_sort(vet, tam, &dados_heap[i]);
		tempo2_heap = clock();
		dados_heap[i].tempo_de_execucao = (double)(tempo2_heap - tempo1_heap) / CLOCKS_PER_SEC;

		printf("\n\nVetor organizado: ");
		print_vetor(vet, tam);
		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_heap[i].tempo_de_execucao, dados_heap[i].num_comparacoes, dados_heap[i].num_trocas);

		printf("\n **************** QUICK **************** \n");
		vet = gera_vetor(tam);
		printf("\n\nVetor gerado: ");
		print_vetor(vet, tam);

		printf("\nQuick comecou");
		tempo1_quick = clock();
		quick_sort(vet, 0, tam - 1, &dados_quick[i]);
		tempo2_quick = clock();
		dados_quick[i].tempo_de_execucao = (double)(tempo2_quick - tempo1_quick) / CLOCKS_PER_SEC;

		printf("\n\nVetor organizado: ");
		print_vetor(vet, tam);
		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_quick[i].tempo_de_execucao, dados_quick[i].num_comparacoes, dados_quick[i].num_trocas);

	}

	for (i = 0; i < nAmostras; i++) {
		fprintf(fp_insertion, "[Amostra %d]\n", i + 1);
		fprintf(fp_insertion, "Tempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n\n", dados_insertion[i].tempo_de_execucao, dados_insertion[i].num_comparacoes, dados_insertion[i].num_trocas);

		fprintf(fp_selection, "[Amostra %d]\n", i + 1);
		fprintf(fp_selection, "Tempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n\n", dados_selection[i].tempo_de_execucao, dados_selection[i].num_comparacoes, dados_selection[i].num_trocas);

		fprintf(fp_merge, "[Amostra %d]\n", i + 1);
		fprintf(fp_merge, "Tempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n\n", dados_merge[i].tempo_de_execucao, dados_merge[i].num_comparacoes, dados_merge[i].num_trocas);

		fprintf(fp_heap, "[Amostra %d]\n", i + 1);
		fprintf(fp_heap, "Tempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n\n", dados_heap[i].tempo_de_execucao, dados_heap[i].num_comparacoes, dados_heap[i].num_trocas);

		fprintf(fp_quick, "[Amostra %d]\n", i + 1);
		fprintf(fp_quick, "Tempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n\n", dados_quick[i].tempo_de_execucao, dados_quick[i].num_comparacoes, dados_quick[i].num_trocas);
	}

	//calcula estatisticas
	DadosSort estatisticas_insertion = calcula_estatisticas(dados_insertion, nAmostras);
	DadosSort estatisticas_selection = calcula_estatisticas(dados_selection, nAmostras);
	DadosSort estatisticas_merge = calcula_estatisticas(dados_merge, nAmostras);
	DadosSort estatisticas_heap = calcula_estatisticas(dados_heap, nAmostras);
	DadosSort estatisticas_quick = calcula_estatisticas(dados_quick, nAmostras);


	fprintf(fp_insertion, "[Tempo de execucao]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_insertion.tempo_de_execucao.media, estatisticas_insertion.tempo_de_execucao.variancia, estatisticas_insertion.tempo_de_execucao.desvio_padrao);
	fprintf(fp_insertion, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_insertion.num_comparacoes.media, estatisticas_insertion.num_comparacoes.variancia, estatisticas_insertion.num_comparacoes.desvio_padrao);
	fprintf(fp_insertion, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_insertion.num_trocas.media, estatisticas_insertion.num_trocas.variancia, estatisticas_insertion.num_trocas.desvio_padrao);

	fprintf(fp_selection, "[Tempo de execucao]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_selection.tempo_de_execucao.media, estatisticas_selection.tempo_de_execucao.variancia, estatisticas_selection.tempo_de_execucao.desvio_padrao);
	fprintf(fp_selection, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_selection.num_comparacoes.media, estatisticas_selection.num_comparacoes.variancia, estatisticas_selection.num_comparacoes.desvio_padrao);
	fprintf(fp_selection, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_selection.num_trocas.media, estatisticas_selection.num_trocas.variancia, estatisticas_selection.num_trocas.desvio_padrao);

	fprintf(fp_merge, "[Tempo de execucao]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_merge.tempo_de_execucao.media, estatisticas_merge.tempo_de_execucao.variancia, estatisticas_merge.tempo_de_execucao.desvio_padrao);
	fprintf(fp_merge, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_merge.num_comparacoes.media, estatisticas_merge.num_comparacoes.variancia, estatisticas_merge.num_comparacoes.desvio_padrao);
	fprintf(fp_merge, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_merge.num_trocas.media, estatisticas_merge.num_trocas.variancia, estatisticas_merge.num_trocas.desvio_padrao);

	fprintf(fp_heap, "[Tempo de execucao]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_heap.tempo_de_execucao.media, estatisticas_heap.tempo_de_execucao.variancia, estatisticas_heap.tempo_de_execucao.desvio_padrao);
	fprintf(fp_heap, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_heap.num_comparacoes.media, estatisticas_heap.num_comparacoes.variancia, estatisticas_heap.num_comparacoes.desvio_padrao);
	fprintf(fp_heap, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_heap.num_trocas.media, estatisticas_heap.num_trocas.variancia, estatisticas_heap.num_trocas.desvio_padrao);

	fprintf(fp_quick, "[Tempo de execucao]\nMedia: %f\nVariancia: %f\nDP: %f\n\n", estatisticas_quick.tempo_de_execucao.media, estatisticas_quick.tempo_de_execucao.variancia, estatisticas_quick.tempo_de_execucao.desvio_padrao);
	fprintf(fp_quick, "[Comparacoes]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_quick.num_comparacoes.media, estatisticas_quick.num_comparacoes.variancia, estatisticas_quick.num_comparacoes.desvio_padrao);
	fprintf(fp_quick, "[Trocas]\nMedia: %f\nVariancia: %f\nDP: %f\n\n",
		estatisticas_quick.num_trocas.media, estatisticas_quick.num_trocas.variancia, estatisticas_quick.num_trocas.desvio_padrao);

	printf("\n\nInsertion:\n");
	print_dados_sort(estatisticas_insertion);

	printf("\nSelection:\n");
	print_dados_sort(estatisticas_selection);

	printf("\nMerge:\n");
	print_dados_sort(estatisticas_merge);

	printf("\nHeap:\n");
	print_dados_sort(estatisticas_heap);

	printf("\nQuick:\n");
	print_dados_sort(estatisticas_quick);

	fclose(fp_selection);
	fclose(fp_heap);
	fclose(fp_insertion);
	fclose(fp_quick);
	fclose(fp_merge);

	return 0;
}

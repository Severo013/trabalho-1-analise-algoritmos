#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "sorts.h"
#include "auxiliar.h"

int main()
{
	int* vet;
	int* vet_to_sort;
	long int tam;
	int resp;

	clock_t tempo1_merge, tempo2_merge;
	clock_t tempo1_heap, tempo2_heap;
	clock_t tempo1_quick, tempo2_quick;

	srand(time(NULL));

	printf("Quer salvar as respostas/dados em arquivos? (1: sim, 2: não) ");
	scanf("%d", &resp);
	if (resp != 1 && resp != 2) {
		printf("Opção não encontrada. Responder apenas 1 ou 2.\n");
		return 0;
	}

	printf("Insira o tamanho do vetor: ");
	scanf("%ld", &tam);

	vet = cria_vetor(tam);
	vet_to_sort = cria_vetor(tam);

	char filename_insertion[50];
	char filename_selection[50];
	char filename_merge[50];
	char filename_heap[50];
	char filename_quick[50];

	FILE* fp_insertion;
	FILE* fp_selection;
	FILE* fp_merge;
	FILE* fp_heap;
	FILE* fp_quick;

	if (resp == 1) {
		sprintf(filename_insertion, "insertion%ld.txt", tam);
		sprintf(filename_selection, "selection%ld.txt", tam);
		sprintf(filename_heap, "heap%ld.txt", tam);
		sprintf(filename_merge, "merge%ld.txt", tam);
		sprintf(filename_quick, "quick%ld.txt", tam);

		fp_insertion = fopen(filename_insertion, "w+");
		fp_selection = fopen(filename_selection, "w+");
		fp_merge = fopen(filename_merge, "w+");
		fp_heap = fopen(filename_heap, "w+");
		fp_quick = fopen(filename_quick, "w+");
	}

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
		printf("\n\n--------------------------------------------------------------------------------------\n");
		printf("AMOSTRA %d\n", i + 1);
		gera_vetor(tam, vet);
		//printf("\n\nVetor gerado: ");
		//print_vetor(vet, tam);
		printf("\n **************** INSERTION **************** \n");
		copy_vetor(tam, vet, vet_to_sort);

		printf("\nInsertion comecou");

		insertion_sort(vet_to_sort, tam, &dados_insertion[i]);
		//printf("\n\nVetor organizado: ");
		//print_vetor(vet_to_sort, tam);

		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_insertion[i].tempo_de_execucao, dados_insertion[i].num_comparacoes, dados_insertion[i].num_trocas);

		printf("\n **************** SELECTION **************** \n");
		copy_vetor(tam, vet, vet_to_sort);

		printf("\nSelection comecou");

		selection_sort(vet_to_sort, tam, &dados_selection[i]);
		//printf("\n\nVetor organizado: ");
		//print_vetor(vet_to_sort, tam);

		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_selection[i].tempo_de_execucao, dados_selection[i].num_comparacoes, dados_selection[i].num_trocas);

		printf("\n **************** MERGE **************** \n");
		copy_vetor(tam, vet, vet_to_sort);

		printf("\nMerge comecou");

		tempo1_merge = clock();
		merge_sort(vet_to_sort, 0, tam - 1, &dados_merge[i]);
		tempo2_merge = clock();
		dados_merge[i].tempo_de_execucao = (double)(tempo2_merge - tempo1_merge) / CLOCKS_PER_SEC;
		//printf("\n\nVetor organizado: ");
		//print_vetor(vet_to_sort, tam);

		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_merge[i].tempo_de_execucao, dados_merge[i].num_comparacoes, dados_merge[i].num_trocas);

		printf("\n **************** HEAP **************** \n");
		copy_vetor(tam, vet, vet_to_sort);

		printf("\nHeap comecou");

		tempo1_heap = clock();
		heap_sort(vet_to_sort, tam, &dados_heap[i]);
		tempo2_heap = clock();
		dados_heap[i].tempo_de_execucao = (double)(tempo2_heap - tempo1_heap) / CLOCKS_PER_SEC;
		//printf("\n\nVetor organizado: ");
		//print_vetor(vet_to_sort, tam);

		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_heap[i].tempo_de_execucao, dados_heap[i].num_comparacoes, dados_heap[i].num_trocas);

		printf("\n **************** QUICK **************** \n");
		copy_vetor(tam, vet, vet_to_sort);

		printf("\nQuick comecou");
		tempo1_quick = clock();
		quick_sort(vet_to_sort, 0, tam - 1, &dados_quick[i]);
		tempo2_quick = clock();
		dados_quick[i].tempo_de_execucao = (double)(tempo2_quick - tempo1_quick) / CLOCKS_PER_SEC;
		//printf("\n\nVetor organizado: ");
		//print_vetor(vet_to_sort, tam);

		printf("\n\nTempo: %f\nNum. Comparacoes: %lld\nNum. Trocas: %lld\n", dados_quick[i].tempo_de_execucao, dados_quick[i].num_comparacoes, dados_quick[i].num_trocas);
	}

	if (resp == 1) {
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
	}

	//calcula estatisticas
	DadosSort estatisticas_insertion = calcula_estatisticas(dados_insertion, nAmostras);
	DadosSort estatisticas_selection = calcula_estatisticas(dados_selection, nAmostras);
	DadosSort estatisticas_merge = calcula_estatisticas(dados_merge, nAmostras);
	DadosSort estatisticas_heap = calcula_estatisticas(dados_heap, nAmostras);
	DadosSort estatisticas_quick = calcula_estatisticas(dados_quick, nAmostras);

	if (resp == 1) {
		print_file_dados_sort(fp_insertion, estatisticas_insertion);
		print_file_dados_sort(fp_selection, estatisticas_selection);
		print_file_dados_sort(fp_merge, estatisticas_merge);
		print_file_dados_sort(fp_heap, estatisticas_heap);
		print_file_dados_sort(fp_quick, estatisticas_quick);
	}

	// printf("\n\nInsertion:\n");
	// print_dados_sort(estatisticas_insertion);

	// printf("\nSelection:\n");
	// print_dados_sort(estatisticas_selection);

	// printf("\nMerge:\n");
	// print_dados_sort(estatisticas_merge);

	// printf("\nHeap:\n");
	// print_dados_sort(estatisticas_heap);

	// printf("\nQuick:\n");
	// print_dados_sort(estatisticas_quick);

	printf("\n\n---------------------------------------------------------------------------------------------------------------------------\n");
	printf("|                                                   ANALISE ESTATÍSTICA                                                   |\n");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("|        MÉTODO        |       TEMPO DE EXECUÇÃO        |           COMPARAÇÕES          |             TROCAS             |\n");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("|       Insertion      |"); print_linha_tabela_dados_sort(estatisticas_insertion);
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("|       Selection      |"); print_linha_tabela_dados_sort(estatisticas_selection);
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("|         Merge        |"); print_linha_tabela_dados_sort(estatisticas_merge);
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("|         Heap         |"); print_linha_tabela_dados_sort(estatisticas_heap);
	printf("---------------------------------------------------------------------------------------------------------------------------\n");
	printf("|         Quick        |"); print_linha_tabela_dados_sort(estatisticas_quick);
	printf("---------------------------------------------------------------------------------------------------------------------------\n");

	free(vet);
	free(vet_to_sort);

	if (resp == 1) {
		fclose(fp_selection);
		fclose(fp_heap);
		fclose(fp_insertion);
		fclose(fp_quick);
		fclose(fp_merge);
	}

	return 0;
}

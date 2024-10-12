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

//============== Auxiliares ==============//
int* geraVetor(long int tam);
void printaVetor(int* vet, long int tam);

//============== Sorts ==============//
//Insertion
void insertionSort(int* vet, long int tam, DadosAmostra* dado);

//Selection
void selectionSort(int* vet, int long tam, DadosAmostra* dado);

//Merge
void mergeSort(int* vet, int comeco, int fim, DadosAmostra* dados);
void intercala(int* vet, int comeco, int meio, int fim, DadosAmostra* dados);

//Heap
void maxHeapify(int* vet, long int tam, int i, DadosAmostra* dados);
void heapSort(int* vet, long int tam, DadosAmostra* dados);

//Quick
int partition(int* vet, int p, long int r, DadosAmostra* dados);
void quickSort(int* vet, int p, long int r, DadosAmostra* dados);
//===================================//
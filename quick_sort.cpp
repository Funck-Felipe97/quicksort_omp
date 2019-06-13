#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define TAMANHO_VETOR 200000
#define NUMERO_THREADS 4
#define LIMITE_PARALELO 1000

void imprimir_vetor(int *vetor) {
   for (int i = 0; i < TAMANHO_VETOR; ++i) {
       printf("%d ", vetor[i]);
    }
}

void iniciar_vetor(int *vetor_sequencial, int *vetor_paralelo) {
   for (int i = 0; i < TAMANHO_VETOR; ++i) {
		vetor_sequencial[i] = rand() % 1000;
      vetor_paralelo[i] = vetor_sequencial[i];
   }
}

void quick_sequencial(int *vetor, int inicio, int fim) {
   
   int pivo, aux, i, j, meio;
   
   i = inicio;
   j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];
   
   do {
      while (vetor[i] < pivo) i = i + 1;
      while (vetor[j] > pivo) j = j - 1;
      
      if(i <= j) {
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   } while(j > i);

   if(inicio < j) quick_sequencial(vetor, inicio, j);
   if(i < fim) quick_sequencial(vetor, i, fim);   

}

void quick_paralelo(int *vetor, int inicio, int fim) {
   
   int pivo, aux, i, j, meio;
   
   i = inicio;
   j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];
   
   do {
      while (vetor[i] < pivo) i = i + 1;
      while (vetor[j] > pivo) j = j - 1;
      
      if(i <= j) {
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   } while(j > i);

   if (fim - inicio < LIMITE_PARALELO) {
      if(inicio < j) quick_paralelo(vetor, inicio, j);
      if(i < fim) quick_paralelo(vetor, i, fim);
   } else {
      #pragma omp task
      { if(inicio < j) quick_paralelo(vetor, inicio, j); }

      #pragma omp task
      { if(i < fim) quick_paralelo(vetor, i, fim); }   
   }

}

void teste_sequencial(int *vetor_sequencial) {
   clock_t tempo;
   printf("\n10 primeiros numeros sequencial desordenados: ");
   for(int i = 0; i < 10; ++i) {
      printf("%d ", vetor_sequencial[i]);
   }

   tempo = clock();
   quick_sequencial(vetor_sequencial, 0, TAMANHO_VETOR - 1);
   printf("\nTempo sequencial: (%f) segundos\n", (clock() - tempo) / (double)CLOCKS_PER_SEC);

   printf("10 primeiros numeros sequencial ordenados: ");
   for(int i = 0; i < 10; ++i) {
      printf("%d ", vetor_sequencial[i]);
   }
}

void teste_paralelo(int *vetor_paralelo) {
   clock_t tempo;
   printf("\n\n10 primeiros numeros paralelos desordenados: ");
   for(int i = 0; i < 10; ++i) {
      printf("%d ", vetor_paralelo[i]);
   }

   tempo = clock();
    #pragma omp parallel num_threads(NUMERO_THREADS)
	{	
		#pragma omp single nowait
		{
			quick_paralelo(vetor_paralelo, 0, TAMANHO_VETOR - 1);	
         printf("\nTempo paralelo: (%f) segundos\n", (clock() - tempo) / (double)CLOCKS_PER_SEC);
		}
	}
   printf("10 primeiros numeros paralelos ordenados: ");
   for(int i = 0; i < 10; ++i) {
      printf("%d ", vetor_paralelo[i]);
   }	
   printf("\n");
}

int main() {
    int vetor_sequencial[TAMANHO_VETOR];
    int vetor_paralelo[TAMANHO_VETOR];

    iniciar_vetor(vetor_sequencial, vetor_paralelo);
    teste_sequencial(vetor_sequencial);
    teste_paralelo(vetor_paralelo);
}

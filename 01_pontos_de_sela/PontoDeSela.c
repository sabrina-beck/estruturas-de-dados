/* Programa: conta.c                                   */
/* Autor: Sabrina Beck Angelini           RA157240     */
/* Disciplina: MC102                      Turma E      */
/* Data: 06/set/2014                                   */

#include <stdio.h>
#include <stdlib.h>

int lerDimensao();
int** lerMatriz(int n);
void escrevePontosDeSela(int** matriz, int n);

typedef enum bool {
	false, true
} bool;

int main() {
	int n;
	int** matriz;

	n = lerDimensao();
	matriz = lerMatriz(n);

	escrevePontosDeSela(matriz, n);

	return 0;
}

int lerDimensao() {
	int n;
	char caracter;

	scanf("%d", &n);
	if (n < 1 || n > 20) {
		printf("Dados inválidos");
		exit(0);
	}

	do {
		scanf("%c", &caracter);
	} while (caracter != '\n'); 

	return n;
}

int** lerMatriz(int n) {
	int** matriz;
	int i, j;
	char caracter;
	matriz = (int**) malloc(n * sizeof(int*));

	for(i = 0; i < n; i++) {
		matriz[i] = (int*) malloc(n * sizeof(int));
	}

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			scanf("%d", &matriz[i][j]);
			scanf("%c", &caracter);
		}

		while (caracter != '\n') {
			scanf("%c", &caracter);
		}
	}

	return matriz;
}

int indiceMenorElemento(int* vetor, int n) {
	int i, menor = vetor[0], indice = 0;
	for(i = 1; i < n; i++) {
		if(menor > vetor[i]) {
			menor = vetor[i];
			indice = i;
		}
	}
	return indice;
} 

bool ehMaiorDaColuna(int** matriz, int n, int linha, int coluna) {
	int i, maior = matriz[0][coluna], indice = 0;

	for(i = 0; i < n; i++)
		if(matriz[i][coluna] > maior) {
			maior = matriz[i][coluna];
			indice = i;
		}
	if(linha == indice)
		return true;

	return false;
}

void escrevePontosDeSela(int** matriz, int n) {
	int i;
	bool achouAlgum = false;

	printf("Os pontos de sela da matriz são:\n\n");

	for(i = 0; i < n; i++) {
		int colunaDoMenor = indiceMenorElemento(matriz[i], n);
		//FIXME
		//printf("\nMenor da linha %d é %d\n", i, matriz[i][colunaDoMenor]);
		bool pontoDeSela = ehMaiorDaColuna(matriz, n,  i, colunaDoMenor);
		//FIXME 
		//printf("É maior da coluna %d ? %d\n\n", colunaDoMenor, pontoDeSela);
		if(pontoDeSela) {
			achouAlgum = true;
			printf("%4d%4d%4d\n ", i, colunaDoMenor, matriz[i][colunaDoMenor]);
		}
	}

	if(!achouAlgum)
		printf("nenhum");
	printf("\n");
}


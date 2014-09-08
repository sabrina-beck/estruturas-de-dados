/* Programa: conta.c                                   */
/* Autor: Sabrina Beck Angelini           RA157240     */
/* Disciplina: MC102                      Turma E      */
/* Data: 06/set/2014                                   */

#include <stdio.h>
#include <stdlib.h>

int lerDimensao();
int** lerMatriz(int n);

//FIXME retirar isso
void escreve(int** matriz, int n) {
	int i, j;
	printf("%d\n", n);

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++)
			printf("%d ", matriz[i][j]);
		printf("\n");
	}
}

int main() {
	int n;
	int** matriz;

	n = lerDimensao();
	matriz = lerMatriz(n);

	escreve(matriz, n);

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

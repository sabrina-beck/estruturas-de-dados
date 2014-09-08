/* Programa: conta.c                                   */
/* Autor: Sabrina Beck Angelini           RA157240     */
/* Disciplina: MC202                      Turma E      */
/* Data: 06/set/2014                                   */

#include <stdio.h>
#include <stdlib.h>

int lerDimensao();
int** lerMatriz(int n);
void escrevePontosDeSela(int** matriz, int n);

typedef enum bool {
	false, true
} bool;

typedef struct Coordenada {
	int linha;
	int coluna;
} Coordenada;

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

Coordenada posicaoDoMenorDaLinha(int** matriz, int n, int linha) {
	int i;
	int menor = matriz[linha][0];
	Coordenada coordenadaDoMenor;
	coordenadaDoMenor.linha = linha;
	coordenadaDoMenor.coluna = 0;

	for(i = 1; i < n; i++)
		if(menor > matriz[linha][i]) {
			menor = matriz[linha][i];
			coordenadaDoMenor.coluna = i;
		}
	return coordenadaDoMenor;
}

Coordenada posicaoDoMaiorDaColuna(int** matriz, int n, int coluna) {
	int i;
	int maior = matriz[0][coluna];
	Coordenada coordenadaDoMaior;
	coordenadaDoMaior.linha = 0;
	coordenadaDoMaior.coluna = coluna;

	for(i = 1; i < n; i++)
		if(maior < matriz[i][coluna]) {
			maior = matriz[i][coluna];
			coordenadaDoMaior.linha = i;
		}

	return coordenadaDoMaior;
}

void escrevePontosDeSela(int** matriz, int n) {
	int i, j;
	bool temPontosDeSela = false;
	Coordenada *menoresPorLinha, *maioresPorColuna;
	menoresPorLinha = (Coordenada*) malloc(n * sizeof(Coordenada));
	maioresPorColuna = (Coordenada*) malloc(n * sizeof(Coordenada));

	printf("Os pontos de sela da matriz são:\n\n");

	for(i = 0; i < n; i++) {
		menoresPorLinha[i] = posicaoDoMenorDaLinha(matriz, n, i);
		maioresPorColuna[i] = posicaoDoMaiorDaColuna(matriz, n, i);
	}

	for(i = 0; i < n; i++) {
		Coordenada menorLinha = menoresPorLinha[i];
		for(j = 0; j < n; j++) {
			Coordenada maiorColuna = maioresPorColuna[j];
			if(maiorColuna.linha == menorLinha.linha && maiorColuna.coluna == menorLinha.coluna) {
				int linha = maiorColuna.linha;
				int coluna = maiorColuna.coluna;
				printf("%4d%4d%4d\n", maiorColuna.linha, maiorColuna.coluna, matriz[linha][coluna]);
				temPontosDeSela = true;
			}
		}
	}

	if(!temPontosDeSela)
		printf("nenhum");

	printf("\n");
}


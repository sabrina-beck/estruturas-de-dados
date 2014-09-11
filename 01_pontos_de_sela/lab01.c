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
	
	free(matriz);

	return 0;
}

int lerDimensao() {
	int n;
	char caracter;

	scanf("%d", &n);
	if (n < 1 || n > 20) {
		printf("Dados inválidos\n");
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
			int qtdLido = scanf("%d", &matriz[i][j]);
			if(qtdLido <= 0) {
		        printf("Dados inválidos\n");
		        exit(0);
	        }

			scanf("%c", &caracter);
		}

		while (caracter != '\n') {
			scanf("%c", &caracter);
		}
	}

	return matriz;
}

void posicoesDoMenorDaLinha(int** matriz, int n, int linha, Coordenada* resultados, int* qtdResultados) {
    Coordenada coordAtual;
	int i, qtd;
	int menor = matriz[linha][0];

    coordAtual.linha = linha;
    coordAtual.coluna = 0;
	resultados[(*qtdResultados)++] = coordAtual;
	qtd = 1;

	for(i = 1; i < n; i++) {
	    coordAtual.coluna = i;
		if(menor > matriz[linha][i]) {
			menor = matriz[linha][i];
			*qtdResultados -= qtd;
            resultados[(*qtdResultados)++] = coordAtual;
			qtd = 1;
		} else if(menor == matriz[linha][i]) {
		    resultados[(*qtdResultados)++] = coordAtual;
		    qtd++;
		}
	}
}

void posicoesDoMaiorDaColuna(int** matriz, int n, int coluna, Coordenada* resultados, int* qtdResultados) {
    Coordenada coordAtual;
	int i, qtd;
	int maior = matriz[0][coluna];
	
	coordAtual.linha = 0;
	coordAtual.coluna = coluna;
	resultados[(*qtdResultados)++] = coordAtual;
	qtd = 1;

	for(i = 1; i < n; ++i) {
	    coordAtual.linha = i;
		if(maior < matriz[i][coluna]) {
			maior = matriz[i][coluna];
			*qtdResultados -= qtd;
			resultados[(*qtdResultados)++] = coordAtual;
			qtd = 1;
		} else if(maior == matriz[i][coluna]) {
		    resultados[(*qtdResultados)++] = coordAtual;
		    qtd++;
		}
		
	}
}

void escrevePontosDeSela(int** matriz, int n) {
	int i, j, qtdMenores = 0, qtdMaiores = 0;
	bool temPontosDeSela = false;
	Coordenada *menoresPorLinha, *maioresPorColuna;
	menoresPorLinha = (Coordenada*) malloc(n * n * sizeof(Coordenada));
	maioresPorColuna = (Coordenada*) malloc(n * n * sizeof(Coordenada));

	printf("Os pontos de sela da matriz são:\n\n");

	for(i = 0; i < n; i++) {
		posicoesDoMenorDaLinha(matriz, n, i, menoresPorLinha, &qtdMenores);
		posicoesDoMaiorDaColuna(matriz, n, i, maioresPorColuna, &qtdMaiores);
	}


	for(i = 0; i < qtdMenores; i++) {
		Coordenada menorLinha = menoresPorLinha[i];
		for(j = 0; j < qtdMaiores; j++) {
			Coordenada maiorColuna = maioresPorColuna[j];
			if(maiorColuna.linha == menorLinha.linha && maiorColuna.coluna == menorLinha.coluna) {
				int linha = maiorColuna.linha;
				int coluna = maiorColuna.coluna;
				printf("%4d%4d%4d\n", maiorColuna.linha, maiorColuna.coluna, matriz[linha][coluna]);
				temPontosDeSela = true;
			}
		}
	}
	
	free(menoresPorLinha);
	free(maioresPorColuna);

	if(!temPontosDeSela)
		printf("    nenhum\n");

}


/* Programa: selas.c                                   */
/* Autor: Sabrina Beck Angelini           RA157240     */
/* Disciplina: MC202                      Turma E      */
/* Data: 11/set/2014                                   */

#include <stdio.h>
#include <stdlib.h>

#define MSG_INVALIDA "Dados inv�lidos\n"
#define NENHUM "    nenhum\n"
/** DECLARA��ES **/

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

/** FUN��O PRINCIPAL **/

int main() {
	int n;
	int** matriz;

	n = lerDimensao();
	matriz = lerMatriz(n);

	escrevePontosDeSela(matriz, n);
	
	free(matriz);

	return 0;
}

/** FUN��ES **/

/*
 * Exibe a mensagem padr�o para dados de entrada inv�lidos
 */
void entradaInvalida() {
	printf(MSG_INVALIDA);
	exit(0);
}

/*
 * Faz a leitura dos dados de rascunho presentes na entrada
 * Precisa do �ltimo caracter lido para n�o confundir um 
 * dado de verdade com rascunho
 */
void lerRascunho(char ultimoCaracterLido) {
	while (ultimoCaracterLido != '\n') {
		scanf("%c", &ultimoCaracterLido);
	}
}

/*
 * Aloca mem�ria din�mica para uma matriz de dimens�o nxm
 */
int** aloca(int n, int m) {
    int i;
	int** matriz = (int**) malloc(n * sizeof(int*));

	for(i = 0; i < n; i++) {
		matriz[i] = (int*) malloc(m * sizeof(int));
	}
	
	return matriz;
}

/*
 * Faz a leitura das dimens�es da matriz de entrada, 
 * considerando que a matriz � nxn
 */
int lerDimensao() {
	int n;
	char caracter = '\0';

    /* Leitura da dimens�o n da matriz */
	int conseguiuLer = scanf("%d", &n);
	
	/* Verifica��o se a dimens�o dada � v�lida */
	if (n < 1 || n > 20 || conseguiuLer == EOF) {
        entradaInvalida();
	}

    /*
     * L� o rascunho da primeira linha da entrada, n�o h�
     * necessidade da leitura de um caracter previamente, pois
     * nenhum caracter foi lido depois da leitura de n, ent�o n�o
     * corre o risco de j� ter lido o '\n' da primeira linha e a
     * segunda linha ser lida como rascunho
     */
    lerRascunho(caracter);

	return n;
}

/*
 * Faz a leitura de uma matriz nxn considerando a possibilidade
 * de rascunho ap�s cada linha lida
 */
int** lerMatriz(int n) {
	int** matriz = aloca(n, n); /* aloca uma matriz nxn de inteiros */
	int i, j;
	char caracter;

    /*
     * L� n*n valores inteiros e os armazena em uma matriz
     */
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			int qtdLido = scanf("%d", &matriz[i][j]);
			
			/*
			 * Se n�o h� valores suficientes na entrada para preencher
			 * a matriz nxn ent�o a entrada � inv�lida
			 */
			if(qtdLido <= 0 || qtdLido == EOF) {
                entradaInvalida();
	        }

            /*
             * L� o espa�o entre os valores da matriz
             * Pode vir a ler um \n ou o primeiro caracter de um rascunho
             */
			scanf("%c", &caracter);
		}

        /* Termina de ler o rascunho da linha atual da entrada */
        lerRascunho(caracter);
	}

	return matriz;
}

/*
 * Armazena no final do vetor de Coordenadas resultados as coordenadas dos
 * menores elementos presentes na linha dada de uma matriz
 */
void posicoesDoMenorDaLinha(int** matriz, int n, int linha, Coordenada* resultados, int* qtdResultados) {
    Coordenada coordAtual;
	int i, qtd;
	int menor = matriz[linha][0];

    /* O valor da posi��o (0,0) � o menor encontrado at� agora */
    coordAtual.linha = linha;
    coordAtual.coluna = 0;
	resultados[(*qtdResultados)++] = coordAtual;
	qtd = 1;

    /* Percorre a linha procurando o menor valor */
	for(i = 1; i < n; i++) {
	    coordAtual.coluna = i;
		if(menor > matriz[linha][i]) {
			menor = matriz[linha][i];

			/*
			 * Armazena as coordenadas do menor valor encontrado no vetor de resultados
			 * Limpando o vetor de resultados, uma vez que o valor anteriormente armazenado
			 * n�o � o menor da linha
			 */
			*qtdResultados -= qtd;
            resultados[(*qtdResultados)++] = coordAtual;
			qtd = 1;
		} else if(menor == matriz[linha][i]) {
			/* Caso o menor valor se repita armazena as coordenadas de todas as ocorr�ncias */
		    resultados[(*qtdResultados)++] = coordAtual;
		    qtd++;
		}
	}
}

/*
 * Verifica se o elemento da coordenada dada � o maior de sua coluna
 */
bool ehMaiorDaColuna(int** matriz, int n, Coordenada coord) {
	int i;
	int maior = matriz[0][coord.coluna];
	
    /* Percorre a coluna procurando o maior valor */
	for(i = 1; i < n; ++i) {
		if(maior < matriz[i][coord.coluna]) {
			maior = matriz[i][coord.coluna];
		}
	}
	
	return matriz[coord.linha][coord.coluna] >= maior;
}

/*
 * Escreve na tela todos os pontos de sela de uma matriz nxn
 */
void escrevePontosDeSela(int** matriz, int n) {
	int i, qtdMenores = 0;
	bool temPontosDeSela = false;
	
	/*
	 * Aloca��o do vetor auxiliar que armazenar� as
	 * coordenadas dos menores elementos de cada linha
	 */
	Coordenada *menoresPorLinha;
	menoresPorLinha = (Coordenada*) malloc(n * n * sizeof(Coordenada));

	printf("Os pontos de sela da matriz s�o:\n\n");

    /*
     * Encontra as coordenadas dos menores elementos de cada linha
     */
	for(i = 0; i < n; i++) {
		posicoesDoMenorDaLinha(matriz, n, i, menoresPorLinha, &qtdMenores);
	}

    /*
     * Percorre o vetor auxiliar verificando se cada uma coordenadas representa tamb�m
     * o maior elemento de sua coluna, nesse caso � um ponto de sela
     */
	for(i = 0; i < qtdMenores; i++) {
		if(ehMaiorDaColuna(matriz, n, menoresPorLinha[i])) {
			int linha = menoresPorLinha[i].linha;
			int coluna = menoresPorLinha[i].coluna;
			printf("%4d%4d%4d\n", linha, coluna, matriz[linha][coluna]);
			temPontosDeSela = true;
		}
	}
	
	free(menoresPorLinha);

    /*
     * N�o encontrando nenhum ponto de sela em uma matriz � exibida
     * uma mensagem padr�o
     */
	if(!temPontosDeSela)
		printf(NENHUM);

}


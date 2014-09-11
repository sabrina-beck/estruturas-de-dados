/* Programa: conta.c                                   */
/* Autor: Sabrina Beck Angelini           RA157240     */
/* Disciplina: MC202                      Turma E      */
/* Data: 11/set/2014                                   */

#include <stdio.h>
#include <stdlib.h>

#define MSG_INVALIDA "Dados inválidos\n"
#define NENHUM "    nenhum\n"
/** DECLARAÇÕES **/

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

/** FUNÇÃO PRINCIPAL **/

int main() {
	int n;
	int** matriz;

	n = lerDimensao();
	matriz = lerMatriz(n);

	escrevePontosDeSela(matriz, n);
	
	free(matriz);

	return 0;
}

/** FUNÇÕES **/

/*
 * Exibe a mensagem padrão para dados de entrada inválidos
 */
void entradaInvalida() {
	printf(MSG_INVALIDA);
	exit(0);
}

/*
 * Faz a leitura dos dados de rascunho presentes na entrada
 * Precisa do último caracter lido para não confundir um 
 * dado de verdade com rascunho
 */
void lerRascunho(char ultimoCaracterLido) {
	while (ultimoCaracterLido != '\n') {
		scanf("%c", &ultimoCaracterLido);
	}
}

/*
 * Aloca memória dinâmica para uma matriz de dimensão nxm
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
 * Faz a leitura das dimensões da matriz de entrada, 
 * considerando que a matriz é nxn
 */
int lerDimensao() {
	int n;
	char caracter = '\0';

    /* Leitura da dimensão n da matriz */
	scanf("%d", &n);
	
	/* Verificação se a dimensão dada é válida */
	if (n < 1 || n > 20) {
        entradaInvalida();
	}

    /*
     * Lê o rascunho da primeira linha da entrada, não há
     * necessidade da leitura de um caracter previamente, pois
     * nenhum caracter foi lido depois da leitura de n, então não
     * corre o risco de já ter lido o '\n' da primeira linha e a
     * segunda linha ser lida como rascunho
     */
    lerRascunho(caracter);

	return n;
}

/*
 * Faz a leitura de uma matriz nxn considerando a possibilidade
 * de rascunho após cada linha lida
 */
int** lerMatriz(int n) {
	int** matriz = aloca(n, n); /* aloca uma matriz nxn de inteiros */
	int i, j;
	char caracter;

    /*
     * Lê n*n valores inteiros e os armazena em uma matriz
     */
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			int qtdLido = scanf("%d", &matriz[i][j]);
			
			/*
			 * Se não há valores suficientes na entrada para preencher
			 * a matriz nxn então a entrada é inválida
			 */
			if(qtdLido <= 0) {
                entradaInvalida();
	        }

            /*
             * Lê o espaço entre os valores da matriz
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

    /* O valor da posição (0,0) é o menor encontrado até agora */
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
			 * não é o menor da linha
			 */
			*qtdResultados -= qtd;
            resultados[(*qtdResultados)++] = coordAtual;
			qtd = 1;
		} else if(menor == matriz[linha][i]) {
			/* Caso o menor valor se repita armazena as coordenadas de todas as ocorrências */
		    resultados[(*qtdResultados)++] = coordAtual;
		    qtd++;
		}
	}
}

/*
 * Armazena no final do vetor de Coordenadas resultados as coordenadas dos
 * maiores elementos presentes na coluna dada de uma matriz
 */
void posicoesDoMaiorDaColuna(int** matriz, int n, int coluna, Coordenada* resultados, int* qtdResultados) {
    Coordenada coordAtual;
	int i, qtd;
	int maior = matriz[0][coluna];
	
	coordAtual.linha = 0;
	coordAtual.coluna = coluna;
	resultados[(*qtdResultados)++] = coordAtual;
	qtd = 1;
	
    /* Percorre a coluna procurando o maior valor */
	for(i = 1; i < n; ++i) {
	    coordAtual.linha = i;
		if(maior < matriz[i][coluna]) {
			maior = matriz[i][coluna];
			
			/*
			 * Armazena as coordenadas do maior valor encontrado no vetor de resultados
			 * Limpando o vetor de resultados, uma vez que o valor anteriormente armazenado
			 * não é o maior da coluna
			 */
			*qtdResultados -= qtd;
			resultados[(*qtdResultados)++] = coordAtual;
			qtd = 1;
		} else if(maior == matriz[i][coluna]) {
    		/* Caso o maior valor se repita armazena as coordenadas de todas as ocorrências */
		    resultados[(*qtdResultados)++] = coordAtual;
		    qtd++;
		}
		
	}
}

/*
 * Escreve na tela todos os pontos de sela de uma matriz nxn
 */
void escrevePontosDeSela(int** matriz, int n) {
	int i, j, qtdMenores = 0, qtdMaiores = 0;
	bool temPontosDeSela = false;
	
	/*
	 * Alocação de vetores auxiliares que armazenarão as
	 * coordenadas dos menores elementos de cada linha e
	 * dos maiores elementos de cada coluna
	 */
	Coordenada *menoresPorLinha, *maioresPorColuna;
	menoresPorLinha = (Coordenada*) malloc(n * n * sizeof(Coordenada));
	maioresPorColuna = (Coordenada*) malloc(n * n * sizeof(Coordenada));

	printf("Os pontos de sela da matriz são:\n\n");

    /*
     * Encontra as coordenadas dos menores elementos de cada linha
     * e dos maiores elementos de cada coluna
     */
	for(i = 0; i < n; i++) {
		posicoesDoMenorDaLinha(matriz, n, i, menoresPorLinha, &qtdMenores);
		posicoesDoMaiorDaColuna(matriz, n, i, maioresPorColuna, &qtdMaiores);
	}

    /*
     * Percorre os vetores auxiliares
     */
	for(i = 0; i < qtdMenores; i++) {
		Coordenada menorLinha = menoresPorLinha[i];
		for(j = 0; j < qtdMaiores; j++) {
			Coordenada maiorColuna = maioresPorColuna[j];
			/*
			 * Se a mesma coordenada se repetir em ambos os vetores auxlizares,
			 * então esse é um ponto de sela
			 */
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

    /*
     * Não encontrando nenhum ponto de sela em uma matriz é exibida
     * uma mensagem padrão
     */
	if(!temPontosDeSela)
		printf(NENHUM);

}


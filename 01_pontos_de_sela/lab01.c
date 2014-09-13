/* Programa: selas.c                                   */
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
	int conseguiuLer = scanf("%d", &n);
	
	/* Verificação se a dimensão dada é válida */
	if (n < 1 || n > 20 || conseguiuLer == EOF) {
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
			if(qtdLido <= 0 || qtdLido == EOF) {
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
 * Verifica se o elemento da coordenada dada é o maior de sua coluna
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
	 * Alocação do vetor auxiliar que armazenará as
	 * coordenadas dos menores elementos de cada linha
	 */
	Coordenada *menoresPorLinha;
	menoresPorLinha = (Coordenada*) malloc(n * n * sizeof(Coordenada));

	printf("Os pontos de sela da matriz são:\n\n");

    /*
     * Encontra as coordenadas dos menores elementos de cada linha
     */
	for(i = 0; i < n; i++) {
		posicoesDoMenorDaLinha(matriz, n, i, menoresPorLinha, &qtdMenores);
	}

    /*
     * Percorre o vetor auxiliar verificando se cada uma coordenadas representa também
     * o maior elemento de sua coluna, nesse caso é um ponto de sela
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
     * Não encontrando nenhum ponto de sela em uma matriz é exibida
     * uma mensagem padrão
     */
	if(!temPontosDeSela)
		printf(NENHUM);

}


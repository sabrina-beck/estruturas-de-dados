/*
 * huffman.h - Interface para o módulo de compressão de textos
 *             utilizando o algoritmo de Huffman.
 */

#include <string.h>

typedef enum {false, true} Boolean;

Boolean ConstroiHuffman(char txt[],int n);
/* A partir do texto 'texto' de 'n' caracteres, constrói a árvore de
   Huffman para compressão deste texto e a guarda numa variável local
   do módulo 'huffman.c'.  Numa outra variável local guarda um vetor
   de apontadores para as folhas da árvore. Devolve 'true' se a
   construção teve sucesso; 'false' caso contrário. */

void ImprimeHuffman();
/* Imprime a árvore de Huffman num formato legível. Função auxiliar
   para os testes pelo programa principal */ 
   
void LiberaHuffman();
/* Libera a memória dinâmica ocupada pelas estruturas criadas por
   'ConstroiHuffman'. */

Boolean Comprime(char *txt, int n,
		 char *bits, int *numBits, int numBitsMax);
/* Comprime os 'n' caracteres do texto 'txt' usando as estruturas já
   construídas, e deixa o resultado como uma seqüência de pseudo-bits
   (ou bits verdadeiros) na área apontada por 'bits'. Devolve em
   'numBits' o número total de bits gerado. Em caso de sucesso devolve
   'true'; se houver mais de 'numBitsMax' bits, devolve 'false'. */

Boolean Descomprime(char *txt, int *n,
		    char *bits, int numBits, int numMaxCars);
/* Descomprime a cadeia de pseudo-bits (ou bits verdadeiros) na área
   apontada por 'bits', de comprimento 'numBits' seguindo a árvore de
   Huffman já construída.  Em caso de sucesso devolve 'true'; se
   aparecer uma codificação incompatível com a árvore, ou se houver
   mais caracteres que 'tamMaxTxt' devolve 'false'.*/

/* 
 * principal.c - Este programa testa o módulo 'trie.c' que
 * implementa árvores digitais ADs)
 *
 *  Comandos aceitos:
 *       c     cria e devolve uma AD vazia
 *       i  s  insere a cadeia s na AD
 *       v  s  verifica se a cadeia s está na AD
 *       r  s  remove a cadeia s da AD
 *       p     visita as cadeias da AD em ordem alfabética
 *       n     imprime o número de nós da AD
 *       a     imprime a altura da AD
 *       k     imprime o número de cadeias na AD
 *       l     libera a memória dinâmica ocupada pela AD     
 *       h     imprime resumo
 *       x ou qencerra execução
 *       #  comentário
 *
 * A liberação total da memória dinâmica alocada por 'MALLOC' é 
 *     testada no fim.
 */
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "balloc.h"
#include "trie.h" 

char entrada[TAM_MAX_CADEIA+4];

/* Função auxiliar que imprime dados sobre bloco de memória não liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {
    printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
} /* bprint */


/* Função que lê o código da ação e a cadeia que pode ser
   vazia. Imprime todas as linhas */
char *leLinha(char *acao) {
 
  char *p, *q;
  p = fgets(entrada, TAM_MAX_CADEIA+4, stdin);
  if (p==NULL) {
    printf("Erro de leitura\n");
    exit(0);
  }
  printf("%s", entrada);
  if (strlen(entrada)<2) { /* ação, \n */
    printf("Entrada inválida\n");
    exit(0);
  }
  *acao = entrada[0];
  do {
    p++;
  } while(*p==' ');
  q = p;
  while (*q>='a' && *q<='z') 
    q++;
  *q = '\0';
  return p;

} /* leLinha */
  
void visita(char *s) {
  if (*s=='\0')
    printf("Cadeia vazia\n");
  else
    printf("%s\n",s);
}

int main() {

  Trie trie;
  Boolean fim = false;
  char *cadeia;
  char acao;
  
  do { 
    
    cadeia = leLinha(&acao);
    
    switch(acao) {

 	case 'c':
	case 'C':
	  trie = CriaAD();
          break;
        
	case '#':
        case ' ':
	  break;
	  
	case 'i':
	case 'I':
          if (!insereAD(trie,cadeia))
	    printf("A cadeia já ocorre na árvore\n");
	  break;
        
	case 'v':
	case 'V':
          if (consultaAD(trie,cadeia))
	    printf("A cadeia ocorre na árvore\n");
	  else
	    printf("A cadeia não ocorre na árvore\n");
	  break;        

	case 'r':
	case 'R':
          if (!removeAD(trie,cadeia))
	    printf("A cadeia não ocorre na árvore\n");
	  break;
        
 	case 'p':
	case 'P':
	  percorreAD(trie,visita);
          break;
          
 	case 'n':
	case 'N':
	  printf("Nos: %d\n",numNosAD(trie));
          break;
          
 	case 'a':
	case 'A':
	  printf("Altura: %d\n",alturaAD(trie));
          break;
          
 	case 'k':
	case 'K':
	  printf("Cadeias: %d\n",numCadeiasAD(trie));
          break;
          
 	case 'l':
	case 'L':
	  liberaAD(trie);
          break;
          
	case 'h':
	case 'H':
	  printf("#     : comentário.\n");
          printf("c     : cria e devolve uma AD vazia\n");
	  printf("i  s  : insere a cadeia s na AD\n");
	  printf("v  s  : verifica se a cadeia s está na AD\n");
	  printf("r  s  : remove a a cadeia s está da AD\n");
	  printf("p     : visita as cadeias da AD em ordem alfabética\n");
	  printf("n     : imprime o número de nós da AD\n");
	  printf("a     : imprime a altura da AD\n");
          printf("k     : imprime o número de cadeias da AD\n");
	  printf("l     : libera a memória dinâmica ocupada pela AD\n");
	  printf("h     : imprime resumo.\n");
	  printf("x     : término.\n");
	  printf("q     : término.\n");
	  break;
	
	case 'x':
	case 'X':
	case 'q':
	case 'Q':
	  fim = true;
	  break;
          
        default:
	  printf("Acao invalida\n");
          break;

	}  /* switch */

    } while (!fim);

  bapply(bprint);

  printf("Processamento terminado\n");
  
  return 0;
  
} /* main */

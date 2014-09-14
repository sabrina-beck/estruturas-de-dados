/* Este programa testa o módulo 'polinomios.c'. São declaradas 4  */
/* variáveis globais do tipo 'Polinomio' (elementos do vetor 'v'),*/
/* e o programa interpreta as ações dadas no arquivo de entrada.  */

/* A liberação total da memória dinâmica alocada por 'MALLOC' é   */
/*      testada no fim utilizando a função 'bapply'.     */


#include <stdio.h>
#include "polinomios.h" 
#include "balloc.h"

/* Função auxiliar que imprime dados sobre bloco de memória não
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */


void ImprimeComentario() {
  char c;
  int res;
  do { 
    res = scanf("%c", &c); 
    if (res!=EOF)
      printf("%c",c);
  } while ((res!=EOF) && (c!='\n'));
}

int main() {

  char acao;
  Polinomio v[4];
  int k, m, n;
  int e;
  float c;
  Boolean fim = false;
    
  /* --------------------------------------------------------------------------- */

  do { 
    scanf("%c", &acao);
    printf("Ação: %c", acao);
    switch (acao)
      { 
          
      case '#':
	ImprimeComentario();
	break;
            
      case 'c':
      case 'C':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	v[k-1] = CriaPolinomioNulo();
	break;
            
      case 'l':
      case 'L':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	LiberaPolinomio(v[k-1]);
	break;
            
      case 'n':
      case 'N':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	if (PolinomioNulo(v[k-1]))
	  printf("Polinomio %d é nulo\n",k);
	else 
	  printf("Polinomio %d não é nulo\n",k);
	break;
            
      case 't':
      case 'T':
	scanf("%d%d%f",&k,&e,&c);
	printf("%2d%3d%5.1f",k,e,c);
	ImprimeComentario();
	InsereTermo(v[k-1],e,c);
	break;
            
      case 'i':
      case 'I':
	scanf("%d",&k);
	printf("%2d",k);
	ImprimeComentario();
	printf("----> ");
	ImprimePolinomio(v[k-1]);
	break;
            
      case 's':
      case 'S':
	scanf("%d%d%d",&k,&m,&n);
	printf("%2d%2d%2d",k,m,n);
	ImprimeComentario();
	v[k-1] = SomaPolinomios(v[m-1],v[n-1]);
	break;
            
      case 'r':
      case 'R':
	scanf("%d%d%d%f",&k,&m,&e,&c);
	printf("%2d%2d%3d%5.1f",k,m,e,c);
	ImprimeComentario();
	v[k-1] = MultTermo(v[m-1],e,c);
	break;
            
      case 'm':
      case 'M':
	scanf("%d%d%d",&k,&m,&n);
	printf("%2d%2d%2d",k,m,n);
	ImprimeComentario();
	v[k-1] = MultPolinomios(v[m-1],v[n-1]);
	break;
            
      case 'h':
      case 'H':
	ImprimeComentario();
	printf("\n");
	printf("#         : comentário\n");
	printf("c k       : v[k] := 0\n");
	printf("l k       : Libera v[k]\n");
	printf("n k       : testa se  v[k]=0\n");
	printf("t k e c   : acrescenta termo (e,c) a v[k]\n");
	printf("i k       : imprime v[k]\n");
	printf("s k m n   : v[k] := v[m]+v[n]\n");
	printf("r k m e c : v[k] := v[m]*(e,c)\n");
	printf("m k m n   : v[k] := v[m]*v[n]\n");
	printf("x         : término\n");
	printf("q         : término\n");
	printf("h         : imprime resumo\n");
	fim = true;
	break;
            
      case 'x':
      case 'X':
      case 'q':
      case 'Q':
	ImprimeComentario();
	fim = true;
	break;
            
      }  /* switch */

  } while (!fim);
      
  /* Verifica se foram liberados todos os blocos alocados */
  bapply(bprint);
   
  printf("Processamento terminado\n");

  return 0;
  
} /* main */

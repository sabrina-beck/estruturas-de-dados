/* Laboratório 03 - matrizes esparsas ligadas - Programa principal */
/* Adaptação do exercício originalmente preparado por Jorge Stolfi */

/* A liberação total da memória dinâmica alocada por 'MALLOC' é   */
/* testada no fim utilizando a função 'bapply'.     */

#include <stdio.h>
#include "matrizes.h" 
#include "balloc.h"

/* As matrizes são representadas externamente por letras maiúsculas: */
#define min_nome 'A'
#define max_nome 'D'

/* Internamente, elas são representadas por inteiros em "[0..num_nomes-1]": */
#define num_nomes (max_nome - min_nome + 1)
typedef unsigned char num_matriz; /* [0..max_nome-min_nome] */

/* Nosso tipo booleanso */
typedef enum {false, true} Boolean;

/* Função auxiliar que imprime dados sobre bloco de memória não
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Faltou liberar o bloco alocado no arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */

void le_nome(num_matriz *k)
  /* Lê um nome de matriz, pulando brancos, e devolve o número correspondente. */
  { 
    char c;
    scanf(" %c", &c);
    if ((c < min_nome) || (c > max_nome)) 
      { erro("nome de matriz invalido"); }
    (*k) = c - min_nome;
  }

int main()
  {
    char acao;
    num_matriz k, k1, k2, k3;
    int m, n, i, j;
    float x;
    matriz a[num_nomes];

    while (true)
      { 
        scanf("%c", &acao);
        printf("ação: %c", acao);
        switch (acao)
          { 
            case 'r': 
              le_nome(&k); prox_linha();
              printf(" %c\n", min_nome+k);
              le_matriz(&a[k]);
              break;
            case 'z': 
              le_nome(&k); scanf("%d %d", &m, &n); prox_linha();
              printf(" %c %d %d\n", min_nome+k, m, n);
              inicializa(&a[k], m, n);
              break;
            case 'v': 
              le_nome(&k); scanf("%d %d", &i, &j); prox_linha();
              printf(" %c %d %d\n", min_nome+k, i, j);
              printf("  %c[%d,%d] = %8.2f\n", min_nome+k, i, j, valor(&(a[k]), i, j));
              break;
            case 'a':
              le_nome(&k); scanf("%d %d %f", &i, &j, &x); prox_linha();
              printf(" %c %2d %2d %8.2f\n", min_nome+k, i, j, x);
              atribui(&a[k], i, j, x);
              break;
            case 's':
              le_nome(&k1); le_nome(&k2); le_nome(&k3); prox_linha();
              printf(" %c %c %c\n", min_nome+k1, min_nome+k2, min_nome+k3);
              soma(&a[k1], &a[k2], &a[k3]);
              break;
            case 'm':
              le_nome(&k1); le_nome(&k2); le_nome(&k3); prox_linha();
              printf(" %c %c %c\n", min_nome+k1, min_nome+k2, min_nome+k3);
              multiplica(&a[k1], &a[k2], &a[k3]);
              break;
            case 't':
              le_nome(&k1); le_nome(&k2); prox_linha();
              printf(" %c %c\n", min_nome+k1, min_nome+k2);
              transpoe(&a[k1], &a[k2]);
              break;
            case 'w':
              le_nome(&k); prox_linha();
              printf(" %c\n", min_nome+k);
              imprime_matriz(&a[k]);
              break;
            case 'x':
              printf("\n");
	      bapply(bprint);
              printf("fim da execução.\n");
              exit(0);
              break;
            case '#':
              { int c;
                do 
                  { c = getchar(); putchar(c); } 
                while ((c != '\n') && (c != EOF));
              }
              break;
  	   case 'l':
	     le_nome(&k); prox_linha();
             printf(" %c\n", min_nome+k);
             libera(&a[k]);
             break;
            default:
              { erro("ação inválida"); }
          } /* switch */
      } /* while */

   bapply(bprint);

   return 0;
  } /* main */

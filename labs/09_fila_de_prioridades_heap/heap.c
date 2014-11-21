/*
 * Nome: Sabrina Beck Angelini      RA: 157240
 * Turma: E
 */

/*
  Implementa��o das fun��es de manipula��o de filas de prioridade
  (FP). Vide o arquivo heap.h com as especifica��es.
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "balloc.h"

typedef struct {
  int tamMax;
  int tam;
  funcCompara *comp;/* fun��o de compara��o */
  void *vetor[1];   /* tamanho alocado ser� 'tamMax' */
} RegHeap, *ImplHeap;


/* Fun��es auxiliares para manipula��o de FPs. */

/*
 * Fun��o que sobe um elemento que est� fora da regra da FP.
 */
void Sobe(ImplHeap h, int m) {

  /* Posi��o do pai do elemento que est� subindo */
  int pai = (m - 1) / 2;
  /* Elemento que est� subindo na fila de prioridade */
  void *subidor = h->vetor[m];
  
  /*
   * Enquanto o elemento n�o chega na raiz e n�o ocupa um lugar
   * na �rvore que atenda as exig�ncia de uma fila de prioridade
   */
  while((m > 0) &&  h->comp(subidor, h->vetor[pai]) > 0) {
    h->vetor[m] = h->vetor[pai];
    m = pai;
    pai = (m - 1) / 2;
  }
  
  /*
   * Por fim coloca o elemento que antes ocupava uma posi��o errada na FP,
   * na posi��o correta, forma otimizada, n�o precisa trocar a cada descida
   */
  h->vetor[m] = subidor;  
} /* Sobe */

/*
 * Fun��o que desce um elemento que esta forada regra da FP
 */
void Desce(ImplHeap h, int m) {
  /* Posi��o do filho esquerdo do elemento que desce */
  int filho = 2 * m + 1;
  /* Valor do elemento que desce */
  void* descedor = h->vetor[m];
  
  /*
   * Enquanto o elemento que desce n�o � folha - neste caso est�
   * na posi��o correta
   */
  while(filho < h->tam) {
    /*
     * Como a regra dessa FP � que a raiz � menor que seus filhos,
     * seleciona-se o menor dos filhos para subir na FP e dar lugar
     * para o elemento que desce
     */
    if(filho < ((h->tam) - 1) && h->comp(h->vetor[filho], h->vetor[filho + 1]) < 0)
      filho++;
    
    /*
     * O elemento deve descer somente se ele filhos menores que ele,
     * de acordo com a regra dessa FP
     */
    if (h->comp(descedor, h->vetor[filho]) < 0) {
      h->vetor[m] = h->vetor[filho];
      m = filho;
      filho = 2 * m + 1;
    } else
    /*
     * Se todos os seus filhos s�o maiores, ent�o o elemento
     * j� est� no lugar certo
     */
      break;
  }
  
  /*
   * Por fim coloca o elemento que antes ocupava uma posi��o errada na FP,
   * na posi��o correta, forma otimizada, n�o precisa trocar a cada descida
   */
  h->vetor[m] = descedor;
} /* Desce */


Heap CriaHeapAux(int n, funcCompara *comp, void *elems[]) {
  /* Cria um heap vazio; se 'elems' n�o � nulo, preenche com os
     valores do vetor 'elems' e transforma num heap.
  */
  ImplHeap ih = MALLOC(sizeof(RegHeap)+(n-1)*sizeof(void *));
  /*
   * N�o importa se elems � passado ou n�o, o tamanho m�ximo da FP
   * ser� n e a fun��o de compara��o comp
   */
  ih->tamMax = n;
  ih->comp = comp;
  
  /* Se n�o h� elementos inicialmente na FP, ent�o o tamanho � 0 */
  if(elems == NULL)
    ih->tam = 0;
  else {
    int i;
    ih->tam = n;
    *(ih->vetor) = *elems;
    
    /*
     * Rearranja elems para atender as regras da FP, para isso,
     * basta subir elemento a elemento do vetor, como se fossem inser��es
     */
    for(i = 1; i < ih->tam; i++)
      Sobe(ih, i);
  }
  
  return ih;
  
} /* CriaHeapAux */

/*
 * Cria uma FP vazia com espa�o de at� 'n' elementos que ser�o
 * apontadores; 'comp' ser� a fun��o de compara��o para estes elementos.
 */
Heap CriaHeap(int n, funcCompara *comp) {

  return CriaHeapAux(n,comp,NULL);
  
} /* CriaHeap */
/* Libera toda a mem�ria din�mica ocupada pela FP 'h', mas n�o por
   seus elementos.
*/
/*
 * Cria uma FP de 'n' elementos apontadores fornecidos no vetor 'elems'.
 * 'comp' ser� a fun��o de compara��o para estes elementos.
 */
Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]) {

  return CriaHeapAux(n,comp,elems);
  
} /* CriaInicializaHeap */

/* Devolve o n�mero de elementos contidos na FP. */
int TamanhoHeap(Heap h) {
  /* Para isso, � preciso usar a implementa��o de Heap: ImplHeap */  
  return ((ImplHeap) h)->tam;
  
} /* TamanhoHeap */

/*
 * Insere o elemento 'e' na FP 'h'. Interrompe a execu��o do programa
 * se houver estouro da FP.
 */
void InsereHeap(Heap h, void *e) {

  ImplHeap ih = h;
  /*
   * Se n�o h� mais espa�o para elementos na FP, o programa n�o
   * pode continuar
   */
  if (ih->tam==ih->tamMax) {
    printf("Estouro da FP\n");
    exit(0);
  }

  /*
   * Na inser��o, basta colocar o novo elemento no final
   * da fila de prioridade e sub�-lo at� sua posi��o correta
   */
  ih->vetor[ih->tam] = e;
  (ih->tam)++;
  Sobe(ih, (ih->tam) - 1);
} /* insereHeap */

/*
 * Remove e devolve o elemento m�ximo (de acordo com a fun��o 'comp')
 * da FP.  Interrompe a execu��o do programa se a FP est� vazia.
 */
void * RemoveHeap(Heap h) {

  ImplHeap ih = h;
  void *ret = NULL;
  /*
   * Se n�o h� mais espa�o para elementos na FP, o programa n�o
   * pode continuar
   */
  if (ih->tam==0) {
    printf("FP vazia\n");
    exit(0);
  }

  /*
   * Na remo��o, basta trocar o primeiro com o �ltimo elemento
   * da fila de prioridade e desc�-lo at� sua posi��o correta
   * Note que como � uma fila, o primeiro elemento � o removido
   * logo a raiz � removida.
   */
  ret = ih->vetor[0];
  (ih->tam)--;
  ih->vetor[0] = ih->vetor[ih->tam];
  Desce(ih, 0);

  return ret;
  
} /* removeHeap */

/*
 * Libera toda a mem�ria din�mica ocupada pela FP 'h', mas n�o por
 * seus elementos.
 */
void LiberaHeap(Heap h) {
  FREE(h);
} /* liberaHeap */


void * Elemento(Heap h, int k) {

  ImplHeap ih = h;
  
  if ((k<0) || (k>=ih->tam))
    return NULL;
  return ih->vetor[k];

} /* Elemento */

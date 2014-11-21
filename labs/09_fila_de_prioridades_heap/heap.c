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
void Sobe(ImplHeap h, int m) {

  /* Posi��o do pai do elemento que est� subindo */
  int pai = (m + 1) / 2;
  /* Elemento que est� subindo na fila de prioridade */
  void *subidor = h->vetor[m];
  
  /*
   * Enquanto o elemento n�o chega na raiz e n�o ocupa um lugar
   * na �rvore que atenda as exig�ncia de uma fila de prioridade
   */
  while((m > 0) &&  h->comp(subidor, h->vetor[pai]) < 0) {
    h->vetor[m] = h->vetor[pai];
    m = pai;
    pai = (m + 1) / 2;
  }
  
  h->vetor[m] = subidor;  
} /* Sobe */

void Desce(ImplHeap h, int m) {
  int filho = 2 * m + 1;
  void* descedor = h->vetor[m];
  
  while(m < h->tam) {
    if(m < (h->tam) - 1 && h->comp(h->vetor[filho], h->vetor[filho + 1]) > 0)
      filho++;

    h->vetor[m] = h->vetor[filho];
    m = filho;
    filho = 2 * m + 1;
  }
  
  h->vetor[m] = descedor;
} /* Desce */


Heap CriaHeapAux(int n, funcCompara *comp, void *elems[]) {
  /* Cria um heap vazio; se 'elems' n�o � nulo, preenche com os
     valores do vetor 'elems' e transforma num heap.
  */
  ImplHeap ih = MALLOC(sizeof(RegHeap)+(n-1)*sizeof(void *));
  ih->tamMax = n;
  ih->comp = comp;
  
  if(elems == NULL) {
    ih->tam = 0;
    ih->vetor = MALLOC(sizeof(void*));
  } else {
    int i;
    ih->tam = n;
    ih->vetor = elems;
    
    for(i = 1; i < ih->tam; i++)
      Sobe(ih, i);
  }
  
  return ih;
  
} /* CriaHeapAux */

Heap CriaHeap(int n, funcCompara *comp) {

  return CriaHeapAux(n,comp,NULL);

} /* CriaHeap */

Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]) {

  return CriaHeapAux(n,comp,elems);

} /* CriaInicializaHeap */

int TamanhoHeap(Heap h) {
  
  return h.tam;
  
} /* TamanhoHeap */


void InsereHeap(Heap h, void *e) {

  ImplHeap ih = h;
  if (ih->tam==ih->tamMax) {
    printf("Estouro da FP\n");
    exit(0);
  }

  h->vetor[h->tam] = e;
  (h->tam)++;
  Sobe(h, (h->tam) - 1);
} /* insereHeap */


void * RemoveHeap(Heap h) {

  ImplHeap ih = h;
  void *ret = NULL;
  if (ih->tam==0) {
    printf("FP vazia\n");
    exit(0);
  }

  ret = h->vetor[0];
  (h->tam)--;
  h->vetor[0] = h->vetor[h->tam];
  Desce(h, 0);

  return ret;
  
} /* removeHeap */

void LiberaHeap(Heap h) {

  FREE(h->vetor);
  FREE(h);

} /* liberaHeap */


void * Elemento(Heap h, int k) {

  ImplHeap ih = h;
  
  if ((k<0) || (k>=ih->tam))
    return NULL;
  return ih->vetor[k];

} /* Elemento */

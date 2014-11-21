/*
 * Nome: Sabrina Beck Angelini      RA: 157240
 * Turma: E
 */

/*
  Implementação das funções de manipulação de filas de prioridade
  (FP). Vide o arquivo heap.h com as especificações.
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "balloc.h"

typedef struct {
  int tamMax;
  int tam;
  funcCompara *comp;/* função de comparação */
  void *vetor[1];   /* tamanho alocado será 'tamMax' */
} RegHeap, *ImplHeap;


/* Funções auxiliares para manipulação de FPs. */

/*
 * Função que sobe um elemento que está fora da regra da FP.
 */
void Sobe(ImplHeap h, int m) {

  /* Posição do pai do elemento que está subindo */
  int pai = (m - 1) / 2;
  /* Elemento que está subindo na fila de prioridade */
  void *subidor = h->vetor[m];
  
  /*
   * Enquanto o elemento não chega na raiz e não ocupa um lugar
   * na árvore que atenda as exigência de uma fila de prioridade
   */
  while((m > 0) &&  h->comp(subidor, h->vetor[pai]) > 0) {
    h->vetor[m] = h->vetor[pai];
    m = pai;
    pai = (m - 1) / 2;
  }
  
  /*
   * Por fim coloca o elemento que antes ocupava uma posição errada na FP,
   * na posição correta, forma otimizada, não precisa trocar a cada descida
   */
  h->vetor[m] = subidor;  
} /* Sobe */

/*
 * Função que desce um elemento que esta forada regra da FP
 */
void Desce(ImplHeap h, int m) {
  /* Posição do filho esquerdo do elemento que desce */
  int filho = 2 * m + 1;
  /* Valor do elemento que desce */
  void* descedor = h->vetor[m];
  
  /*
   * Enquanto o elemento que desce não é folha - neste caso está
   * na posição correta
   */
  while(filho < h->tam) {
    /*
     * Como a regra dessa FP é que a raiz é menor que seus filhos,
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
     * Se todos os seus filhos são maiores, então o elemento
     * já está no lugar certo
     */
      break;
  }
  
  /*
   * Por fim coloca o elemento que antes ocupava uma posição errada na FP,
   * na posição correta, forma otimizada, não precisa trocar a cada descida
   */
  h->vetor[m] = descedor;
} /* Desce */


Heap CriaHeapAux(int n, funcCompara *comp, void *elems[]) {
  /* Cria um heap vazio; se 'elems' não é nulo, preenche com os
     valores do vetor 'elems' e transforma num heap.
  */
  ImplHeap ih = MALLOC(sizeof(RegHeap)+(n-1)*sizeof(void *));
  /*
   * Não importa se elems é passado ou não, o tamanho máximo da FP
   * será n e a função de comparação comp
   */
  ih->tamMax = n;
  ih->comp = comp;
  
  /* Se não há elementos inicialmente na FP, então o tamanho é 0 */
  if(elems == NULL)
    ih->tam = 0;
  else {
    int i;
    ih->tam = n;
    *(ih->vetor) = *elems;
    
    /*
     * Rearranja elems para atender as regras da FP, para isso,
     * basta subir elemento a elemento do vetor, como se fossem inserções
     */
    for(i = 1; i < ih->tam; i++)
      Sobe(ih, i);
  }
  
  return ih;
  
} /* CriaHeapAux */

/*
 * Cria uma FP vazia com espaço de até 'n' elementos que serão
 * apontadores; 'comp' será a função de comparação para estes elementos.
 */
Heap CriaHeap(int n, funcCompara *comp) {

  return CriaHeapAux(n,comp,NULL);
  
} /* CriaHeap */
/* Libera toda a memória dinâmica ocupada pela FP 'h', mas não por
   seus elementos.
*/
/*
 * Cria uma FP de 'n' elementos apontadores fornecidos no vetor 'elems'.
 * 'comp' será a função de comparação para estes elementos.
 */
Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]) {

  return CriaHeapAux(n,comp,elems);
  
} /* CriaInicializaHeap */

/* Devolve o número de elementos contidos na FP. */
int TamanhoHeap(Heap h) {
  /* Para isso, é preciso usar a implementação de Heap: ImplHeap */  
  return ((ImplHeap) h)->tam;
  
} /* TamanhoHeap */

/*
 * Insere o elemento 'e' na FP 'h'. Interrompe a execução do programa
 * se houver estouro da FP.
 */
void InsereHeap(Heap h, void *e) {

  ImplHeap ih = h;
  /*
   * Se não há mais espaço para elementos na FP, o programa não
   * pode continuar
   */
  if (ih->tam==ih->tamMax) {
    printf("Estouro da FP\n");
    exit(0);
  }

  /*
   * Na inserção, basta colocar o novo elemento no final
   * da fila de prioridade e subí-lo até sua posição correta
   */
  ih->vetor[ih->tam] = e;
  (ih->tam)++;
  Sobe(ih, (ih->tam) - 1);
} /* insereHeap */

/*
 * Remove e devolve o elemento máximo (de acordo com a função 'comp')
 * da FP.  Interrompe a execução do programa se a FP está vazia.
 */
void * RemoveHeap(Heap h) {

  ImplHeap ih = h;
  void *ret = NULL;
  /*
   * Se não há mais espaço para elementos na FP, o programa não
   * pode continuar
   */
  if (ih->tam==0) {
    printf("FP vazia\n");
    exit(0);
  }

  /*
   * Na remoção, basta trocar o primeiro com o último elemento
   * da fila de prioridade e descê-lo até sua posição correta
   * Note que como é uma fila, o primeiro elemento é o removido
   * logo a raiz é removida.
   */
  ret = ih->vetor[0];
  (ih->tam)--;
  ih->vetor[0] = ih->vetor[ih->tam];
  Desce(ih, 0);

  return ret;
  
} /* removeHeap */

/*
 * Libera toda a memória dinâmica ocupada pela FP 'h', mas não por
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

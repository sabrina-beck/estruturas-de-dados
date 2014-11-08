/*
  Arquivo heap.h: define a interface para uma fila de prioridades (FP)
  de  elementos fornecidos através de apontadores.
  
  A implementação supõe que deseja-se uma FP com elemento máximo na
  raiz; pode-se obter uma FP com o mínimo, através de definição
  conveniente da função de comparação 'comp'.
*/ 

typedef void * Heap;  /* tipo efetivo escondido */
typedef int funcCompara(void *, void *); /* tipo da função de comparação, devolvendo <0, 0, >0 */

Heap CriaHeap(int n, funcCompara *comp);
/* Cria uma FP vazia com espaço de até 'n' elementos que serão
   apontadores; 'comp' será a função de comparação para estes elementos.
*/

Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]);
/* Cria uma FP de 'n' elementos apontadores fornecidos no vetor 'elems'.
   'comp' será a função de comparação para estes elementos.
*/

int TamanhoHeap(Heap h);
/* Devolve o número de elementos contidos na FP. */

void InsereHeap(Heap h, void *e);
/* Insere o elemento 'e' na FP 'h'. Interrompe a execução do programa
   se houver estouro da FP.
*/

void * RemoveHeap(Heap h);
/* Remove e devolve o elemento máximo (de acordo com a função 'comp')
   da FP.  Interrompe a execução do programa se a FP está vazia.
*/

void LiberaHeap(Heap h);
/* Libera toda a memória dinâmica ocupada pela FP 'h', mas não por
   seus elementos.
*/

/* ============================================================ */

void * Elemento(Heap h, int k);
/* Devolve o k-ésimo elemento (0<=k<tamanho da FP) do vetor que
   representa a FP.  Devolve NULL se o valor de k não é válido.  Esta
   função é usada apenas para verificação da estrutura da FP mas não faz
   parte da especificação da interface abstrata pois esta não impõe a
   implementação usando um vetor.
 */

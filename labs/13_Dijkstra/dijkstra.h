/*
  dijkstra.h: interface para implemenação do algoritmo de Dijkstra
  para grafos orientados.
*/

typedef void *Grafo; 
typedef enum {CERTO, ERRADO} Erro;

Grafo CriaGrafoVazio(int n);
/* Devolve um grafo de 'n' vértices numerados de 0 a n-1, sem arestas. */

Erro AcrescentaAresta(Grafo g, int u, int v, int p);
/* Acrescenta ao grafo 'g' a aresta 'u->v' de peso 'p'.  Casos de erro
   detectados: valores de 'u' ou 'v' inválidos, ou a aresta já existe,
   ou o peso não é positivo. As listas de adjacência devem estar em
   ordem crescente dos vértices de destino. */

void Dijkstra(Grafo g, int r, int dist[]);
/* Para cada vértice 'v' do grafo 'g', calcula a distância mínima
   (soma dos pesos) de 'r' a 'v', e coloca seu valor em dist[v].  Caso
   o caminho não exista, deve colocar o valor INT_MAX importado de
   <limits.h>; o valor de dist[r] deve ser 0.
   
   Antes de retornar, deve liberar toda a memória dinâmica alocada
   para as variáveis auxiliares internas, exceto o grafo propriamente
   dito.  Deve permitir outras chamadas desta função com outro valor
   de 'r'.

*/   

void LiberaGrafo(Grafo g);
/* Libera a memória dinâmica usada para representar o grafo */


void ImprimeGrafo(Grafo g);
/* Imprime as listas de adjacência do grafo sob a forma indicada neste exemplo:

      1:   2 (   2)   4 (   7)   6 (  12)
      
   onde os vértices adjacentes ao vértice 1 são 2, 4 e 6 (em ordem
   crescente).  Cada vértice e seu peso deve ser impresso no formato
   %4d.  Esta função permite a verificação da representação do grafo e
   ajuda na depuração do programa.
   
*/ 


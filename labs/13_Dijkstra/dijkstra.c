/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turmas:        E e F
  
  Tarefa: 13
  Segundo semestre de 2014

*/

/* A especificação das funções encontra-se no arquivo dijkstra.h */

#include <stdio.h>
#include <limits.h>

#include "dijkstra.h"
#include "balloc.h"

typedef enum {false, true} Boolean;

/* Aresta */
typedef struct aux {
  int dest;
  int peso;
  struct aux *prox;
} Aresta;

/* Implementação de grafo */
typedef struct {
  int tam;               /* número de vértices */
  Aresta * vertices[1];  /* tamanho final será 'tam' */
} RegGrafo, *ImplGrafo;

/*
 * Devolve um grafo de 'n' vértices numerados de 0 a n-1, sem arestas.
 */
Grafo CriaGrafoVazio(int n) {
  ImplGrafo grafo = MALLOC(sizeof(RegGrafo) + (n - 1)*sizeof(Aresta*));
  grafo->tam = n;
  
  return grafo;
  
} /* CriaGrafoVazio */

/*
 * Função auxiliar que verifica se um vértice é valido
 */
Boolean ehValido (ImplGrafo grafo, int u) {
  return u >= 0 && u < grafo->tam;
}

/*
 * Acrescenta ao grafo 'g' a aresta 'u->v' de peso 'p'.  Casos de erro
 * detectados: valores de 'u' ou 'v' inválidos, ou a aresta já existe,
 * ou o peso não é positivo. As listas de adjacência permanecem em
 * ordem crescente dos vértices de destino.
 */
Erro AcrescentaAresta(Grafo g, int u, int v, int p) {
  Aresta **atual, *aux, *nova;
  ImplGrafo grafo = (ImplGrafo) g;
  if(!ehValido(grafo, u) || !ehValido(grafo, v) || p < 0) {
    return ERRADO;
  }
  
  /*
   * Procura a posição da nova aresta na lista de arestas do vértice u,
   * mantendo a lista em ordem crescente dos vértices de destino
   */
  atual = &(grafo->vertices[u]);
  while(*atual != NULL && (*atual)->dest < v) {
    *atual = (*atual)->prox;
  }

  /* Se a aresta já existe está errado */
  if((*atual) != NULL && (*atual)->dest == v)
    return ERRADO;

  /* Cria a nova aresta */
  nova = MALLOC (sizeof(Aresta));
  nova->dest = v;
  nova->peso = p;
  nova->prox = NULL;

  /*
   * aux é o apontador 'prox' que deverá apontar para a nova aresta, no caso
   * da lista estar vazia, então é o apontador do vetor
   */
   aux = *atual;
   *atual = nova;
   nova->prox = aux;
  return CERTO;   /* PROVISÓRIO */
  
} /* AcrescentaAresta */

/*
 * Imprime as listas de adjacência do grafo sob a forma indicada neste exemplo:
 *
 *    1:   2 (   2)   4 (   7)   6 (  12)
 *
 * onde os vértices adjacentes ao vértice 1 são 2, 4 e 6 (em ordem
 * crescente).  Cada vértice e seu peso deve ser impresso no formato
 * %4d.  Esta função permite a verificação da representação do grafo e
 * ajuda na depuração do programa.
 *
 */ 
void ImprimeGrafo(Grafo g) {
 
  ImplGrafo ig = g;
  int i, n;
  Aresta *v;
  
  n = ig->tam;
  printf("Grafo de %d vértices:\n",n);
  for (i=0; i<n; i++) {
    printf("%4d:",i);
    v = ig->vertices[i];
    while (v!=NULL) {
      printf("%4d (%d)",v->dest,v->peso);
      v = v->prox;
    }
    printf("\n");
  }
  
} /* ImprimeGrafo */

/*
 * Para cada vértice 'v' do grafo 'g', calcula a distância mínima
 * (soma dos pesos) de 'r' a 'v', e coloca seu valor em dist[v].  Caso
 * o caminho não exista, deve colocar o valor INT_MAX importado de
 * <limits.h>; o valor de dist[r] deve ser 0.
 *
 * Antes de retornar, deve liberar toda a memória dinâmica alocada
 * para as variáveis auxiliares internas, exceto o grafo propriamente
 * dito.  Deve permitir outras chamadas desta função com outro valor
 * de 'r'.
 *
 */   
void Dijkstra(Grafo g, int r, int dist[]) {
  int i, numVertices;
  int* vertices;
  Aresta* aresta;
  ImplGrafo grafo = (ImplGrafo) g;

  /* Inicidliza as distâncias */
  for(i = 0; i < grafo->tam; i++)
    dist[i] = INT_MAX;
  
  dist[r] = 0;
  
  /* Cria o vetor auxiliar de vértices */
  vertices = MALLOC (grafo->tam * sizeof(int));
  numVertices = grafo->tam;
  for(i = 0; i < numVertices; i++)
    vertices[i] = i;
  
  /* Faz os percursos */
  while(numVertices > 0) {
    /* verticeAtual contém o índice do vertice no vetor local vertices */
    int verticeAtual = 0;
    /* Procura o vértice com custo mínimo */
    for(i = 1; i < numVertices; i++)
      if(dist[vertices[verticeAtual]] > dist[vertices[i]])
        verticeAtual = i;
    /* Se o vertice com custo mínimo tiver custo infinito, então esse vértice não conectado a outros vértices */
    if(dist[vertices[verticeAtual]] == INT_MAX)
      break;
    
    /* Remove o vertice atual */
    for(i = verticeAtual; i < numVertices - 1; i++)
      vertices[i] = vertices[i + 1];
    numVertices--;
    
    /* Calcula o custo para cada vértice adjacente */
    aresta = grafo->vertices[vertices[verticeAtual]];
    while(aresta != NULL) {
      int custo = dist [vertices[verticeAtual]] + aresta->peso;
      if(custo < dist[aresta->dest]) {
        dist[aresta->dest] = custo;
      }
      aresta = aresta->prox;
    }
  }
  
  FREE (vertices);
  
} /* Dijkstra */

/*
 * Libera a memória dinâmica usada para representar o grafo
 */
void LiberaGrafo(Grafo g) {
  int i;
  ImplGrafo grafo = (ImplGrafo) g;
  
  /* Primeiro libera as listas de arestas de cada vértice */
  for(i = 0; i < grafo->tam; i++) {
    Aresta* atual = grafo->vertices[i];
    while(atual != NULL) {
      Aresta *aux = atual->prox;
      FREE(atual);
      atual = aux;
    }
  }
  
  /* Depois libera a estrutura do Grafo */
  FREE(grafo);
} /* LiberaGradfo */

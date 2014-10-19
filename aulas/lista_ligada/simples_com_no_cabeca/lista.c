#include <stdio.h>

/*** LISTA SIMPLES COM NÓ CABEÇA ***/

typedef
  struct No {
    int info;
    struct No *prox;
  } No, *Lista;

Lista criaLista() {
  Lista lista = malloc(sizeof(No));
  lista->info = -1; /* convenção do conteúdo do né cabeça, poderia ser a quantidade de elementos */
  lista->prox = NULL;
  return lista
}

/*
 * Essas implementações não funcionam para listas vazias que não possuem nó cabeça,
 * nem funcionam para remover o nó cabeça, recebe o nó predecessor ao inserido/removido
 */
void insere(Lista p, int info) {
  Lista novo = malloc(sizeof(No));
  novo->info = info;
  novo->prox = p->prox;
  p->prox = novo;
}

void remove(Lista p, int *x) {
  Lista removido = p->prox;
  *x = removido->info;
  p->prox = removido->prox;
  free(removido);
}

#include <stdio.h>

/*** LISTA SIMPLES ***/

typedef
  struct No {
    int info;
    struct No *prox;
  } No, *Lista;

/*
 * Passa o apontador da variável que aponta para o próximo nó do nó predecessor ao novo nó,
 * essa complexidade se deve à dificuldade de inserir em listas vazias.
 */
void insere(Lista *p, int info) {
  Lista novo = malloc(sizeof(No));
  novo->info = info;
  novo->prox = *p;
  *p = novo;
}

void remover(Lista *p, int* x) {
  Lista removido = *p;
  *x = removido->info;
  *p = removido->prox;
  free(removido);
}

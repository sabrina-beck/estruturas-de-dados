#include <stdio.h>

/*** LISTA DUPLAMENTE LIGADA CIRCULAR COM NÓ CABEÇA ***/

typedef
  struct No {
    int info;
    struct No *esq, *dir
  } No, *Lista;
  
Lista criaLista() {
  Lista lista = malloc(sizeof(No));
  lista->info = -1;
  lista->esq = lista;
  lista->dir = lista;
  return lista;
}
 
/*
 * Insere a esquerda do nó passado por parâmetro
 */
void insereEsq(Lista lista, int info) {
  Lista novo = malloc(sizeof(No));
  novo->info = info;
  novo->esq = lista->esq;
  novo->dir = lista;
  novo->dir->esq = novo;
  novo->esq->dir = novo;
}

/*
 * Remove o elemento dado e retorna o valor removido,
 * supõe que há pelo menos um elemento na lista
 */
void remover(Lista removido, int *x) {
  removido->esq->dir = removido->dir;
  removido->dir->esq = removido->esq;
  *x = removido->info;
  free(removido);
}

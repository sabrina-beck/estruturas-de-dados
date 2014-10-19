#include <stdio.h>

/*** LISTA CIRCULAR COM NÓ CABEÇA ***/

typedef
  struct No {
    int info;
    struct No *prox;
  } No, *Lista;
  
Lista criaLista() {
  Lista lista = malloc(sizeof(No));
  lista->info = -1;
  lista->prox = lista;
}
  
/*
 * Pesquisa sem sentinela, pesquisa padrão
 */
Lista buscar(Lista lista, int info) {
  Lista atual = lista->prox;
  
  while(atual != lista && atual->info != info)
    atual = atual->prox;
  
  if(atual == lista)
    return NULL;
    
  return atual;
}

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
  return lista;
}
  
/*
 * Pesquisa sem sentinela, pesquisa padrão
 */
Lista buscar(Lista lista, int info) {
  Lista atual = lista;

  /* do..while para pular o nó cabeça */  
  do{
    atual = atual->prox;
  }while(atual != lista && atual->info != info);
  
  if(atual == lista)
    return NULL;
    
  return atual;
}

/*
 * Pesquisa com sentinela, guarda o valor buscado no nó cabeça,
 * desse modo com certeza vai achar o valor buscado, e terá apenas
 * uma comparação de final de lista, verificando se o que encontrou
 * está no nó cabeça, nesse caso não achou o valor na lista.
 */
Lista buscarComSentinela(Lista lista, int info) {
  Lista atual = lista;
  lista->info = info;
  
  do {
    atual = atual->prox;
  } while(atual->info !- info);
  
  if(atual == lista)
    return NULL;
  
  return atual;
}
 

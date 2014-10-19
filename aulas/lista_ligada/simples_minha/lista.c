#include <stdio.h>
#include "lista.h"
#include <stdlib.h>

NoLista criaNo(void* info) {
  NoLista lista = malloc(sizeof(No));
  lista->info = info;
  lista->prox = NULL;
  return lista;
}

Lista novaLista() {
  Lista lista;
  lista->primeiro = NULL;
  lista->qtd = 0;
  return criaNo(NULL);
}

Lista insereNoInicio(void* info, Lista lista){
  NoLista novo = criaNo(info);
  novoNo->prox = lista->primeiro;
  lista->primeiro = novoNo;
  lita->qtd++;
  return lista;
}

Lista insereNoFim(void* info, Lista lista) {
  NoLista atual;
  NoLista novoNo;

  if(estaVazia(Lista))
    return insereNoInicio(info, lista);

  novoNo = criaNo(info);
  atual = lista->primeiro;
  while(atual->prox != NULL)
    atual = atual->prox;
  atual->prox = novoNo;
  lista->qtd++;
  
  return lista;
}

Lista insereEm(int pos, void* info, Lista lista) {
  int i;
  NoLista atual = lista->primeiro;
  NoLista novoNo = criaNo(info);
  
  for(i = 0; i < pos - 1 && atual->prox != NULL; i++)
    atual = atual->prox;
    
  if(i == pos - 2) {
    novoNo->prox = atual->prox;
    atual->prox = novoNo;
    if(i == 0)
      lista->primeiro = novoNo;
    lista->qtd++;
  }
  
  return lista;
}

bool remover(void* info, Lista lista) {
  NoLista atual = lista->primeiro;
  NoLista removido;
  
  if(estaVazia(lista))
    return false;
  //FIXME
  while(atual->prox != NULL && atual->prox->info != info)
    atual = atual->prox;

  if(atual->prox != NULL) {
    removido = atual->prox;
    atual->prox = atual->prox->prox;
    free(removido);
    lista->qtd--;
    return true;
  }
  
  return false;
}

bool removerDe(int pos, Lista lista) {
  int i;
  NoLista atual = lista->primeiro;
  
  if(estaVazia(lista))
    return false;
  //FIXME
  for(i = 0; i < pos-1 && atual->prox != NULL; i++)
    atual = atual->prox;

  if(i == pos-1) {
    NoLista removido = atual->prox;
    atual->prox = atual->prox->prox;
    free(removido);
    lista->qtd--;
    return true;
  }
  
  return false;
}

void* encontrar(int pos, Lista lista) {
  NoLista atual = lista->primeiro;
  int i;
  
  if(lista == NULL)
    return NULL;

  for(i = 0; i < pos; i++) {
    atual = atual->prox;
    if(atual == NULL)
      return NULL;
  }

  return atual;
}

int posicaoDe(void* info, Lista lista) {
  int i;
  NoLista atual = lista->primeiro;
  
  for(i = 0; atual != NULL && atual->info != info; i++){
    atual = atual->prox;
  }
  
  if(atual == NULL)  
    return -1;
   
  return i;
}

bool estaVazia(Lista lista) {
  return lista->qtd == 0;
}

int quantidadeDeElementos(Lista lista) {
   return lista->qtd;
}

void liberar(Lista lista) {
  NoLista atual = lista->primeiro;
  
  while(atual != NULL){
    NoLista prox = atual->prox;
    free(atual);
    atual = prox;
  }
}

void imprime(Lista lista) {
  NoLista atual = lista->primeiro;
  
  while(atual != NULL) {
    printf("%s ->", atual->info);
    atual = atual->prox;
  }
  
  printf("NULL\n");
}

#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

bool estaVazia(Pilha topo) {
  return topo == NULL;
}

void empilhar(Pilha *topo, char info) {
  Pilha novoNo = malloc(sizeof(No));
  novoNo->info = info;
  
  novoNo->prox = *topo;
  *topo = novoNo;
}

char desempilhar(Pilha *topo) {
  if(estaVazia(*topo))
    return '\0';
  Pilha desempilhado = *topo;
  char infoDesempilhado = desempilhado->info;
  *topo = (*topo)->prox;
  free(desempilhado);
  return infoDesempilhado;
}

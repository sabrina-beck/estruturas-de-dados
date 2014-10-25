#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

Pilha criarPilha() {
  Pilha pilha;
  pilha.topo = -1;
  return pilha;
}

bool estaVazia(Pilha pilha) {
  return pilha.topo == -1;
}

void empilhar(Pilha *pilha, int info) {
    if(pilha->topo == TAM_MAX-1) {
      printf("Falta memória!\n");
      exit(0);
    }
    
    pilha->topo++;
    pilha->elementos[pilha->topo] = info;
}

int desempilhar(Pilha *pilha) {
  int info;
  if(estaVazia(*pilha)) {
    printf("Pilha VAZIA!\n");
    exit(0);
  }
  info = pilha->elementos[pilha->topo--];
  return info;
}

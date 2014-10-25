#define TAM_MAX 100

/*** PILHA SEQUENCIAL ***/

typedef 
  struct Pilha {
    int topo;
    int elementos[TAM_MAX];
  } Pilha;
 
/*
 * Usa a convenção do topo apontar para o último elemento inserido
 */
Pilha* criaPilha() {
  Pilha *pilha;
  pilha->topo = -1;
  return pilha;
}

/*
 * Passa o apontador da pilha porque a variável topo será alterada
 */
void empilha(Pilha *pilha, int info) {
  if(topo == TAM_MAX - 1) {
    printf("Pilha cheia!!");
    return;
  }
  pilha->topo++;
  pilha->elementos[pilha->topo] = info;
}

/*
 * Desempilha e retorna o valor desempilhado
 */
int desempilha(Pilha *pilha) {
  if(topo == -1) {
    printf("Pilha Vazia!!");
    return -99999999;
  }
  pilha->topo--;
  return pilha->topo + 1;
}

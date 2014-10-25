/*** PILHA LIGADA ***/

typedef
  struct NoPilha {
    int info;
    struct NoPilha *prox;
  } NoPilha, *Pilha;
  
/*
 * Recebe um apontador para o apontador do topo da
 * pilha, pois o topo vai mudar
 */
void empilha(Pilha *pilha, int info) {
  Pilha novo = malloc(sizeof(NoPilha));
  
  if(novo == NULL)
    printf("Acabou a memória!");
    
  novo->info = info;
  novo->prox = (*pilha);
  (*pilha) = novo;
}

int desempilha(Pilha *pilha, int info) {
  Pilha removido = *pilha;
  int x = removido->info;
  *pilha = (*pilha)->prox;
  free(removido);
  return x;
}

/*** FILA LIGADA CIRCULAR ***/

/*
 * Há um único apontador para o último elemento da fila, sendo
 * circular e com nó cabeça basta avançar para o cabeça e do
 * cabeça para o início da fila
 */
 
typedef
  struct No {
    int info;
    struct No *prox;
  } No, *Fila;
  
Fila* criaFila() {
  Fila *fila = malloc(sizeof(No));
  fila->info = -1;
  fila->prox = fila;
  return fila;
}

/* verifica se é nó cabeça */
bool estaVazia(Fila fila) {
  return fila.info == -1;
}

void enfileirar(Fila *fila, int info) {
  Fila novo = malloc(sizeof(No));
  novo->info = info;
  novo->prox = (*fila)->prox;
  fila->prox = novo;
  *fila = novo;
}

int desenfileirar(Fila *fila) {
  Fila removido, cabeca;
  int dado;
  if(estaVazia(*fila)) {
    printf("Fila Vazia!!");
    return -999;
  }
  
  cabeca = (*fila)->prox;
  /* Pula o nó cabeça e pega o elemento da frente */
  removido = cabeca->prox;
  dado = removido->info;
  if(removido == *fila)
    *fila = removido->prox;
  cabeca->prox = removido->prox;
  
  return dado;
}

#define TAM_MAX 100

/*** FILA SEQUENCIAL CIRCULAR ***/

typedef
  struct Fila {
    int frente, fim;
    int elementos[TAM_MAX];
  } Fila;
  
Fila criaFila() {
  Fila fila;
  fila.frente = 0;
  fila.fim = 0;
  return fila;
}

int tamanho(Fila fila) {
  return (fila.fim - fila.frente + TAM_MAX) % TAM_MAX;
}

bool estaVazia(Fila fila) {
  return fila.fim == fila.frente;
}

/*
 * Essa implementação sacrifica uma posição do vetor para poder
 * identificar quando a fila está cheia, uma alternativa seria
 * manter uma booleana marcando se a fila está cheia ou uma
 * variável inteira com o tamanho da fila.
 */
bool estaCheia(Fila fila) {
  return frente == (fim + 1) % TAM_MAX;
}

void enfileirar(Fila *fila, int info) {
  if(estaCheia(*fila)) {
    printf("Fila cheia!");
    return;
  }
  fila->fim = (fila->fim + 1) % TAM_MAX;
  fila->elementos[fila->fim] = info;
}

int desenfileirar(Fila *fila) {
  int removido;
  if(estaVazia(*fila)) {
    printf("Fila vazia!!");
    return -999;
  }
  
  removido = fila->elementos[fila->frente];
  fila->frente = (fila->frente + 1) % n;
  return removido;
}

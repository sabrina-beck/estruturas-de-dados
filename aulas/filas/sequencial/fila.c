#define TAM_MAX 100 
/*** FILA SEQUENCIAL ***/

/*
 * Convenção adotada para implementação sequencial:
 * frente aponta para uma posição
 * antes do primeiro elemento da fila e fim aponta para
 * a posição do último elemento da fila.
 * Problema: não ocupa todo o espaço do vetor, mesmo quando há.
 */
 
typedef
  struct Fila {
    int frente, fim;
    int elementos[TAM_MAX];
  } Fila;
  
Fila criaFila() {
  Fila fila;
  fila.frente = -1;
  fila.fim = -1;
  return fila;
}

bool estaVazia(Fila fila) {
  return fila.frente == fila.fim;
}

int tamanho(Fila fila) {
  return fila.fim - fila.frente;
}

void enfileirar(Fila *fila, int info) {
  if(fim == TAM_MAX - 1) {
    printf("Fila cheia!!");
    return;
  }
  fila->fim++;
  fila->elementos[fila->fim] = info;
}

int desenfileirar(Fila *fila) {
  if(estaVazia(*fila)) {
    printf("Fila vazia!!");
    return;
  }
  fila->frente++;
  return fila->elementos[fila->frente];  
}



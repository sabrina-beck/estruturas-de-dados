/*** FILA LIGADA ***/

typedef
  struct No {
    int info;
    struct Fila *prox;
  } No, *ApNo;

typedef
  struct Fila {
    ApNo *frente, *fim;
  } Fila;
  
Fila criaFila() {
  Fila fila;
  fila.frente = NULL;
  fila.fim = NULL;
  return fila;
}

bool estaVazia(Fila fila) {
  return fila.frente == NULL;
}

void enfileirar(Fila *fila, int info) {
  ApNo novo = malloc(sizeof(ApNo));
  novo->info = info;
  novo->prox = NULL;
  if(estaVazia(*fila))
    fila->frente = novo;
  else
    fila->fim->prox = novo;
  fila->fim = novo;
}

int desenfileirar(Fila *fila) {
  ApNo removido;
  int dado;
  if(estaVazia(*fila)) {
    printf("Fila Vazia!!");
    return -999;
  }
  removido = fila->frente;
  dado = removido->info;
  
  if(fila->frente == fila->fim)
    fila->fim = NULL;
  
  fila->frente = removido->prox;
  free(removido);
  return dado;
}

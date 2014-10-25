void inOrdem(Arvore arv) {
  if(arv != NULL) {
    inOrdem(arv->esq);
    printf("%d ", arv->info);
    inOrdem(arv->dir);
  }
}

void inOrdemCaudal() {
  while(arv != NULL) {
    inOrdemCaudal(arv->esq);
    printf("%d ", arv->info);
    arv = arv->dir;
  }
}

void preOrdem(Arvore arv) {
  if(arv != NULL) {
    printf("%d ", arv->info);
    preOrdem(arv->esq);
    preOrdem(arv->dir);
  }
}

void preOrdemCaudal(Arvore arv) {
  while(arv != NULL) {
    printf("%d ", arv->info);
    preOrdemCaudal(arv->esq);
    arv = arv->dir;
  }
}

void preOrdemPilha(Arvore arv) {
  Pilha pilha = NULL;
  empilhar(&pilha, arv);
  do {
    Arvore atual = desempilhar(&pilha);
    if(atual != NULL) {
      printf("%d ", atual->info);
      empilhar(&pilha, arv->dir);
      empilhar(&pilha, arv->esq);
    }
  } while(!estaVazia(pilha));
}

void preOrdemPilhaCaudal(Arvore arv) {
  Pilha pilha = NULL;
  empilhar(&pilha, arv);
  do {
    Arvore atual = desempilhar(&pilha);
    while(atual != NULL) {
      printf("%d ", atual->info);
      empilhar(atual->dir);
      atual = atual->esq;
    }
  } while(!estaVazia(pilha));
}

void posOrdem(Arvore arv) {
  if(arv != NULL) {
    posOrdem(arv->esq);
    posOrdem(arv->dir);
    printf("%d ", arv->info);
  }
}

void emLargura(Arvore arv) {
  Fila fila = criarFila();
  enfileirar(&fila, arv);
  do {
    Arvore atual = desenfileirar(&fila);
    if(atual != NULL) {
      printf(atual->info);
      enfileirar(atual->esq);
      enfileirar(atual->dir);
    }
  } while(!estaVazia(fila));
}



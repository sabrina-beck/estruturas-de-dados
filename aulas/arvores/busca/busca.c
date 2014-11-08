
bool busca(Arvore arv, int x) {
  Arvore atual = arv;
  while(atual != NULL) {
    if(atual->info > x)
      atual = atual->esq;
    else if(atual->info < x)
      atual = atual->dir;
    else if(atual->info == x)
      return true;
  }
  return false;
}

bool busca_recursiva(Arvore arv, int x) {
  if(arv == NULL)
    return false;
  if(arv->info == x)
    return true;
  if(arv->info > x)
    return busca_recursiva(arv->esq, x);
  return busca_recursiva(arv->dir, x);
}

bool inserir(Arvore *arv, int x) {
  Arvore *atual = arv;
  Arvore novo;
  while(*atual != NULL) {
    if((*atual)->info > x)
      *atual = &((*atual)->esq);
    else if((*atual)->info < x)
      *atual = &((*atual)->dir);
    else
      return false;
  }
  novo = malloc(sizeof(No));
  novo->info = x;
  novo->dir = NULL;
  novo->esq = NULL;
  *atual = novo;
  return true;
}

bool inserirRecursivo(Arvore *arv, int x) {
  if(*arv == NULL) {
    *arv = malloc(sizeof(No));
    (*arv)->info = x;
    (*arv)->esq = NULL;
    (*arv)->dir = NULL;
    return true;
  }
  
  if((*arv)->info == x)
    return false;
  
  if((*arv)->info > x)
    inserirRecursivo(&((*arv)->esq), x);
  inserirRecursivo(&((*arv)->dir), x);
}

bool removerRecursivo(Arvore *arv, int x) {
  if(*arv == NULL)
    return false;
  
  if((*arv)->info > x)
    return removerRecursivo(&((*arv)->esq), x);
  if((*arv)->info < x)
    return removerRecursivo(&((*arv)->dir), x);

  if((*arv)->esq == NULL) {
    Arvore removido = *arv;
    *arv = removido->dir;
    free(removido);
  }
  
  if((*arv)->dir == NULL) {
    Arvore removido = *arv;
    *arv = removido->esq;
    free(removido);
  }

  if((*arv)->dir != NULL && (*arv)->esq != NULL) {
    Arvore removido = *arv;
    Arvore *substituto = &(removido->esq);
    while((*substituto)->dir != NULL)
      *substituto = (*substituto)->dir;
    (*arv)->info = substituto->info;
    free(*substitulo);
    *substituto = NULL; 
  }
    
  return true;
}

#include <stdio.h>

typedef
  struct No {
    int info;
    struct No *esq, *dir;
  } No, *Arvore;

int height(Arvore arv) {
  int heightEsq, heightDir;
  if(arv == NULL)
    return 0;
  heightEsq = height(arv->esq);
  heightDir = height(arv->dir);
  if(heightEsq > heightDir)
    return heightEsq + 1;
    
  return heightDir + 1;
}

int main() {
  return 0;
}

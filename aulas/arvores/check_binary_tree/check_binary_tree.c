#include <stdio.h>

typedef
  enum bool { false, true } bool;

typedef
  struct No {
    int info;
    struct No *esq, *dir;
  } No, *Arvore;

bool isBinarySearchTree(Arvore arv, int min, int max) {
  if(arv == NULL)
    return true;

  if(arv->info < min || arv->info > max)
    return false;
  
  return isBinarySearchTree(arv->esq, min, arv->info - 1) && 
         isBinarySearchTree(arv->dir, arv->info + 1, max);
}

bool isBST(Arvore arv) {
  return isBinarySearchTree(arv, INT_MIN, INT_MAX);
}

int main() {
  

  return 0;
}

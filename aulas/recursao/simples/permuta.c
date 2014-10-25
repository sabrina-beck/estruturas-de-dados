#include <stdio.h>
#define TAM_MAX 71

void troca (char *str, int i, int j) {
  char aux = str[i];
  str[i] = str[j];
  str[j] = aux;
}

void permuta(char *str, int ini, int fim) {
  if(ini == 0)
    printf("%s\n", str);
  else {
    int i;
    for(i = ini - 1; i >= 0; i--) {
      troca(str, i, ini - 1);
      permuta(str, ini - 1, fim);
      troca(str, i, ini - 1);
    }
  }
}

int main() {
  char str[TAM_MAX];
  int tam;
  
  printf("Digite uma palavra: ");
  scanf("%s", str);
  
  for(tam = 0; str[tam]; tam++);
  
  permuta(str, tam, tam);

  return 0;
}

#include <stdio.h>

void hanoi(char orig, char dest, char aux, int n) {
  while(n > 0) {
    char t;
    hanoi(orig, aux, dest, n - 1);
    printf("Mova de %c para %c\n", orig, dest);
    t = orig;
    orig = aux;
    aux = t;
    n = n - 1;
  }
}

int main() {
  int n;
  
  printf("Quantos discos? ");
  scanf("%d", &n);
  
  hanoi('A', 'B', 'C', n);

  return 0;
}

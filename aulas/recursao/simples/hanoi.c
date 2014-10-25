#include <stdio.h>

void hanoi(char orig, char dest, char aux, int n) {
  if(n > 0) {
    hanoi(orig, aux, dest, n - 1);
    printf("Mova de %c para %c\n", orig, dest);
    hanoi(aux, dest, orig, n - 1);
  }
}

int main() {
  int n;
  
  printf("São quantos discos? ");
  scanf("%d", &n);
  
  hanoi('A', 'B', 'C', n);
  
  return 0;
}

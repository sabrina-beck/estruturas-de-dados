#include <stdio.h>

double fat(int n) {
  if(n == 0)
    return 1;
  return n * fat(n - 1);
}

int main() {
  int n;
  double fatorial;
  
  do{
    printf("Digite um valor: ");
    scanf("%d", &n);
  } while(n < 0);
  
  fatorial = fat(n);
  
  printf("Fatorial de %d: %.0f\n", n, fatorial);

  return 0;
}

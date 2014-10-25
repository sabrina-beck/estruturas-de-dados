#include <stdio.h>

double fat(int n) {
  int i;
  double fat = 1;
  for(i = 1; i <= n; i++)
    fat *= i;
  return fat;
}

int main() {
  int n;
  double fatorial;
  
  do {
    printf("Digite um valor:");
    scanf("%d", &n);
  } while(n < 0);
  
  fatorial = fat(n);
  
  printf("%d! = %.0f\n", n, fatorial);

  return 0;
}

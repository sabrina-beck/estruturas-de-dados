#include <stdio.h>

int fibonacci(int n) {
  if(n <= 1){
    return n;
  }
  
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  int n;
  
  do {
    printf("Digite um valor inteiro: ");
    scanf("%d", &n);
  } while(n < 0);
  
  printf("Fibonacci: %d\n", fibonacci(n));


  return 0;
}

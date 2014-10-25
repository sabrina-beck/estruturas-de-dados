#include <stdio.h>

int fibonacci(int n) {
  int primeiro = 0, segundo = 1, i, fib = 0;
  
  for(i = 1; i < n; i++) {
    fib = primeiro + segundo;
    primeiro = segundo;
    segundo = fib;
  }

  return fib;
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

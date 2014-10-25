#include <stdio.h>
#include "pilha.h"
#define TAM_MAX 71

bool ehAbertura(char c) {
  return c == '(' || c == '[' || c == '{';
}

char aberturaDe(char c) {
  if(c == ')')
    return '(';
  if(c == ']')
    return '[';
  if(c == '}')
    return '{';
  return '\0';
}

char fechaDe(char c) {
  if(c == '(')
    return ')';
  if(c == '{')
    return '}';
  if(c == '[')
    return ']';
  return '\0';
}

bool analisar(char* expr) {
  Pilha pilha = NULL;
  int i;
  bool deuCerto = true;
  for(i = 0; expr[i]; i++) {
    if(ehAbertura(expr[i]))
      empilhar(&pilha, expr[i]);
    else {
      char info = desempilhar(&pilha);
      char esperado = aberturaDe(expr[i]);
      if (info != esperado) {
        printf("Falta %c\n", esperado);
        return false;
      }
    }
  }
  while(!estaVazia(pilha)) {
    char atual = desempilhar(&pilha);
    printf("Falta %c\n", fechaDe(atual));
    deuCerto = false;
  }
  return deuCerto;
}

int main() {
  char str[TAM_MAX];
  bool ok;

  printf("Digite uma expressão parentética: ");
  scanf("%[^\n]", str);
  
  ok = analisar(str);
  if(ok)
    printf("Expressão está CORRETA.\n");
  else
    printf("Expressão está INCORRETA.\n");
  
  return 0;
}

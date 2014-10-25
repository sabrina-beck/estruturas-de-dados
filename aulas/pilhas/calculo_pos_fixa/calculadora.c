#include <stdio.h>
#include "pilha.h"
#define TAM_MAX_IN 71

bool ehOperador(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '~' || c == '&';
}

int toInt(char c) {
  return c - 48;
}

int resultado(char* posfixa) {
  Pilha pilha = criarPilha();
  int i;
  for(i = 0; posfixa[i]; i++) {
    char atual = posfixa[i];
    if(!ehOperador(atual))
      empilhar(&pilha, toInt(atual));
    else {
      switch(atual) {
        case '~': {
          int op = desempilhar(&pilha);
          empilhar(&pilha, -op);
        }
        break;
        case '&': {
          int op = desempilhar(&pilha);
          empilhar(&pilha, +op);
        }
        break;
        case '+': {
          int op1 = desempilhar(&pilha);
          int op2 = desempilhar(&pilha);
          empilhar(&pilha, op1 + op2);
        }
        break;
        case '-': {
          int op1 = desempilhar(&pilha);
          int op2 = desempilhar(&pilha);
          empilhar(&pilha, op1 - op2);
        }
        break;
        case '*': {
          int op1 = desempilhar(&pilha);
          int op2 = desempilhar(&pilha);
          empilhar(&pilha, op1 * op2);
        }
        break;
        case '/': {
          int op1 = desempilhar(&pilha);
          int op2 = desempilhar(&pilha);
          empilhar(&pilha, op1 / op2);
        }
      }
    }
  }
  
  return desempilhar(&pilha);;
}

int main() {
  char str[TAM_MAX_IN];
  
  printf("Digite uma expressão pos-fixa: ");
  scanf("%[^\n]", str);
  
  printf("Resultado = %d\n", resultado(str));

  return 0;
}

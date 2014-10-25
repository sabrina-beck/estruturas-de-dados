#include "pilha.h"
#include <stdio.h>
#define TAM_MAX_STR 171

bool ehOperador(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^';
}

int precedencia(char c) {
  if(c == '+' || c == '-')
      return 1;

  if(c == '*' || c == '/')
      return 2;
  
  if(c == '^')
    return 3;

  return 0;
}

void paraPosFixa(char* infixa, char* posfixa) {
  Pilha pilha = NULL;
  int indIn, indPos = 0;
  for(indIn = 0; infixa[indIn]; indIn++) {
    char atual = infixa[indIn];
    if(!ehOperador(atual)) {
      posfixa[indPos++] = atual;
    } else if(atual == '(') {
      empilhar(&pilha, atual);
    } else if(atual == ')') {
      char saindo = desempilhar(&pilha);
       
      while(saindo != '(') {
        posfixa[indPos++] = saindo;
        saindo = desempilhar(&pilha);
      }
    } else {
      if(estaVazia(pilha))
        empilhar(&pilha, atual);
      else {
        if((atual == '^' && atual != pilha->info) || atual != '^')
          while(!estaVazia(pilha) && precedencia(pilha->info) >= precedencia(atual)) {
            posfixa[indPos++] = desempilhar(&pilha);
          }
        empilhar(&pilha, atual);
      }
    }
  }
  
  while(!estaVazia(pilha)) {
    posfixa[indPos++] = desempilhar(&pilha);
  }
}
/* a+b*c+(d*a+b)-c */
int main () {
  char infixa[TAM_MAX_STR];
  char posfixa[TAM_MAX_STR];

  printf("Digite uma expressão infixa: ");
  scanf("%[^\n]", infixa);
  
  paraPosFixa(infixa, posfixa);
  
  printf("Pos-fixa: %s\n", posfixa);

  return 0;
}

#include <stdio.h>

char *in, *pos;
int indIn, indPos;

void Expressao() {
  char atual;
  Termo();
  do {
    atual = in[indIn];
    if(atual == '+' || atual == '-') {
      indIn++;
      Termo();
      pos[indPos++] = atual;
    } else
      break;
  } while(true);
}

void Termo() {
  char atual;
  Fator();
  do {
    atual = in[indIn]
    if(atual == '*' || atual == '/') {
      indIn++;
      Fator();
      pos[IndPos++] = atual;
    } else
      break;
  } while(true);
}

void Fator() {
  Primario();
  atual = in[indIn];
  if(atual == '^') {
    indIn++;
    Fator();
    pos[IndPos++] = atual;
  }
}

void Primario() {
  atual = in[indIn];
  if((atual >= 'a' && atual <= 'z') || (atual >= 'A' && atual <= 'Z')) {
    pos[indPos++] = atual;
    indIn++;
  } else if(atual == '(') {
    indIn++;
    Expressao();
    atual = in[indIn];
    if(atual == ')')
      indIn++;
  } else if(atual == '+') {
    indIn++;
    Primario();
    pos[indPos++] = '&';
  } else if(atual == '-') {
    indIn++;
    Primario();
    pos[indPos++] = '~';
  }
}

int main() {

  return 0;
}

/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 05 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: Módulo de transformação de expressões na notação
 * infixa para pós-fixa.
 */

#include "analisador.h"
#include <ctype.h>

typedef enum bool { false, true } bool;

/* Variáveis globais a este módulo */

char *in;  /* Cadeia e índice para expressão infixa (entrada). */
int indIn;

char *pos; /* Cadeia e índice para expressão pósfixa (saída). */
int indPos;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */


/* Protótipos das funções mutuamente recursivas  */
Erro Expressao();
Erro Termo();
Erro Fator();
Erro Primario();
void ignoraBrancos();

/* Função auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma expressão da notação infixa para a pós-fixa. Em caso
   de erro, devolve o código e a posição na cadeia de entrada onde o
   erro foi encontrado.  */
  Erro erro;

  in = infixa;
  indIn = 0;
  pos = posfixa;
  indPos = 0;

  ignoraBrancos();
  if(!in[indIn])
    return montaErro(CADEIA_DE_BRANCOS, indPos);

  erro = Expressao();
  
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  if(in[indIn])
    return montaErro(OPERADOR_ESPERADO, indIn);
  
  posfixa[indPos] = '\0';
  return erro;
  
}

/*************************************************************/
/*           Funções de implementação do analisador          */
/*************************************************************/
bool fimDaCadeia(char c) {
  return c == '\0' || c == '\n';
}

bool caracterValido(char c) {
  return fimDaCadeia(c) || (c >= 'a' && c <= 'z') || c == '(' || c == ')' ||
         c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void ignoraBrancos() {
  char atual = in[indIn];
  if(atual == ' ') {
    indIn++;
    ignoraBrancos();
  }
}

Erro verificaEntrada() {
  char atual;

  ignoraBrancos();

  atual = in[indIn];
    
  if(!caracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  return resCorreto;
}

bool ehFimExpressao(char atual) {
  return atual == ')' || fimDaCadeia(atual);
}

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com código de erro e posição */
  Erro erro;
  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;

} /* montaErro */


Erro Expressao() {
/* Processa uma expressão da cadeia de entrada.  */
  Erro erro = Termo();
  char atual;
  
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  do {
    
    erro = verificaEntrada();
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
      
    atual = in[indIn];
    
    if(atual == '+' || atual == '-') {
      indIn++;
      
      erro = Termo();
      if(erro.codigoErro != EXPR_VALIDA)
        return erro;
      
      pos[indPos++] = atual;
    } else
      break;
  } while (true);

  if(!ehFimExpressao(atual))
    erro = montaErro(OPERADOR_ESPERADO, indIn);
  
  return erro;  

} /* Expressao */

Erro Termo() {
/* Processa um termo da cadeia de entrada.  */

  Erro erro = Fator();
  
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  do {
    char atual;
    
    erro = verificaEntrada();
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    atual = in[indIn];
    
    if(atual == '*' || atual == '/') {
      indIn++;
      
      erro = Fator();
      
      if(erro.codigoErro != EXPR_VALIDA)
          return erro;
      
      pos[indPos++] = atual;
    } else
      break;
  
  } while (true);
  
  return erro;

} /* Termo */


Erro Fator() {
/* Processa um fator da cadeia de entrada.  */
  char atual;
  Erro erro = Primario();
  
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  erro = verificaEntrada();
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  atual = in[indIn];
  if(atual == '^') {
    indIn++;
    
    erro = Fator();
    
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
    
    pos[indPos++] = atual;
  }
  
  return erro;  

} /* Fator */


Erro Primario() {
/* Processa um fator primário da cadeia de entrada.  */
  char atual;
  Erro erro = resCorreto;
  
  erro = verificaEntrada();
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  atual = in[indIn];
  if(atual >= 'a' && atual <= 'z') {
    indIn++;
    pos[indPos++] = atual;
  } else if(atual == '(') {
    indIn++;
    erro = Expressao();
    
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
    
    atual = in[indIn];
    if(atual == ')')
      indIn++;
    else
      return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
  } else if (atual == '+') {
    indIn++;
    erro = Primario();
    
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
    
    pos[indPos++] = '&';
  } else if (atual == '-') {
    indIn++;
    erro = Termo();
    
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    pos[indPos++] = '~';
  } else
    return montaErro(OPERANDO_ESPERADO, indIn);
  
  return erro;

} /* Primario */

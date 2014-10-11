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

/* Enum de boolean */
typedef enum {
  false, true
} boolean;

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
Erro Potencia();
void EliminaBrancos();
boolean ehCaracterValido(char c);

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
  
  /* Verifica cadeia vazia */
  EliminaBrancos();
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

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com código de erro e posição */
  Erro erro;

  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;

} /* montaErro */


Erro Expressao() {
/* Processa uma expressão da cadeia de entrada.  */
  Erro erro;

  /* Se a expressão começar com um operador '+' ou '-', ele é unário */
  if(in[indIn] == '+' || in[indIn] == '-')
    erro = Primario();
  else
    erro = Termo();

  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
    
  if(in[indIn]) {
    boolean fim = false;
    do {
      char atual = in[indIn];
      
      if(!ehCaracterValido(atual))
        return montaErro(CARACTERE_INVALIDO, indIn);
      
      if(atual == '+' || atual == '-') {
        indIn++;
        erro = Termo();
        
        if(erro.codigoErro != EXPR_VALIDA)
          return erro;
        
        pos[indPos++] = atual;
      } else fim = true;
    } while(!fim);
 
  }
  
  return resCorreto;


} /* Expressao */

/*FIXME acertar retornos*/
Erro Termo() {
/* Processa um termo da cadeia de entrada.  */
  Erro erro;

  erro = Fator();
  
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  boolean fim = false;
  do {
    char atual = in[indIn];
    if(!ehCaracterValido(atual))
      return montaErro(CARACTERE_INVALIDO, indIn);
    switch(atual) {
      case '*':
      case '/': {
        indIn++;
        erro = Fator();
        
        if(erro.codigoErro != EXPR_VALIDA)
          return erro;
        
        pos[indPos++] = atual;
      }
      break;
      default:
          fim = true;
    }
  } while(!fim);
  
  return resCorreto;

} /* Termo */

/*FIXME acertar retornos*/
Erro Fator() {
/* Processa um fator da cadeia de entrada.  */
  char atual;
  Erro erro;
  
  EliminaBrancos();
  
  atual = in[indIn];
  
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  if(atual >= 'a' && atual <= 'z') {
    pos[indPos++] = atual;
    indIn++;
  } else if (atual == '(') {
    indIn++;
    erro = Expressao();
    
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    if(in[indIn] == ')')
      indIn++;
    else
      return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
  } else
    return montaErro(OPERANDO_ESPERADO, indIn);
  
  EliminaBrancos();
  
  atual = in[indIn];
  
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  if (atual == '^') {
    indIn++;
    erro = Potencia();
    
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    pos[indPos++] = atual;
  }
  
  return resCorreto;  

} /* Fator */

void EliminaBrancos() {
  if(in[indIn] == ' ') {
    indIn++;
    EliminaBrancos();
  }
  
}

boolean ehCaracterValido(char c) {
  return (c >= 'a' && c <= 'z') || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '\0' 
    || c == ')' || c == '(';
}

Erro Primario() {
/* Processa um fator primário da cadeia de entrada.  */
  char atual;
  int posAnt;
  Erro erro;

  atual = in[indIn];
  
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  indIn++;
  posAnt = indIn;
  erro = Termo();
  
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
    
  if(indIn == posAnt) {
    return montaErro(OPERANDO_ESPERADO, indIn);
  }

  pos[indPos++] = atual == '+' ? '&' : '~';
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Primario */

Erro Potencia() {
/* Processa uma potencia */
  Erro erro;

  erro = Fator();
  
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  char atual = in[indIn];
  
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  if(atual == '^') {
    indIn++;
    erro = Potencia();
    
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    pos[indPos++] = atual;
  } 

  return resCorreto;

} /* Potencia */

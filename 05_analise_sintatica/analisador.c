/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 05 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: M�dulo de transforma��o de express�es na nota��o
 * infixa para p�s-fixa.
 */

#include "analisador.h"
#include <ctype.h>

/* Enum de boolean */
typedef enum {
  false, true
} boolean;

/* Vari�veis globais a este m�dulo */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

char *pos; /* Cadeia e �ndice para express�o p�sfixa (sa�da). */
int indPos;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */


/* Prot�tipos das fun��es mutuamente recursivas  */
Erro Expressao();
Erro Termo();
Erro Fator();
Erro Primario();
Erro Potencia();
void EliminaBrancos();
boolean ehCaracterValido(char c);

/* Fun��o auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma express�o da nota��o infixa para a p�s-fixa. Em caso
   de erro, devolve o c�digo e a posi��o na cadeia de entrada onde o
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
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com c�digo de erro e posi��o */
  Erro erro;

  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;

} /* montaErro */


Erro Expressao() {
/* Processa uma express�o da cadeia de entrada.  */
  Erro erro;

  /* Se a express�o come�ar com um operador '+' ou '-', ele � un�rio */
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
/* Processa um fator prim�rio da cadeia de entrada.  */
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
  
  return resCorreto;  /***** PROVIS�RIO ******/  

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

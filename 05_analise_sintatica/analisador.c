/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 05 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: M�dulo de transforma��o de express�es na nota��o
 * infixa para p�s-fixa.
 */

#include "analisador.h"
#include <ctype.h>

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

/* Fun��o auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma express�o da nota��o infixa para a p�s-fixa. Em caso
   de erro, devolve o c�digo e a posi��o na cadeia de entrada onde o
   erro foi encontrado.  */

  /***** COMPLETAR!  *****/
  
  posfixa[0] = '\0';  /***** PROVIS�RIO ******/  
  return resCorreto;  /***** PROVIS�RIO ******/  
  
}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com c�digo de erro e posi��o */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* montaErro */


Erro Expressao() {
/* Processa uma express�o da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  


} /* Expressao */


Erro Termo() {
/* Processa um termo da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* Termo */


Erro Fator() {
/* Processa um fator da cadeia de entrada.  */


  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* Fator */


Erro Primario() {
/* Processa um fator prim�rio da cadeia de entrada.  */
  


  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVIS�RIO ******/  

} /* Primario */

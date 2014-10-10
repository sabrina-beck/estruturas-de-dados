/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 05 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: Módulo de transformação de expressões na notação
 * infixa para pós-fixa.
 */

#include "analisador.h"
#include <ctype.h>

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

/* Função auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma expressão da notação infixa para a pós-fixa. Em caso
   de erro, devolve o código e a posição na cadeia de entrada onde o
   erro foi encontrado.  */

  /***** COMPLETAR!  *****/
  
  posfixa[0] = '\0';  /***** PROVISÓRIO ******/  
  return resCorreto;  /***** PROVISÓRIO ******/  
  
}

/*************************************************************/
/*           Funções de implementação do analisador          */
/*************************************************************/

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com código de erro e posição */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* montaErro */


Erro Expressao() {
/* Processa uma expressão da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  


} /* Expressao */


Erro Termo() {
/* Processa um termo da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Termo */


Erro Fator() {
/* Processa um fator da cadeia de entrada.  */


  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Fator */


Erro Primario() {
/* Processa um fator primário da cadeia de entrada.  */
  


  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Primario */

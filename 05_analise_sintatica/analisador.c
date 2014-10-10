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
  erro = Expressao();
  
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

  Termo();
  boolean fim = false;
  do {
    char atual = in[indIn];
    if(atual == '+' || atual == '-') {
      indIn++;
      Termo();
      pos[indPos++] = atual;
    } else fim = true;
  } while(!fim);
  
  return resCorreto;  /***** PROVISÓRIO ******/  


} /* Expressao */


Erro Termo() {
/* Processa um termo da cadeia de entrada.  */

  Fator();
  boolean fim = false;
  do {
    char atual = in[indIn];
    if(atual == '*' || atual == '/') {
      indIn++;
      Fator();
      pos[indPos++] = atual;
    } else fim = true;
    
  } while(!fim);
  
  return resCorreto;

} /* Termo */


Erro Fator() {
/* Processa um fator da cadeia de entrada.  */

  char atual = in[indIn];

  if(atual >= 'a' && atual <= 'z') {
    pos[indPos++] = atual;
    indIn++;
  } else if (atual == '(') {
    indIn++;
    Expressao();
    if(in[indIn] == ')')
      indIn++;
    else
      return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
  }
  
  return resCorreto;  

} /* Fator */


Erro Primario() {
/* Processa um fator primário da cadeia de entrada.  */
  


  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Primario */

/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 06 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: Módulo de transformação de expressões em árvores
 * binárias e seus percursos.
 */

#include "analisador.h"
#include <stdlib.h>
#include <ctype.h>
#include "balloc.h"

/* Variáveis globais a este módulo */

char *in;  /* Cadeia e índice para expressão infixa (entrada). */
int indIn;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

/* Macro para desprezar espaços em branco na cadeia de entrada. */
/* Para evitar chamadas desnecessárias a esta macro, adotou-se  */
/* seguinte conveção. A macro é invocada uma vez imediatamente  */
/* antes da primeira chamada à função Expressao e imediatamente */
/* após todo o incremento de indIn.                             */
#define DESPREZA_ESPACOS() while (in[indIn] == ' ') indIn++


/* Protótipos das funções mutuamente recursivas. */
/* O resultado é devolvido através da variável 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);

/* Função auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);


/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a notação infixa em árvore binária.  Em caso de erro,
   devolve o código e a posição na cadeia de entrada onde o erro foi
   encontrado.  */

  /***** COMPLETAR!  *****/
  
  *arv = NULL;        /***** PROVISÓRIO ******/  
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


Erro Expressao(ArvBin *arv) {
/* Processa uma expressão da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  
  
} /* Expressao */


Erro Termo(ArvBin *arv) {
/* Processa um termo da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Termo */


Erro Fator(ArvBin *arv) {
/* Processa um fator da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Fator */


Erro Primario(ArvBin *arv) {
/* Processa um  primário da cadeia de entrada.  */

  /***** COMPLETAR!  *****/
  
  return resCorreto;  /***** PROVISÓRIO ******/  

} /* Primario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representação pré-fixa a partir da árvore. */
 
  /***** COMPLETAR!  *****/

  *pos = '\0';   /***** PROVISÓRIO ******/  

}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representação pós-fixa a partir da árvore. */  

  /***** COMPLETAR!  *****/

  *pos = '\0';   /***** PROVISÓRIO ******/  

}


void LiberaArv(ArvBin arv) {
/* Libera o espaço ocupado pela árvore. */

  /***** COMPLETAR!  *****/


}


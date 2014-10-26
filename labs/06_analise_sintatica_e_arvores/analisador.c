/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 06 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: M�dulo de transforma��o de express�es em �rvores
 * bin�rias e seus percursos.
 */

#include "analisador.h"
#include <stdlib.h>
#include <ctype.h>
#include "balloc.h"

/* Vari�veis globais a este m�dulo */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

/* Macro para desprezar espa�os em branco na cadeia de entrada. */
/* Para evitar chamadas desnecess�rias a esta macro, adotou-se  */
/* seguinte conve��o. A macro � invocada uma vez imediatamente  */
/* antes da primeira chamada � fun��o Expressao e imediatamente */
/* ap�s todo o incremento de indIn.                             */
#define DESPREZA_ESPACOS() while (in[indIn] == ' ') indIn++

typedef enum bool { false, true } bool;

/* Prot�tipos das fun��es mutuamente recursivas. */
/* O resultado � devolvido atrav�s da vari�vel 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);
Erro Unario(ArvBin *arv);
void ignoraBrancos();

/* Fun��o auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);


/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a nota��o infixa em �rvore bin�ria.  Em caso de erro,
   devolve o c�digo e a posi��o na cadeia de entrada onde o erro foi
   encontrado.  */

  in = infixa;
  indIn = 0;
  
  *arv = NULL;
    
  return Expressao(arv);

}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
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
/* Devolve estrutura com c�digo de erro e posi��o */
  Erro erro;
  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;
} /* montaErro */

void criaNoArv(ArvBin *arv) {
  *arv = malloc(sizeof(NoArvBin));
  (*arv)->esq = NULL;
  (*arv)->dir = NULL;
}

Erro Expressao(ArvBin *arv) {
/* Processa uma express�o da cadeia de entrada.  */

  char atual;
  Erro erro;
  ArvBin *noAtual = arv, filhoEsq, filhoDir;
  
  if(in[indIn] == '+' || in[indIn] == '-')
    erro = Unario(noAtual);
  else
    erro = Termo(noAtual);
  
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  do {
    filhoEsq = *noAtual;
    
    erro = verificaEntrada();
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
      
    atual = in[indIn];
    
    if(atual == '+' || atual == '-') {
      criaNoArv(noAtual);
      (*noAtual)->info = atual;
      indIn++;
      
      erro = Termo(&filhoDir);
      if(erro.codigoErro != EXPR_VALIDA)
        return erro;
      
      (*noAtual)->esq = filhoEsq;
      (*noAtual)->dir = filhoDir;
    } else
      break;
  } while (true);

  if(!ehFimExpressao(atual))
    erro = montaErro(OPERADOR_ESPERADO, indIn);
  
  *arv = *noAtual;
  
  return erro;    
} /* Expressao */


Erro Termo(ArvBin *arv) {
/* Processa um termo da cadeia de entrada.  */
  ArvBin *noAtual = arv, filhoEsq, filhoDir;
  Erro erro;
  
  erro = Fator(noAtual);
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  do {
    char atual;
    
    filhoEsq = *noAtual;
    
    erro = verificaEntrada();
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    atual = in[indIn];
    
    if(atual == '*' || atual == '/') {
      criaNoArv(noAtual);
      (*noAtual)->info = atual;
      indIn++;
      
      erro = Fator(&filhoDir);
      
      if(erro.codigoErro != EXPR_VALIDA)
          return erro;
      (*noAtual)->esq = filhoEsq;
      (*noAtual)->dir = filhoDir;
    } else
      break;
  } while (true);
  
  *arv = *noAtual;
  
  return erro;
} /* Termo */


Erro Fator(ArvBin *arv) {
/* Processa um fator da cadeia de entrada.  */
  char atual;
  ArvBin operando, *noAtual;
  Erro erro;

  erro = Primario(&operando);
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  erro = verificaEntrada();
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
                
  noAtual = &operando;
  
  if(*arv != NULL) {
    operando->dir = (*arv)->dir;
    FREE(*arv);
  }
  atual = in[indIn];
  if(atual == '^') {
    ArvBin subarvoreDir;

    criaNoArv(&subarvoreDir);
    subarvoreDir->dir = operando;
    
    criaNoArv(noAtual);
    (*noAtual)->info = atual;
    indIn++;
    
    erro = Fator(&subarvoreDir);
    
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
        
    (*noAtual)->dir = subarvoreDir;
  }
  
  *arv = *noAtual;
  
  return erro;  
} /* Fator */


Erro Primario(ArvBin *arv) {
/* Processa um  prim�rio da cadeia de entrada.  */
  char atual;
  Erro erro = resCorreto;
  
  erro = verificaEntrada();
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  atual = in[indIn];
  if(atual >= 'a' && atual <= 'z') {
    indIn++;
    criaNoArv(arv);
    (*arv)->info = atual;
  } else if(atual == '(') {
    indIn++;
    erro = Expressao(arv);
    
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
    
    atual = in[indIn];
    if(atual == ')')
      indIn++;
    else
      return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
  } else
    return montaErro(OPERANDO_ESPERADO, indIn);
  
  return erro;
} /* Primario */

Erro Unario(ArvBin *arv) {
 char atual = in[indIn];
 Erro erro = resCorreto;
 criaNoArv(arv);

 if (atual == '+') {
    int anterior = indIn++;
   (*arv)->info = '&';
    erro = Termo(&((*arv)->dir));
    
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
        
    if(anterior == indIn)
      return montaErro(OPERANDO_ESPERADO, indIn);
    
  } else if (atual == '-') {
    int anterior = indIn++;
    erro = Termo(&((*arv)->dir));
    
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    if(anterior == indIn)
      return montaErro(OPERANDO_ESPERADO, indIn);
    
     (*arv)->info = '~';
  }
  
  return erro;
} /* Unario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representa��o pr�-fixa a partir da �rvore. */
 
  /***** COMPLETAR!  *****/
  
  *pre = '\0';

}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representa��o p�s-fixa a partir da �rvore. */  

  /***** COMPLETAR!  *****/

  *pos = '\0';   /***** PROVIS�RIO ******/  

}


void LiberaArv(ArvBin arv) {
/* Libera o espa�o ocupado pela �rvore. */

  /***** COMPLETAR!  *****/


}


/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
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

typedef enum bool { false, true } bool;

/* Protótipos das funções mutuamente recursivas. */
/* O resultado é devolvido através da variável 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);
Erro Unario(ArvBin *arv);
void ignoraBrancos();

/* Função auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);


/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a notação infixa em árvore binária.  Em caso de erro,
   devolve o código e a posição na cadeia de entrada onde o erro foi
   encontrado.  */

  in = infixa;
  indIn = 0;
  
  *arv = NULL;
    
  return Expressao(arv);

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

void criaNoArv(ArvBin *arv) {
  *arv = malloc(sizeof(NoArvBin));
  (*arv)->esq = NULL;
  (*arv)->dir = NULL;
}

Erro Expressao(ArvBin *arv) {
/* Processa uma expressão da cadeia de entrada.  */

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
/* Processa um  primário da cadeia de entrada.  */
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
 /* Produz a representação pré-fixa a partir da árvore. */
 
  /***** COMPLETAR!  *****/
  
  *pre = '\0';

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


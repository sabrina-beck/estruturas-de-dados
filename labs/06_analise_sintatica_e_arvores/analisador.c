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
#include <string.h>

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
bool fimDaCadeia(char c);

/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a nota��o infixa em �rvore bin�ria.  Em caso de erro,
   devolve o c�digo e a posi��o na cadeia de entrada onde o erro foi
   encontrado.  */
  Erro erro;

  /* Inicializa string infixa usada na convers�o */
  in = infixa;
  indIn = 0;
  
  /* Inicializa �rvore */
  *arv = NULL;
  
  /* Verifica se n�o � uma cadeia de caractere brancos */
  ignoraBrancos();
  if(!in[indIn])
    return montaErro(CADEIA_DE_BRANCOS, 0);
  
  /* Transforma a express�o infixa em uma �rvore bin�ria de express�o */
  erro = Expressao(arv);

  /* Verifica se houve algum erro na transforma��o */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  /*
   * Se ainda tiver dados na cadeia infixa para serem interpretados,
   * significa que falta algum operador, uma vez que o algoritmo encerra
   * quando n�o acha o operador esperado
   */
  if(!fimDaCadeia(in[indIn]))
    erro = montaErro(OPERADOR_ESPERADO, indIn);
  
  return erro;

}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

/*
 * Verifica se o caracter representa o fim de cadeia de caracteres
 */
bool fimDaCadeia(char c) {
  return c == '\0' || c == '\n';
}

/*
 * Verifica se o caracter � um caracter previsto pela implementa��o
 */
bool caracterValido(char c) {
  return fimDaCadeia(c) || (c >= 'a' && c <= 'z') || c == '(' || c == ')' ||
         c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/*
 * Ignora caractere em branco, uma vez que n�o significam erro
 * na cadeia de entrada e nem um dado de entrada
 */
void ignoraBrancos() {
  char atual = in[indIn];
  if(atual == ' ') {
    indIn++;
    ignoraBrancos();
  }
}

/*
 * Faz o tratamento da entrada ignorando caracteres em branco e
 * verificando caracteres inv�lidos
 */
Erro trataEntrada() {
  char atual;

  ignoraBrancos();

  atual = in[indIn];

  /* Verifica se o caracter atual � previsto pela implementa��o, se � v�lido */    
  if(!caracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  return resCorreto;
}

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com c�digo de erro e posi��o */
  Erro erro;
  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;
} /* montaErro */

/*
 * Cria um N� de �rvore, com filhos nulos,
 * concentra c�digo de aloca��o din�mica
 */
void criaNoArv(ArvBin *arv) {
  *arv = MALLOC(sizeof(NoArvBin));
  (*arv)->esq = NULL;
  (*arv)->dir = NULL;
}

Erro Expressao(ArvBin *arv) {
/* Processa uma express�o da cadeia de entrada.  */

  char atual;
  Erro erro;
  /* noAtual ter� a �rvore resultante no fim do algoritimo */
  ArvBin *noAtual = arv, filhoEsq;
  
  /* Se a express�o come�ar com um operador '+' ou '-', ele � un�rio */
  if(in[indIn] == '+' || in[indIn] == '-')
    erro = Unario(noAtual);
  else
  /*
   * Caso n�o tenha um operador un�rio no in�cio da express�o, ent�o 
   * o primeiro termo � tratado
   */
    erro = Termo(noAtual);
  
  /*
   * Essa verifica��o � necess�ria sempre que um m�todo retornar erro, pois neste caso, n�o � necess�rio
   * continuar a an�lise (nem poss�vel continuar) , uma vez errada a express�o a recurs�o/m�todo/an�lise deve
   * ser interrompida e o erro retornado para tratamento no programa principal.
   */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  do {
    /*
     * Caso haja um operador de express�o ('+' ou '-') ent�o o primeiro termo analisado � filho esquerdo
     * do operador na arvore bin�ria de express�o resultante
     */
    filhoEsq = *noAtual;
    
    /* Tratamento de caracteres inv�lidos e espa�os em branco */
    erro = trataEntrada();
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    atual = in[indIn];
    if(atual == '+' || atual == '-') {
      /*
       * Cria �rvore equivalente � opera��o atual, ou seja,
       * a raiz ser� o operador encontrado ('+' ou '-') seu 
       * filho esquerdo ser� a �ltima opera��o (parte da express�o ou um termo)
       * analisada e seu filho direito ser� o pr�ximo termo analisado
       */
      criaNoArv(noAtual);
      (*noAtual)->info = atual;
      (*noAtual)->esq = filhoEsq;

      /* Controle do �ndice atual na cadeia de entrada */
      indIn++;
      
      /*
       * Para cada operador '+' e '-' existe um termo a ser avaliado,
       * sendo este o filho direito do operador atual
       */
      erro = Termo(&((*noAtual)->dir));
      
      /*
       * Verifica��o necess�ria para n�o continuar a an�lise em express�o errada
       * Tamb�m desaloca a mem�ria necess�ria
       */
      if(erro.codigoErro != EXPR_VALIDA) {
        LiberaArv(*noAtual);
        return erro;
      }
    } else
      /* Se n�o achar mais operadores, ent�o a express�o acabou */
      break;
  } while (true);
  
  /* No fim, noAtual ter� a �rvore resultante */
  *arv = *noAtual;
  
  return erro;    
} /* Expressao */


Erro Termo(ArvBin *arv) {
/* Processa um termo da cadeia de entrada.  */
  /* noAtual ter� a �rvore resultante no fim do algoritimo */
  ArvBin *noAtual = arv, filhoEsq;
  Erro erro;
  
  /* Todo termo come�a com um fator a ser analisado */
  erro = Fator(noAtual);
  
  /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  do {
    char atual;
    
    /*
     * Se existir algum operador de termo '*' ou '/' o primeiro fator
     * analisado ser� filho esquerdo deste operador
     */
    filhoEsq = *noAtual;
    
    /* Tratamento de caracteres inv�lidos e espa�os em branco */
    erro = trataEntrada();
    
    /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    atual = in[indIn];
    if(atual == '*' || atual == '/') {
      /*
       * Cria �rvore equivalente � opera��o atual, ou seja,
       * a raiz ser� o operador encontrado ('*' ou '/') seu 
       * filho esquerdo ser� a �ltima opera��o (parte do termo ou um fator)
       * analisada e seu filho direito ser� o pr�ximo fator analisado
       */
      criaNoArv(noAtual);
      (*noAtual)->info = atual;
      (*noAtual)->esq = filhoEsq;
      
      /* Controle do �ndice atual na cadeia de entrada */
      indIn++;
      
      /*
       * Para cada operador '*' e '/' existe um fator a ser avaliado,
       * sendo este o filho direito do operador atual
       */
      erro = Fator(&((*noAtual)->dir));
      
      /*
       * Verifica��o necess�ria para n�o continuar a an�lise em express�o errada
       * Tamb�m desaloca a mem�ria necess�ria
       */
      if(erro.codigoErro != EXPR_VALIDA) {
          LiberaArv(*noAtual);
          return erro;
      }
    } else
      /* Se n�o achar mais operadores, ent�o o termo acabou */
      break;
  } while (true);
  
  /* No fim, noAtual ter� a �rvore resultante */
  *arv = *noAtual;
  
  return erro;
} /* Termo */


Erro Fator(ArvBin *arv) {
/* Processa um fator da cadeia de entrada.  */
  char atual;
  Erro erro;

  /* Um fator come�a com um prim�rio */
  erro = Primario(arv);
  
  /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  /* Tratamento de caracteres inv�lidos e espa�os em branco */
  erro = trataEntrada();
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
                
  atual = in[indIn];
  /* Um fator � uma sequ�ncia de pot�ncias */
  if(atual == '^') {
    /*
     * A �rvore resultante ter� como raiz o operador de potencia '^',
     * seu filho esquerdo ser� o prim�rio lido nessa chamada e seu
     * filho esquerdo ser� composta pelo fator analisado posteriormente
     */
    ArvBin aux = *arv;
    criaNoArv(arv);
    (*arv)->esq = aux;
    (*arv)->info = atual;
    
    /* Controle do �ndice atual na cadeia de entrada */
    indIn++;
    
    /*
     * Para cada operador '^' existe um fator a ser avaliado,
     * sendo este o filho direito do operador atual
     */
    erro = Fator(&((*arv)->dir));
    
    /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
  }
  
  return erro;  
} /* Fator */


Erro Primario(ArvBin *arv) {
/* Processa um  prim�rio da cadeia de entrada.  */
  char atual;
  Erro erro = resCorreto;
  
  erro = trataEntrada();
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

 /* Os �nicos operadores un�rios existentes s�o '+' e '-' */
 if (atual == '+') {
    int anterior = indIn++; /* controle para ver se h� realmente um operando
                               para esse operador */

    /*
     * Na �rvore de express�o a ra�z ser� o operador un�rio e seu filho
     * direito ser� o termo correspondente
     */
    (*arv)->info = '&';
    erro = Termo(&((*arv)->dir));
    
    /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
    
    /* Verifica se h� realmente um operando para esse operador */
    if(anterior == indIn)
      return montaErro(OPERANDO_ESPERADO, indIn);
    
  } else if (atual == '-') {
    int anterior = indIn++; /* controle para ver se h� realmente um operando
                               para esse operador */
                               
    /*
     * Na �rvore de express�o a ra�z ser� o operador un�rio e seu filho
     * direito ser� o termo correspondente
     */                            
    (*arv)->info = '~';
    erro = Termo(&((*arv)->dir));
    
    /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /* Verifica se h� realmente um operando para esse operador */
    if(anterior == indIn)
      return montaErro(OPERANDO_ESPERADO, indIn);
    
  }
  
  return erro;
} /* Unario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representa��o pr�-fixa a partir da �rvore. */
 
  if(arv != NULL) {
    /*
     * Como o resultado deve estar na cadeia pre,
     * o dado analisado atualmente � o primeiro da cadeia,
     * depois ela � usada para armazenar o percurso na sub�rvore esquerda
     * e posteriormente � concatenada com o percurso da sub�rvore direito
     */
    char preDir[TAM_MAX_EXPR + 1];
    *pre = arv->info;
    ArvPre(arv->esq, pre + 1);
    ArvPre(arv->dir, preDir);
    strcat(pre, preDir);
  } else
    /* Por �ltimo deve ser informado o fim da cadeia */
    *pre = '\0';

}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representa��o p�s-fixa a partir da �rvore. */  

  if(arv != NULL) {
    /*
     * Como o resultado deve estar na cadeia pos,
     * primeiro ela � usada para armazenar o percurso na sub�rvore esquerda
     * depois ela � concatenada com o percurso da sub�rvore direita
     * e por ultimo, o dado atualmente lido � concatenado a cadeia
     */
    char posDir[TAM_MAX_EXPR + 1], atual[2];
    atual[0] = arv->info;
    atual[1] = '\0'; /* Garante que a string final tenha o delimitador '\0' */
    ArvPos(arv->esq, pos);
    ArvPos(arv->dir, posDir);
    strcat(pos, posDir);
    strcat(pos, atual);
  } else
    /* Por �ltimo deve ser informado o fim da cadeia */
    *pos = '\0';

}


void LiberaArv(ArvBin arv) {
/* Libera o espa�o ocupado pela �rvore. */
  /*
   * Para liberar o espa�o alocado da �rvore devemos
   * desalocar a raiz por ultimo (para n�o perder a referencia
   * para seus filhos, para isso, usamos o percurso pos-ordem
   */
  if(arv != NULL) {
    LiberaArv(arv->esq);
    LiberaArv(arv->dir);
    FREE(arv);
  }
}


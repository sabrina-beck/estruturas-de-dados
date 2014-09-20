/* M�dulo de c�lculo de express�es p�s-fixas sobre uma base de dados     */
/* formada por polin�mios em uma vari�vel.                               */
/*************************************************************************/
/* Sabrina Beck Angelini                                        RA157240 */
/* Turma: E                                                              */
/* Data: 20/09/2014                                                      */
/*************************************************************************/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "pilha.h"
#include "polinomios.h"
#include "balloc.h"
#include "boolean.h"

/* Mensagens de erro para este m�dulo.                                     */

#define MSG_ERRO_NOME_INVALIDO "nome inv�lido para a base de polin�mios."
#define MSG_ERRO_POLINOMIO_NAO_INICIALIZADO "tentativa de recuperar polin�mio n�o inicializado."
#define MSG_ERRO_FALTA_OPERANDO "n�mero insuficiente de operandos."
#define MSG_ERRO_FALTA_OPERADOR  "n�mero insuficiente de operandores."
#define MSG_ERRO_CARACTERE_INVALIDO "caractere inv�lido."

#define IMPRIME_ERRO(msg)  {printf("Erro: %s\n",msg); exit(0); }

#define TAM_BASE 5
Polinomio vetorPoli[TAM_BASE];

void InicializaBasePolinomios() {
/* Inicializa polin�mios com NULL, indicando que n�o h� polin�mios       */
/* v�lidos na base.                                                      */ 
  int i;
  for (i = 0; i < TAM_BASE; i++)
    vetorPoli[i] = NULL;
}

Polinomio RecuperaPolinomio(char x) {
/* Retorna o polin�mio de nome x.                                        */
  Polinomio poli;
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    poli =  vetorPoli[x - 'A'];
  else {
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
    return NULL;
  }
  
  if (poli == NULL)
    IMPRIME_ERRO(MSG_ERRO_POLINOMIO_NAO_INICIALIZADO);

  return poli;
}

void ArmazenaPolinomio(char x, Polinomio p) {
/* Armazena o polin�mio p sob o nome x na base.                          */
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    vetorPoli[x - 'A'] = p;
  else 
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
}

/*** C�lculo da express�o                                                 */

/* Defini��o dos elementos da pilha. Polin�mios tempor�rios devem ser     */
/* liberados ap�s terem sido utilizados. Polin�mios da base s� s�o        */
/* liberados quando o usu�rio invoca libera.                              */ 
typedef struct ElemPilha {
  Polinomio poli;
  Boolean temp; 
} ElemPilha;

ElemPilha* VerificaDesempilha (Pilha* pilha) {
/* Desempilha um elemento, enviando uma mensagem de erro caso a pilha      */
/* esteja vazia.                                                           */
  if (PilhaVazia(pilha)) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
    return NULL;
  }
  return (ElemPilha*) Desempilha(pilha);
}

void EmpilhaOperando(Pilha* pilha, Polinomio poli, Boolean temp) {
/* Cria e empilha um n� do tipo ElemPilha.                                 */
  ElemPilha *elem = MALLOC (sizeof(ElemPilha));
  elem->poli = poli; 
  elem->temp = temp; 
  Empilha (pilha, elem);
}

Boolean Operando(char c) {
/* Verifica se um caractere corresponde a um operando v�lido.              */
   return (c >= 'a' && c < 'a'+TAM_BASE) || (c >= 'A' && c < 'A'+TAM_BASE);
}

void liberaElemPilha(ElemPilha *elem) {
/* Libera a mem�ria ocupada por um elemento da pilha */
  if(elem->temp) {
  /* Se o elemento aponta para um polin�mio tempor�rio,
   * este deve ser liberado
   */
    LiberaPolinomio(elem->poli);
  }
  FREE(elem);
}

/* Declara��o gen�rica de uma opera��o bin�ria com polinomios */
typedef Polinomio (funcao)(Polinomio a, Polinomio b);

/* 
 * Calcula uma opera��o bin�ria com polinomios considerando os dois
 * elementos do topo da pilha, recebe a opera��o por par�metro
 */
void calculaOperacaoBinaria(Pilha *pilha, funcao *operacao) {
  /*
   * Desempilha operandos dessa opera��o, dois pois � opera��o bin�ria
   */
  ElemPilha *operandoDir = VerificaDesempilha(pilha);
  ElemPilha *operandoEsq = VerificaDesempilha(pilha);
  
  /*
   * Se algum operando estiver nulo, ent�o a quantidade de operandos
   * n�o bate e a express�o est� errada
   */
  if(operandoDir == NULL || operandoEsq == NULL) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
    exit(0);
  }

  /* Empilha o resultado da opera��o */  
  EmpilhaOperando(pilha, operacao(operandoEsq->poli, operandoDir->poli) , true);

  /* Libera a mem�ria de antigos operandos tempor�rios */
  liberaElemPilha(operandoEsq);
  liberaElemPilha(operandoDir);
}

/*
 * Retorna uma copia do polinomio orig, para os casos em que o resultado da
 * express�o � um polinomio n�o tempor�rio, ou seja, da base de dados
 * Eu ficaria mais feliz se essa fun��o ficasse no arquivo polinomios.c,
 * mas n�o posso alterar a interface polinomios.h, por isso ela est� aqui
 */
Polinomio copia(Polinomio orig) {
  Polinomio poli = CriaPolinomioNulo();
  Polinomio atual = orig->prox;
  while(atual->expo != -1){ /* Percorre at� achar o cabe�a */
    InsereTermo(poli, atual->expo, atual->coef);
    atual = atual->prox;
  }
  return poli;
}

Polinomio CalcExpr(char* expr) { 
/* Retorna o polin�mio referente � express�o dada.                       */
/* O polin�mio devolvido � sempre uma nova c�pia, mesmo que a            */
/* express�o seja uma vari�vel simples.                                  */
  int i;
  ElemPilha *resultado;
  Polinomio polinomioResultante;
  Pilha pilha;
  CriaPilha(&pilha);
  /* Percorre a express�o */
  for(i = 0; expr[i]; i++) {
    char lido = expr[i];
    if(Operando(lido)) {
      /*
       * Sendo o carcter lido um operando, seu respectivo polinomio
       * � empilhado para futuros c�lculos
       */
      Polinomio poli = RecuperaPolinomio(lido);
      EmpilhaOperando(&pilha, poli, false);
    } else {
      /*
       * Caso seja um operador bin�rio os dois elementos do topo da pilha
       * s�o desempilhados e o resultado da opera��o � empilhada
       * Caso seja um operador un�rio, o elemento do topo � desempilhado
       * e o resultado da opera��o � empilhado
       */
      switch(lido) {
        case '+': {
          /* Soma os operandos */
          calculaOperacaoBinaria(&pilha, SomaPolinomios);
        }
        break;
        case '-': {
          /* Subtrai os operandos */
          calculaOperacaoBinaria(&pilha, SubPolinomios);
        }
        break;
        case '~': {
          /* Desempilha o �nico operando */
          ElemPilha *operando = VerificaDesempilha(&pilha);
          
          /*
           * Se o operando for nulo, ent�o a quantidade de operandos
           * n�o bate e a express�o est� errada
           */
          if(operando == NULL) {
            IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
            exit(0);
          }
          
          /* Empilha o resultado */
          EmpilhaOperando(&pilha, MultTermo(operando->poli, 0, -1), true);
          
          /* Libera mem�ria de antigos operandos */
          liberaElemPilha(operando);
        }
        break;
        case '*': {
          /* Multiplica os operandos */
          calculaOperacaoBinaria(&pilha, MultPolinomios);
        }
        case '\n':
        break;
        default: {
          IMPRIME_ERRO(MSG_ERRO_CARACTERE_INVALIDO);
          exit(0);
        }
      }
    }
  }
  
  /*
   * No final, o topo da pilha cont�m o resultado da express�o,
   * por isso, se a pilha estiver vazia, ent�o faltaram operandos
   */
  if(PilhaVazia(&pilha)) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
    exit(0);
  }
  
  /* Desempilha o resultado */
  resultado = VerificaDesempilha(&pilha);
  polinomioResultante = resultado->poli;
  
  /*
   * Se a pilha ainda tiver elementos, significa que sobraram
   * operados sem operadores, logo a express�o estava errada
   */
  if(!PilhaVazia(&pilha)) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERADOR);
    exit(0);
  }
  
  /* 
   * Caso o resultado seja um polin�mio da base de dados, uma
   * copia dele � feita para futuro armazenamento
   */
  if(!resultado->temp) {
    FREE(resultado);
    return copia(polinomioResultante);
  }
  
  FREE(resultado);
  return polinomioResultante;

}

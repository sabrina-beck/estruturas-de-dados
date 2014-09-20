/* Módulo de cálculo de expressões pós-fixas sobre uma base de dados     */
/* formada por polinômios em uma variável.                               */
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

/* Mensagens de erro para este módulo.                                     */

#define MSG_ERRO_NOME_INVALIDO "nome inválido para a base de polinômios."
#define MSG_ERRO_POLINOMIO_NAO_INICIALIZADO "tentativa de recuperar polinômio não inicializado."
#define MSG_ERRO_FALTA_OPERANDO "número insuficiente de operandos."
#define MSG_ERRO_FALTA_OPERADOR  "número insuficiente de operandores."
#define MSG_ERRO_CARACTERE_INVALIDO "caractere inválido."

#define IMPRIME_ERRO(msg)  {printf("Erro: %s\n",msg); exit(0); }

#define TAM_BASE 5
Polinomio vetorPoli[TAM_BASE];

void InicializaBasePolinomios() {
/* Inicializa polinômios com NULL, indicando que não há polinômios       */
/* válidos na base.                                                      */ 
  int i;
  for (i = 0; i < TAM_BASE; i++)
    vetorPoli[i] = NULL;
}

Polinomio RecuperaPolinomio(char x) {
/* Retorna o polinômio de nome x.                                        */
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
/* Armazena o polinômio p sob o nome x na base.                          */
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    vetorPoli[x - 'A'] = p;
  else 
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
}

/*** Cálculo da expressão                                                 */

/* Definição dos elementos da pilha. Polinômios temporários devem ser     */
/* liberados após terem sido utilizados. Polinômios da base só são        */
/* liberados quando o usuário invoca libera.                              */ 
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
/* Cria e empilha um nó do tipo ElemPilha.                                 */
  ElemPilha *elem = MALLOC (sizeof(ElemPilha));
  elem->poli = poli; 
  elem->temp = temp; 
  Empilha (pilha, elem);
}

Boolean Operando(char c) {
/* Verifica se um caractere corresponde a um operando válido.              */
   return (c >= 'a' && c < 'a'+TAM_BASE) || (c >= 'A' && c < 'A'+TAM_BASE);
}

void liberaElemPilha(ElemPilha *elem) {
/* Libera a memória ocupada por um elemento da pilha */
  if(elem->temp) {
  /* Se o elemento aponta para um polinômio temporário,
   * este deve ser liberado
   */
    LiberaPolinomio(elem->poli);
  }
  FREE(elem);
}

/* Declaração genérica de uma operação binária com polinomios */
typedef Polinomio (funcao)(Polinomio a, Polinomio b);

/* 
 * Calcula uma operação binária com polinomios considerando os dois
 * elementos do topo da pilha, recebe a operação por parâmetro
 */
void calculaOperacaoBinaria(Pilha *pilha, funcao *operacao) {
  /*
   * Desempilha operandos dessa operação, dois pois é operação binária
   */
  ElemPilha *operandoDir = VerificaDesempilha(pilha);
  ElemPilha *operandoEsq = VerificaDesempilha(pilha);
  
  /*
   * Se algum operando estiver nulo, então a quantidade de operandos
   * não bate e a expressão está errada
   */
  if(operandoDir == NULL || operandoEsq == NULL) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
    exit(0);
  }

  /* Empilha o resultado da operação */  
  EmpilhaOperando(pilha, operacao(operandoEsq->poli, operandoDir->poli) , true);

  /* Libera a memória de antigos operandos temporários */
  liberaElemPilha(operandoEsq);
  liberaElemPilha(operandoDir);
}

/*
 * Retorna uma copia do polinomio orig, para os casos em que o resultado da
 * expressão é um polinomio não temporário, ou seja, da base de dados
 * Eu ficaria mais feliz se essa função ficasse no arquivo polinomios.c,
 * mas não posso alterar a interface polinomios.h, por isso ela está aqui
 */
Polinomio copia(Polinomio orig) {
  Polinomio poli = CriaPolinomioNulo();
  Polinomio atual = orig->prox;
  while(atual->expo != -1){ /* Percorre até achar o cabeça */
    InsereTermo(poli, atual->expo, atual->coef);
    atual = atual->prox;
  }
  return poli;
}

Polinomio CalcExpr(char* expr) { 
/* Retorna o polinômio referente à expressão dada.                       */
/* O polinômio devolvido é sempre uma nova cópia, mesmo que a            */
/* expressão seja uma variável simples.                                  */
  int i;
  ElemPilha *resultado;
  Polinomio polinomioResultante;
  Pilha pilha;
  CriaPilha(&pilha);
  /* Percorre a expressão */
  for(i = 0; expr[i]; i++) {
    char lido = expr[i];
    if(Operando(lido)) {
      /*
       * Sendo o carcter lido um operando, seu respectivo polinomio
       * é empilhado para futuros cálculos
       */
      Polinomio poli = RecuperaPolinomio(lido);
      EmpilhaOperando(&pilha, poli, false);
    } else {
      /*
       * Caso seja um operador binário os dois elementos do topo da pilha
       * são desempilhados e o resultado da operação é empilhada
       * Caso seja um operador unário, o elemento do topo é desempilhado
       * e o resultado da operação é empilhado
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
          /* Desempilha o único operando */
          ElemPilha *operando = VerificaDesempilha(&pilha);
          
          /*
           * Se o operando for nulo, então a quantidade de operandos
           * não bate e a expressão está errada
           */
          if(operando == NULL) {
            IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
            exit(0);
          }
          
          /* Empilha o resultado */
          EmpilhaOperando(&pilha, MultTermo(operando->poli, 0, -1), true);
          
          /* Libera memória de antigos operandos */
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
   * No final, o topo da pilha contém o resultado da expressão,
   * por isso, se a pilha estiver vazia, então faltaram operandos
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
   * operados sem operadores, logo a expressão estava errada
   */
  if(!PilhaVazia(&pilha)) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERADOR);
    exit(0);
  }
  
  /* 
   * Caso o resultado seja um polinômio da base de dados, uma
   * copia dele é feita para futuro armazenamento
   */
  if(!resultado->temp) {
    FREE(resultado);
    return copia(polinomioResultante);
  }
  
  FREE(resultado);
  return polinomioResultante;

}

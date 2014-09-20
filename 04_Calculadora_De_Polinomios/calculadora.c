/* Módulo de cálculo de expressões pós-fixas sobre uma base de dados     */
/* formada por polinômios em uma variável.                               */

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

Polinomio CalcExpr(char* expr) { 
/* Retorna o polinômio referente à expressão dada.                       */
/* O polinômio devolvido é sempre uma nova cópia, mesmo que a            */
/* expressão seja uma variável simples.                                  */

  /*----- COMPLETAR -----*/
  return NULL;        // resultado temporário

}

/* Implementação de pilhas. Os elementos empilhados são do tipo void*.     */
/*************************************************************************/
/* Sabrina Beck Angelini                                        RA157240 */
/* Turma: E                                                              */
/* Data: 20/09/2014                                                      */
/*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/* Mensagens de erro para este módulo.                                     */
#define MSG_ERRO_PILHA_CHEIA "número máximo de elementos na pilha excedido."
#define MSG_ERRO_PILHA_VAZIA "tentativa de desempilhar elemento de pilha vazia."

#define IMPRIME_ERRO(msg)  {printf("%s\n",msg); exit(0); }


void CriaPilha (Pilha* p) {
/* Inicializa uma pilha.                                                   */
  p->topo = -1;
}

Boolean PilhaVazia (Pilha* p) {
/* Verifica se a pilha está vazia.                                         */
  return p->topo == -1; /*-- PROVISÓRIO --*/
}

void Empilha (Pilha* p, void *elem) {
/* Empilha um elemento na pilha.                                           */
  /* Se a pilha está cheia não é possível empilhar */
  if(p->topo == MAX_ELEM_PILHA-1) {
    IMPRIME_ERRO(MSG_ERRO_PILHA_CHEIA);
    exit(0);
  }
  /* O topo vai sobe uma posição e o elemento é armazenado */
  p->topo++;
  p->vetor[p->topo] = elem;
}

void* Desempilha (Pilha* p) {
/* Desempilha um elemento da pilha.                                        */ 
  /* Se a pilha está vazia, não é possível desempilhar */
  if(PilhaVazia(p)) {
    IMPRIME_ERRO(MSG_ERRO_PILHA_VAZIA);
    exit(0);
  }
  /* O topo desce uma posição e o elemento removido é retornado */
  return p->vetor[p->topo--];
}


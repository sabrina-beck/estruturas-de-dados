/* Implementa��o de pilhas. Os elementos empilhados s�o do tipo void*.     */
/*************************************************************************/
/* Sabrina Beck Angelini                                        RA157240 */
/* Turma: E                                                              */
/* Data: 20/09/2014                                                      */
/*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/* Mensagens de erro para este m�dulo.                                     */
#define MSG_ERRO_PILHA_CHEIA "n�mero m�ximo de elementos na pilha excedido."
#define MSG_ERRO_PILHA_VAZIA "tentativa de desempilhar elemento de pilha vazia."

#define IMPRIME_ERRO(msg)  {printf("%s\n",msg); exit(0); }


void CriaPilha (Pilha* p) {
/* Inicializa uma pilha.                                                   */
  p->topo = -1;
}

Boolean PilhaVazia (Pilha* p) {
/* Verifica se a pilha est� vazia.                                         */
  return p->topo == -1; /*-- PROVIS�RIO --*/
}

void Empilha (Pilha* p, void *elem) {
/* Empilha um elemento na pilha.                                           */
  /* Se a pilha est� cheia n�o � poss�vel empilhar */
  if(p->topo == MAX_ELEM_PILHA-1) {
    IMPRIME_ERRO(MSG_ERRO_PILHA_CHEIA);
    exit(0);
  }
  /* O topo vai sobe uma posi��o e o elemento � armazenado */
  p->topo++;
  p->vetor[p->topo] = elem;
}

void* Desempilha (Pilha* p) {
/* Desempilha um elemento da pilha.                                        */ 
  /* Se a pilha est� vazia, n�o � poss�vel desempilhar */
  if(PilhaVazia(p)) {
    IMPRIME_ERRO(MSG_ERRO_PILHA_VAZIA);
    exit(0);
  }
  /* O topo desce uma posi��o e o elemento removido � retornado */
  return p->vetor[p->topo--];
}


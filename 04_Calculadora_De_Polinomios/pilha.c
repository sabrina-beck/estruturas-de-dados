/* Implementação de pilhas. Os elementos empilhados são do tipo void*.     */

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
  if(p->topo == MAX_ELEM_PILHA-1)
    IMPRIME_ERRO(MSG_ERRO_PILHA_CHEIA);
  p->topo++;
  p->vetor[p->topo] = elem;
}

void* Desempilha (Pilha* p) {
/* Desempilha um elemento da pilha.                                        */ 
  if(p->topo == -1)
    IMPRIME_ERRO(MSG_ERRO_PILHA_VAZIA);
  return p->vetor[p->topo--];
}


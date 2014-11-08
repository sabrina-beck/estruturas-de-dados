/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turmas:        E e F
  
  Tarefa 10
  Segundo semestre de 2014

*/
/* Arquivo trie.c:

   Implementa��o de �rvores digitais (ADs) atrav�s de um tipo
   abstrato de dados usando apontadores "void *".

   Todas as defini��es est�o no arquivo "trie.h".

*/

#include <stdio.h>

#include "trie.h"
#include "balloc.h"

typedef struct RegTrie * ImplTrie;

typedef struct RegTrie {
  Boolean fim;                 /* t�rmino de uma cadeia */
  ImplTrie subarv[TAM_ALFABETO]; /* vetor de sub�rvores */
} RegTrie;



/* ------------------------------------------------------------ */
/*          Sugest�es de algumas fun��es auxiliares             */
/* ------------------------------------------------------------ */

ImplTrie criaInicializaNo() {
/* Devolve um n� com a marca de fim de cadeia falsa e todas as
   sub�rvores vazias; usada para criar a AD inicial e durante a
   inser��o.
*/
   
  ImplTrie p = MALLOC(sizeof(RegTrie));
  if (p==NULL) {
    printf("Mem�ria esgotada\n");
    exit(0);
  }
  p->fim = false;
  for (int k=0; k<TAM_ALFABETO; k++)
    p->subarv[k] = NULL;
  return p;

}


Boolean livre(ImplTrie t) {
/* Devolve verdadeiro se o n� 't' n�o � final e � uma folha; usada
   durante a remo��o.
*/
  
  /* COMPLETAR!! */
  
  return false;  /* PROVIS�RIO */

}


void percorreAux(ImplTrie t, funcVisita *v, char *buf, int m) {
/* Percorre a AD em ordem lexicogr�fica; constroi as cadeias em 'buf'
  e aplica a fun��o 'v' quando termina uma cadeia, colocando no fim o
  caractere '\0'; 'm' � o �ndice do pr�ximo caractere em 'buf'.
*/

  /* COMPLETAR!! */

}


/* ------------------------------------------------------------ */
/*                      Fim das sugest�es                       */
/* ------------------------------------------------------------ */


Trie CriaAD() {
  
  return criaInicializaNo();
  
}


Boolean consultaAD(Trie t, char *s) {

  /* COMPLETAR!! */
  
  return false;  /* PROVIS�RIO */

}


Boolean insereAD(Trie t, char *s) {

  /* COMPLETAR!! */
  
  return false;  /* PROVIS�RIO */

}

  
int numCadeiasAD(Trie t) {
  
  /* COMPLETAR!! */
  
  return 0;  /* PROVIS�RIO */

}


Boolean removeAD(Trie t, char *s) {

  /* COMPLETAR!! */
  
  return false;  /* PROVIS�RIO */

}


void percorreAD(Trie t, funcVisita *v) {
  
  char buf[TAM_MAX_CADEIA];
  
  percorreAux((ImplTrie)t,v,buf,0);
  
}

void liberaAD(Trie t) {

  /* COMPLETAR!! */

}


/* 
  Fun��es usadas somente para verifica��o; conceitualmente
  n�o fazem parte da implementa��o.
*/
   
int numNosAD(Trie t) {

  /* COMPLETAR!! */
  
  return 0;  /* PROVIS�RIO */

}

int alturaAD(Trie t) {

  /* COMPLETAR!! */
  
  return 0;  /* PROVIS�RIO */

}



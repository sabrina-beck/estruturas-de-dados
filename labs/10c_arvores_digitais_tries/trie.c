/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 10
  Segundo semestre de 2014

*/
/* Arquivo trie.c:

   Implementação de árvores digitais (ADs) através de um tipo
   abstrato de dados usando apontadores "void *".

   Todas as definições estão no arquivo "trie.h".

*/

#include <stdio.h>

#include "trie.h"
#include "balloc.h"

typedef struct RegTrie * ImplTrie;

typedef struct RegTrie {
  Boolean fim;                 /* término de uma cadeia */
  ImplTrie subarv[TAM_ALFABETO]; /* vetor de subárvores */
} RegTrie;



/* ------------------------------------------------------------ */
/*          Sugestões de algumas funções auxiliares             */
/* ------------------------------------------------------------ */

ImplTrie criaInicializaNo() {
/* Devolve um nó com a marca de fim de cadeia falsa e todas as
   subárvores vazias; usada para criar a AD inicial e durante a
   inserção.
*/
   
  ImplTrie p = MALLOC(sizeof(RegTrie));
  if (p==NULL) {
    printf("Memória esgotada\n");
    exit(0);
  }
  p->fim = false;
  for (int k=0; k<TAM_ALFABETO; k++)
    p->subarv[k] = NULL;
  return p;

}


Boolean livre(ImplTrie t) {
/* Devolve verdadeiro se o nó 't' não é final e é uma folha; usada
   durante a remoção.
*/
  int i;
  
  for(i = 0; i < TAM_ALFABETO; i++)
    if(t->subarv[i] != NULL)
      return false;
  
  return !t->fim;

}


void percorreAux(ImplTrie t, funcVisita *v, char *buf, int m) {
/* Percorre a AD em ordem lexicográfica; constroi as cadeias em 'buf'
  e aplica a função 'v' quando termina uma cadeia, colocando no fim o
  caractere '\0'; 'm' é o índice do próximo caractere em 'buf'.
*/

  /* COMPLETAR!! */

}


/* ------------------------------------------------------------ */
/*                      Fim das sugestões                       */
/* ------------------------------------------------------------ */


Trie CriaAD() {
  
  return criaInicializaNo();
  
}


Boolean consultaAD(Trie t, char *s) {

  /* COMPLETAR!! */
  
  return false;  /* PROVISÓRIO */

}


Boolean insereAD(Trie t, char *s) {

  /* COMPLETAR!! */
  
  return false;  /* PROVISÓRIO */

}

  
int numCadeiasAD(Trie t) {
  
  /* COMPLETAR!! */
  
  return 0;  /* PROVISÓRIO */

}


Boolean removeAD(Trie t, char *s) {

  /* COMPLETAR!! */
  
  return false;  /* PROVISÓRIO */

}


void percorreAD(Trie t, funcVisita *v) {
  
  char buf[TAM_MAX_CADEIA];
  
  percorreAux((ImplTrie)t,v,buf,0);
  
}

void liberaAD(Trie t) {

  /* COMPLETAR!! */

}


/* 
  Funções usadas somente para verificação; conceitualmente
  não fazem parte da implementação.
*/
   
int numNosAD(Trie t) {

  /* COMPLETAR!! */
  
  return 0;  /* PROVISÓRIO */

}

int alturaAD(Trie t) {

  /* COMPLETAR!! */
  
  return 0;  /* PROVISÓRIO */

}



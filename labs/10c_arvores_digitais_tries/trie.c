/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
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
  int i;
  
  for(i = 0; i < TAM_ALFABETO; i++)
    if(t->subarv[i] != NULL)
      return false;
  
  return !t->fim;

}


void percorreAux(ImplTrie t, funcVisita *v, char *buf, int m) {
/* Percorre a AD em ordem lexicogr�fica; constroi as cadeias em 'buf'
  e aplica a fun��o 'v' quando termina uma cadeia, colocando no fim o
  caractere '\0'; 'm' � o �ndice do pr�ximo caractere em 'buf'.
*/

  /* COMPLETAR!! - Grupo 3 */

}


/* ------------------------------------------------------------ */
/*                      Fim das sugest�es                       */
/* ------------------------------------------------------------ */

/*
 * Devolve uma AD vazia. Sup�e uma implementa��o que n�o modifica mais
 * o apontador para a raiz da AD.
 */
Trie CriaAD() {
  
  return criaInicializaNo();
  
}

/*
 * Verifica se a cadeia de caracteres 's' foi inserida na AD 't'.
 */
Boolean consultaAD(Trie t, char *s) {
  ImplTrie noAtual = t;
  int indice = -1;
  int aresta;
  
  do {
    indice++;
    aresta = s[indice] - 'a';
    noAtual = noAtual->subarv[aresta];
  } while(noAtual != NULL && s[indice + 1]);

  if(noAtual->fim)
    return true;

  return false;

}

/*
 * Insere na AD 't' a cadeia de caracteres 's'.  Devolve o valor
 * verdadeiro se houve inser��o; devolve o valor falso se a cadeia j�
 * ocorre em 't'.  A cadeia 's' pode ser vazia (de comprimento zero).
 */
Boolean insereAD(Trie t, char *s) {

  /* COMPLETAR!! */
  
  return false;  /* PROVIS�RIO */

}

  
int numCadeiasAD(Trie t) {
  ImplTrie it = t;
  int i, soma;
  if(it == NULL)
    return 0;
  
  soma = 0;
  for(i = 0; i < TAM_ALFABETO; i++)
    soma += numCadeiasAD(it->subarv[i]);
  
  if(it->fim)
    soma++;
  
  return soma;

}


Boolean removeAD(Trie t, char *s) {

  /* COMPLETAR!! - Grupo 2 */
  
  return false;  /* PROVIS�RIO */

}


void percorreAD(Trie t, funcVisita *v) {
  
  char buf[TAM_MAX_CADEIA];
  
  percorreAux((ImplTrie)t,v,buf,0);
  
}

void liberaAD(Trie t) {

  ImplTrie it = t;
  if(it != NULL) {
    int i;
    for(i = 0; i < TAM_ALFABETO; i++)
      liberaAD(it->subarv[i]);
    FREE(it);
  }

}


/* 
  Fun��es usadas somente para verifica��o; conceitualmente
  n�o fazem parte da implementa��o.
*/
   
/* Devolve o n�mero de n�s da AD. */
int numNosAD(Trie t) {
  int num, i;
  ImplTrie it = t;
  if(it == NULL)
    return 0;
  
  num = 0;
  for(i = 0; i < TAM_ALFABETO; i++)
    num += numNosAD(it->subarv[i]);
  
  return 1 + num;

}

/* Devolve a altura da AD. */
int alturaAD(Trie t) {

  int maior, i;
  ImplTrie it = t;
  if(it == NULL)
    return 0;
  
  maior = alturaAD(it->subarv[0]);
  for(i = 1; i < TAM_ALFABETO; i++) {
    int alturaAtual = alturaAD(it->subarv[i]);
    if(alturaAtual > maior)
      maior = alturaAtual;
  }
  
  return maior + 1;

}



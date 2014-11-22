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
  
  /*
   * AD vazia � apenas um n� que n�o representa fim de cadeia e n�o tem filhos
   */
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
  
  /*
   * Para um n� ser folha, todos os seus filhos devem ser nulos, ou seja,
   * n�o tem filhos
   */
  for(i = 0; i < TAM_ALFABETO; i++)
    if(t->subarv[i] != NULL)
      return false;
  
  /*
   * Sendo folha, s� � livre se representa fim de cadeia
   */
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
  int indice = 0;
  int aresta;

  /*
   * Para cadeias vazias, basta verificar se a raiz representa fim de cadeia
   */
  if(*s == '\0')
    return noAtual->fim;
  
  /*
   * Para percorrer a cadeia 's' na AD, basta seguir as arestas de cada
   * letra representada por �ndice, at� chegar em uma sub�rvore nula ou
   * no fim da cadeia
   */
  while(noAtual != NULL && s[indice]) {
    aresta = s[indice] - 'a';
    noAtual = noAtual->subarv[aresta];
    indice++;
  }

  /*
   * Se chegou na sub�rvore nula, significa que a AD n�o cont�m todos os
   * caracteres da cadeia, logo n�o possui a cadeia
   */
  if(noAtual == NULL)
    return false;

  /*
   * Caso a AD possua todas as letras da cadeia, basta verificar se
   * o n� atual representa fim de cadeia para saber se 's' pertence
   * ap conjunto
   */
  return noAtual->fim;

}

/*
 * Insere na AD 't' a cadeia de caracteres 's'.  Devolve o valor
 * verdadeiro se houve inser��o; devolve o valor falso se a cadeia j�
 * ocorre em 't'.  A cadeia 's' pode ser vazia (de comprimento zero).
 */
Boolean insereAD(Trie t, char *s) {

  ImplTrie it = t;
  int indice;
  
  /*
   * Se a cadeia 's' � vazia, basta verificar se a raiz � fim de cadeia para
   * saber se 's' est� na AD, se n�o estiver, a inser��o se resume em
   * fazer a raiz representar fim de cadeia
   */
  if(*s == '\0') {
    if(it->fim)
      return false;
    it->fim = true;
    return true;
  }
  
  /*
   * Se n�o existe aresta para o caracter atual da cadeia, basta
   * criar um novo n� e apontar para ele com a aresta desejada,
   * por �ltimo, inserir os caracteres restantes
   */
  indice = *s - 'a';
  if(it->subarv[indice] == NULL) {
    ImplTrie novo = criaInicializaNo();
    it->subarv[indice] = novo;
    return insereAD(novo, s + 1);
  }
  
  /*
   * Enquando a AD apresentar caracteres da cadeia,
   * basta continuar a inser��o para o caracter seguinte
   */
  return insereAD(it->subarv[indice], s + 1);

}

/* Devolve o n�mero de cadeias contidas na AD. */ 
int numCadeiasAD(Trie t) {

  ImplTrie it = t;
  int i, soma;
  
  /*
   * Se a AD � nula, n�o h� cadeias
   */
  if(it == NULL)
    return 0;
  
  /*
   * Soma as cadeias das sub�rvores
   */
  soma = 0;
  for(i = 0; i < TAM_ALFABETO; i++)
    soma += numCadeiasAD(it->subarv[i]);
  
  /*
   * S� � contada uma cadeia quando � achado um n� que
   * representa fim de cadeia
   */
  if(it->fim)
    soma++;
  
  return soma;

}

Boolean removeAD(Trie t, char *s) {

  ImplTrie it = t;
  int aresta;
  
  if(t == NULL)
    return false;
  
  if(*s == '\0') {
    if(it->fim) { 
      it->fim = false;
      return true;
    } else
      return false;
  } else {
    aresta = *s - 'a';
    if(it->subarv[aresta] == NULL)
      return false;
  }

  if(removeAD(it->subarv[aresta], s + 1)) {
    if(livre(it->subarv[aresta])) {
      FREE(it->subarv[aresta]);
      it->subarv[aresta] = NULL;
    }
    return true;arq12.in
  }
  
  return false;

}


void percorreAD(Trie t, funcVisita *v) {
  
  char buf[TAM_MAX_CADEIA];
  
  percorreAux((ImplTrie)t,v,buf,0);
  
}

/* Libera a mem�ria din�mica alocada na constru��o da AD 't'. */
void liberaAD(Trie t) {

  ImplTrie it = t;
  if(it != NULL) {
    int i;
    /*
     * � preciso liberar a raiz ap�s liberar seus filhos, para n�o
     * perder a refer�ncia para os mesmos
     */
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
  /*
   * O n�mero de n�s de uma �rvore vazia � 0
   */
  if(it == NULL)
    return 0;

  /*
   * Conta n�s das sub�rvores de 't' 
   */  
  num = 0;
  for(i = 0; i < TAM_ALFABETO; i++)
    num += numNosAD(it->subarv[i]);
  
  /*
   * O n�mero de n�s de uma AD � 1 (considerando a raiz) +
   * n�mero de n�s de suas sub�rvores
   */
  return 1 + num;

}

/* Devolve a altura da AD. */
int alturaAD(Trie t) {

  int maior, i;
  ImplTrie it = t;
  /*
   * �rvore nulas tem altura 0
   */
  if(it == NULL)
    return 0;

  /*
   * Calcula a maior altura dentre as sub�rvores de 't'
   */  
  maior = alturaAD(it->subarv[0]);
  for(i = 1; i < TAM_ALFABETO; i++) {
    int alturaAtual = alturaAD(it->subarv[i]);
    if(alturaAtual > maior)
      maior = alturaAtual;
  }
  
  /*
   * A altura da AD ser� 1 (contando o n�vel da raiz) + a altura da
   * sub�rvore mais alta
   */
  return maior + 1;

}



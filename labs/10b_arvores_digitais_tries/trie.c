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
  
  /*
   * AD vazia é apenas um nó que não representa fim de cadeia e não tem filhos
   */
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
  
  /*
   * Para um nó ser folha, todos os seus filhos devem ser nulos, ou seja,
   * não tem filhos
   */
  for(i = 0; i < TAM_ALFABETO; i++)
    if(t->subarv[i] != NULL)
      return false;
  
  /*
   * Sendo folha, só é livre se representa fim de cadeia
   */
  return !t->fim;

}


void percorreAux(ImplTrie t, funcVisita *v, char *buf, int m) {
/* Percorre a AD em ordem lexicográfica; constroi as cadeias em 'buf'
  e aplica a função 'v' quando termina uma cadeia, colocando no fim o
  caractere '\0'; 'm' é o índice do próximo caractere em 'buf'.
*/

  /* COMPLETAR!! - Grupo 3 */

}


/* ------------------------------------------------------------ */
/*                      Fim das sugestões                       */
/* ------------------------------------------------------------ */

/*
 * Devolve uma AD vazia. Supõe uma implementação que não modifica mais
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
   * letra representada por índice, até chegar em uma subárvore nula ou
   * no fim da cadeia
   */
  while(noAtual != NULL && s[indice]) {
    aresta = s[indice] - 'a';
    noAtual = noAtual->subarv[aresta];
    indice++;
  }

  /*
   * Se chegou na subárvore nula, significa que a AD não contém todos os
   * caracteres da cadeia, logo não possui a cadeia
   */
  if(noAtual == NULL)
    return false;

  /*
   * Caso a AD possua todas as letras da cadeia, basta verificar se
   * o nó atual representa fim de cadeia para saber se 's' pertence
   * ap conjunto
   */
  return noAtual->fim;

}

/*
 * Insere na AD 't' a cadeia de caracteres 's'.  Devolve o valor
 * verdadeiro se houve inserção; devolve o valor falso se a cadeia já
 * ocorre em 't'.  A cadeia 's' pode ser vazia (de comprimento zero).
 */
Boolean insereAD(Trie t, char *s) {

  ImplTrie it = t;
  int indice;
  
  /*
   * Se a cadeia 's' é vazia, basta verificar se a raiz é fim de cadeia para
   * saber se 's' está na AD, se não estiver, a inserção se resume em
   * fazer a raiz representar fim de cadeia
   */
  if(*s == '\0') {
    if(it->fim)
      return false;
    it->fim = true;
    return true;
  }
  
  /*
   * Se não existe aresta para o caracter atual da cadeia, basta
   * criar um novo nó e apontar para ele com a aresta desejada,
   * por último, inserir os caracteres restantes
   */
  indice = *s - 'a';
  if(it->subarv[indice] == NULL) {
    ImplTrie novo = criaInicializaNo();
    it->subarv[indice] = novo;
    return insereAD(novo, s + 1);
  }
  
  /*
   * Enquando a AD apresentar caracteres da cadeia,
   * basta continuar a inserção para o caracter seguinte
   */
  return insereAD(it->subarv[indice], s + 1);

}

/* Devolve o número de cadeias contidas na AD. */ 
int numCadeiasAD(Trie t) {

  ImplTrie it = t;
  int i, soma;
  
  /*
   * Se a AD é nula, não há cadeias
   */
  if(it == NULL)
    return 0;
  
  /*
   * Soma as cadeias das subárvores
   */
  soma = 0;
  for(i = 0; i < TAM_ALFABETO; i++)
    soma += numCadeiasAD(it->subarv[i]);
  
  /*
   * Só é contada uma cadeia quando é achado um nó que
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

/* Libera a memória dinâmica alocada na construção da AD 't'. */
void liberaAD(Trie t) {

  ImplTrie it = t;
  if(it != NULL) {
    int i;
    /*
     * É preciso liberar a raiz após liberar seus filhos, para não
     * perder a referência para os mesmos
     */
    for(i = 0; i < TAM_ALFABETO; i++)
      liberaAD(it->subarv[i]);
    FREE(it);
  }

}


/* 
  Funções usadas somente para verificação; conceitualmente
  não fazem parte da implementação.
*/
   
/* Devolve o número de nós da AD. */
int numNosAD(Trie t) {

  int num, i;
  ImplTrie it = t;
  /*
   * O número de nós de uma árvore vazia é 0
   */
  if(it == NULL)
    return 0;

  /*
   * Conta nós das subárvores de 't' 
   */  
  num = 0;
  for(i = 0; i < TAM_ALFABETO; i++)
    num += numNosAD(it->subarv[i]);
  
  /*
   * O número de nós de uma AD é 1 (considerando a raiz) +
   * número de nós de suas subárvores
   */
  return 1 + num;

}

/* Devolve a altura da AD. */
int alturaAD(Trie t) {

  int maior, i;
  ImplTrie it = t;
  /*
   * Árvore nulas tem altura 0
   */
  if(it == NULL)
    return 0;

  /*
   * Calcula a maior altura dentre as subárvores de 't'
   */  
  maior = alturaAD(it->subarv[0]);
  for(i = 1; i < TAM_ALFABETO; i++) {
    int alturaAtual = alturaAD(it->subarv[i]);
    if(alturaAtual > maior)
      maior = alturaAtual;
  }
  
  /*
   * A altura da AD será 1 (contando o nível da raiz) + a altura da
   * subárvore mais alta
   */
  return maior + 1;

}



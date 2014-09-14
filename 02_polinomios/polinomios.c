/* Este módulo implementa operações sobre polinômios em uma variável.   */
/* Cada polinômio é representado por uma lista ligada circular, com nó   */
/* cabeça. Os nós da lista representam os termos não nulos do polinômio */
/* em ordem crescente dos seus expoentes. O nó cabeça tem expoente '-1'.*/

#include "polinomios.h"
#include "balloc.h"
#include <stdio.h>

/*-----------------------  Função auxiliar  ----------------------------*/

void InsereTermoAux(Polinomio p, int e, float c) {
/* Insere o termo '(e,c)' após o nó apontado por 'p'.                  */

/*----- COMPLETAR -----*/

} /* InsereTermoAux */



/*---------------- Implementação das funções da interface --------------*/


void ImprimePolinomio(Polinomio p) {
/* Imprime, em ordem crescente dos expoentes, os termos do              */
/* não nulos do 'p'. No caso do polinômio identicamente nulo,           */
/* imprime as palavras "Polinômio nulo".                                */

  if (p==NULL) {
    printf("Polinômio inválido\n");
    return;
  }
  
  if (p->prox==p) {
    printf("Polinômio nulo\n");
    return;
  }
  
  p = p->prox;
  while (p->expo!=-1) {
    printf("(%2d,%5.1f) ",p->expo,p->coef);
    p = p->prox;
  }
  printf("\n");

} /* ImprimePolinomio */


Polinomio CriaPolinomioNulo() {
/*
 * Devolve um novo polinômio identicamente nulo. Ou seja, apenas com nó cabeça
 * que tem expoente igual a -1, lembrando que a lista é circular
 */
  Polinomio nulo = MALLOC(sizeof(Polinomio));
  nulo->expo = -1;
  nulo->prox = nulo;
  
  return nulo;

} /* CriaPolinomioNulo */



void LiberaPolinomio(Polinomio p) {
/* Libera toda a memória dinâmica ocupada por um polinômio.             */
  /* Pula o cabeça para poder identificar o final do polinômio */
  Polinomio atual = p->prox;
  Polinomio proximo = p->prox;

  /* Desaloca cada termo */
  while(atual->expo != -1) {
    FREE(atual);
    atual = proximo;
    proximo = atual->prox;
  }

  /* Desaloca o nó cabeça */
  FREE(atual);

}

Boolean PolinomioNulo(Polinomio p) {
/* Verifica se o polinômio 'p' é identicamente nulo.                    */
  /* É identicamente nulo se só possui o nó cabeça */
  return p->expo == -1 && p->prox->expo == -1;

} /* PolinomioNulo */


void InsereTermo(Polinomio p, int e, float c) {
/* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os      */
/* termos ordenados. Supõe que não existe ainda em 'p' um termo com     */
/* expoente 'e', e que 'c' não é zero.                                  */
  if(c !=  0) {
    Polinomio atual = p; /* pula nó cabeça */
    Polinomio novo = MALLOC(sizeof(Polinomio));
    novo->expo = e;
    novo->coef = c;
    /* Percorre até achar a posição de inserção */
    while(atual->prox->expo != -1 && atual->prox->expo < e) {
      atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
  }

} /* InsereTermo */


Polinomio SomaPolinomios(Polinomio a, Polinomio b) {
/* Devolve a soma dos polinômios 'a' e 'b'. Não altera os polinômios    */
/* dados. Termos nulos não são inseridos no resultados.                 */

  /*----- COMPLETAR -----*/
  return NULL;    /*-- PROVISÓRIO --*/

} /* SomaPolinomios */


Polinomio MultTermo(Polinomio p, int e, float c) {
/* Devolve o polinômio 'p' multiplicado pelo termo '(e,c)'. Supõe       */
/* que 'c' não é nulo. Não altera o polinômio dado.                    */

  /*----- COMPLETAR -----*/
  return NULL;    /*-- PROVISÓRIO --*/

} /* MultTermo */


Polinomio MultPolinomios(Polinomio a, Polinomio b) {
/* Devolve o produto dos polinômios 'a' e 'b'. Não altera os polinômios */
/* dados.                                                               */

  /*----- COMPLETAR -----*/
  return NULL;    /*-- PROVISÓRIO --*/

} /* MultPolinomios */

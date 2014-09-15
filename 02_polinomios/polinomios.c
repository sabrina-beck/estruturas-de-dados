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
  Polinomio novo = MALLOC(sizeof(Polinomio));
  novo->expo = e;
  novo->coef = c;
  novo->prox = p->prox;
  p->prox = novo;
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
  Polinomio atual = p->prox; /* Pula o nó cabeça */
  Polinomio proximo = atual->prox;

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
    Polinomio atual = p;
    /* Percorre até achar a posição de inserção */
    while(atual->prox->expo != -1 && atual->prox->expo < e) {
      atual = atual->prox;
    }
    InsereTermoAux(atual, e, c);
  }

} /* InsereTermo */


Polinomio SomaPolinomios(Polinomio a, Polinomio b) {
/* Devolve a soma dos polinômios 'a' e 'b'. Não altera os polinômios    */
/* dados. Termos nulos não são inseridos no resultados.                 */

  Polinomio atualA = a->prox; /* Pula nó cabeça */
  Polinomio atualB = b->prox;
  Polinomio soma = CriaPolinomioNulo();
  
  /* Percorre os dois polinômios ao mesmo tempo */
  while(atualA->expo != -1 && atualB->expo != -1) {
    /* Se os termos tiverem o mesmo expoentes eles são somados */
    if(atualA->expo == atualB->expo) {
      int expo = atualA->expo;
      float coef = atualA->coef + atualB->coef;
      /* Termos com coeficiente nulos não sã adicionados na resposta */
      if(coef != 0)
        InsereTermo(soma, expo, coef);
      atualA = atualA->prox;
      atualB = atualB->prox;
      
      /*
       * Os termos que não tem um correspondente em expoente no
       * outro polinomio, são simplesmente adicionados na resposta
       */
    } else if(atualA->expo > atualB->expo) {
      InsereTermo(soma, atualB->expo, atualB->coef);
      atualB = atualB->prox;
    } else {
      InsereTermo(soma, atualA->expo, atualA->coef);
      atualA = atualA->prox;
    }
  }
  
  /* Termina de processar o polinômio de mais termos */
  while(atualA->expo != -1) {
    InsereTermo(soma, atualA->expo, atualA->coef);
    atualA = atualA->prox;
  }
  
  while(atualB->expo != -1) {
    InsereTermo(soma, atualB->expo, atualB->coef);
    atualB = atualB->prox;
  }

  return soma;    /*-- PROVISÓRIO --*/

} /* SomaPolinomios */


Polinomio MultTermo(Polinomio p, int e, float c) {
/* Devolve o polinômio 'p' multiplicado pelo termo '(e,c)'. Supõe       */
/* que 'c' não é nulo. Não altera o polinômio dado.                    */
  Polinomio novo = CriaPolinomioNulo();
  if(c != 0) {
    Polinomio atual = p->prox; /* Pula nó cabeça */
    /* Percorre o polinômio termo a termo */
    while(atual->expo != -1) {
      InsereTermo(novo, atual->expo + e, atual->coef * c);
      atual = atual->prox;
    }
  }
  return novo;
} /* MultTermo */


Polinomio MultPolinomios(Polinomio a, Polinomio b) {
/* Devolve o produto dos polinômios 'a' e 'b'. Não altera os polinômios */
/* dados.                                                               */

  /*----- COMPLETAR -----*/
  return NULL;    /*-- PROVISÓRIO --*/

} /* MultPolinomios */

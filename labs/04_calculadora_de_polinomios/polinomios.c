/* Este m�dulo implementa opera��es sobre polin�mios em uma vari�vel.   */
/* Cada polin�mio � representado por uma lista ligada circular, com n�   */
/* cabe�a. Os n�s da lista representam os termos n�o nulos do polin�mio */
/* em ordem crescente dos seus expoentes. O n� cabe�a tem expoente '-1'.*/
/*************************************************************************/
/* Sabrina Beck Angelini                                        RA157240 */
/* Turma: E                                                              */
/* Data: 20/09/2014                                                      */
/*************************************************************************/

#include "polinomios.h"
#include "balloc.h"
#include <stdio.h>

/*-----------------------  Fun��o auxiliar  ----------------------------*/

void InsereTermoAux(Polinomio p, int e, float c) {
/* Insere o termo '(e,c)' ap�s o n� apontado por 'p'.                  */
  Polinomio novo = MALLOC(sizeof(Polinomio));
  novo->expo = e;
  novo->coef = c;
  novo->prox = p->prox;
  p->prox = novo;
} /* InsereTermoAux */



/*---------------- Implementa��o das fun��es da interface --------------*/


void ImprimePolinomio(Polinomio p) {
/* Imprime, em ordem crescente dos expoentes, os termos do              */
/* n�o nulos do 'p'. No caso do polin�mio identicamente nulo,           */
/* imprime as palavras "Polin�mio nulo".                                */

  if (p==NULL) {
    printf("Polin�mio inv�lido\n");
    return;
  }
  
  if (p->prox==p) {
    printf("Polin�mio nulo\n");
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
 * Devolve um novo polin�mio identicamente nulo. Ou seja, apenas com n� cabe�a
 * que tem expoente igual a -1, lembrando que a lista � circular
 */
  Polinomio nulo = MALLOC(sizeof(Polinomio));
  nulo->expo = -1;
  nulo->prox = nulo;
  
  return nulo;

} /* CriaPolinomioNulo */



void LiberaPolinomio(Polinomio p) {
/* Libera toda a mem�ria din�mica ocupada por um polin�mio.             */
  /* Pula o cabe�a para poder identificar o final do polin�mio */
  Polinomio atual = p->prox; /* Pula o n� cabe�a */
  Polinomio proximo = atual->prox;

  /* Desaloca cada termo */
  while(atual->expo != -1) {
    FREE(atual);
    atual = proximo;
    proximo = atual->prox;
  }

  /* Desaloca o n� cabe�a */
  FREE(atual);

}

Boolean PolinomioNulo(Polinomio p) {
/* Verifica se o polin�mio 'p' � identicamente nulo.                    */
  /* � identicamente nulo se s� possui o n� cabe�a */
  return p->expo == -1 && p->prox->expo == -1;

} /* PolinomioNulo */


void InsereTermo(Polinomio p, int e, float c) {
/* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os      */
/* termos ordenados. Sup�e que n�o existe ainda em 'p' um termo com     */
/* expoente 'e', e que 'c' n�o � zero.                                  */
  if(c !=  0) {
    Polinomio atual = p;
    /* Percorre at� achar a posi��o de inser��o */
    while(atual->prox->expo != -1 && atual->prox->expo < e) {
      atual = atual->prox;
    }
    InsereTermoAux(atual, e, c);
  }

} /* InsereTermo */


Polinomio SomaPolinomios(Polinomio a, Polinomio b) {
/* Devolve a soma dos polin�mios 'a' e 'b'. N�o altera os polin�mios    */
/* dados. Termos nulos n�o s�o inseridos no resultados.                 */

  Polinomio atualA = a->prox; /* Pula n� cabe�a */
  Polinomio atualB = b->prox;
  Polinomio soma = CriaPolinomioNulo();
  Polinomio atualSoma = soma;
  
  /* Percorre os dois polin�mios ao mesmo tempo */
  while(atualA->expo != -1 && atualB->expo != -1) {
    /* Se os termos tiverem o mesmo expoentes eles s�o somados */
    if(atualA->expo == atualB->expo) {
      int expo = atualA->expo;
      float coef = atualA->coef + atualB->coef;
      /* Termos com coeficiente nulos n�o s� adicionados na resposta */
      if(coef != 0) {
        InsereTermoAux(atualSoma, expo, coef);
        atualSoma = atualSoma->prox;
      }
      atualA = atualA->prox;
      atualB = atualB->prox;
      
      /*
       * Os termos que n�o tem um correspondente em expoente no
       * outro polinomio, s�o simplesmente adicionados na resposta
       */
    } else if(atualA->expo > atualB->expo) {
      InsereTermoAux(atualSoma, atualB->expo, atualB->coef);
      atualB = atualB->prox;
      atualSoma = atualSoma->prox;
    } else {
      InsereTermoAux(atualSoma, atualA->expo, atualA->coef);
      atualA = atualA->prox;
      atualSoma = atualSoma->prox;
    }
  }
  
  /* Termina de processar o polin�mio que tem mais termos */
  while(atualA->expo != -1) {
    InsereTermoAux(atualSoma, atualA->expo, atualA->coef);
    atualA = atualA->prox;
    atualSoma = atualSoma->prox;
  }
  
  while(atualB->expo != -1) {
    InsereTermoAux(atualSoma, atualB->expo, atualB->coef);
    atualB = atualB->prox;
    atualSoma = atualSoma->prox;
  }

  return soma;
  
} /* SomaPolinomios */

Polinomio SubPolinomios(Polinomio a, Polinomio b) {
/* Devolve a diferen�a entre o polin�mio 'a' e o polin�mio 'b'. N�o      */
/* altera os polin�mios dados. Termos nulos n�o s�o inseridos no         */
/* resultado.                                                            */
  Polinomio bNeg = MultTermo(b, 0, -1);
  Polinomio sub = SomaPolinomios(a, bNeg);
  LiberaPolinomio(bNeg);
  return sub;

} /* SubPolinomios */

Polinomio MultTermo(Polinomio p, int e, float c) {
/* Devolve o polin�mio 'p' multiplicado pelo termo '(e,c)'. Sup�e       */
/* que 'c' n�o � nulo. N�o altera o polin�mio dado.                    */
  Polinomio novo = CriaPolinomioNulo();
  Polinomio novoAtual = novo;
  if(c != 0) {
    Polinomio atual = p->prox; /* Pula n� cabe�a */
    /* Percorre o polin�mio termo a termo */
    while(atual->expo != -1) {
      InsereTermoAux(novoAtual, atual->expo + e, atual->coef * c);
      atual = atual->prox;
      novoAtual = novoAtual->prox;
    }
  }
  return novo;

} /* MultTermo */


Polinomio MultPolinomios(Polinomio a, Polinomio b) {
/* Devolve o produto dos polin�mios 'a' e 'b'. N�o altera os polin�mios */
/* dados.                                                               */
  Polinomio atualB = b->prox; /* Pula n� cabe�a */
  Polinomio mult = CriaPolinomioNulo();

  /* Percorre cada termo do polinomio B */
  while(atualB->expo != -1) {
    /* Multiplica o termo de B por cada termo do polinomio A */
    Polinomio aMultTermo = MultTermo(a, atualB->expo, atualB->coef);
    Polinomio multAux = mult;
    /* Soma o polinomio A multiplicado pelo termo atual de B � resposta */
    mult = SomaPolinomios(multAux, aMultTermo);
    /* Anda com o "�ndice" do polin�mio B */
    atualB = atualB->prox;
    /* Libera mem�ria alocada */
    LiberaPolinomio(aMultTermo);
    LiberaPolinomio(multAux);
  }
  return mult;
  
} /* MultPolinomios */

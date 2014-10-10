/* Este módulo é a interface para  operações sobre polinômios em uma      */
/* variável. Cada polinômio é representado por uma lista ligada           */
/* circular, com nó cabeça. Os nós da lista representam os termos não     */
/* nulos do polinômio em ordem crescente dos seus expoentes. O nó         */
/* cabeça tem expoente '-1'.                                              */

#ifndef _Polinomios_DEFINED
#define _Polinomios_DEFINED

#include "boolean.h"

typedef struct Termo {
  int    expo;
  float  coef;
  struct Termo *prox;
} Termo, *Polinomio;

void ImprimePolinomio(Polinomio p);
/* Imprime, em ordem crescente dos expoentes, os termos não               */
/* nulos do polinônimo 'p'. No caso do polinômio identicamente nulo,      */
/* imprime as palavras "Polinômio nulo".                                  */

Polinomio CriaPolinomioNulo();
/* Devolve um novo polinômio identicamente nulo.                          */

void LiberaPolinomio(Polinomio p);
/* Libera toda a memória dinâmica ocupada por um polinômio.               */

Boolean PolinomioNulo(Polinomio p);
/* Verifica se o polinômio 'p' é identicamente nulo.                      */

void InsereTermo(Polinomio p, int e, float c);
/* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os        */
/* termos ordenados. Supõe que não existe ainda em 'p' um termo com       */
/* expoente 'e', e que 'c' não é zero.                                    */

Polinomio MultTermo(Polinomio p, int e, float c);
/* Devolve o polinômio 'p' multiplicado pelo termo '(e,c)'. Supõe         */
/* que 'c' não é nulo. Não altera os polinômios dados.                    */

Polinomio SomaPolinomios(Polinomio a, Polinomio b);
/* Devolve a soma dos polinômios 'a' e 'b'. Não altera os polinômios      */
/* dados. Termos nulos não são inseridos no resultado.                    */

Polinomio SubPolinomios(Polinomio a, Polinomio b);
/* Devolve a diferença entre o polinômio 'a' e o polinômio 'b'. Não       */
/* altera os polinômios dados. Termos nulos não são inseridos no          */
/* resultado.                                                             */

Polinomio MultPolinomios(Polinomio a, Polinomio b);
/* Devolve o produto dos polinômios 'a' e 'b'. Não altera os polinômios   */
/* dados. Deve usar as funções 'MultTermo' e 'SomaPolinomios'.            */

#endif

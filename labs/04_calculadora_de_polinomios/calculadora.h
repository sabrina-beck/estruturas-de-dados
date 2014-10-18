/* Interface para o módulo de cálculo de expressões pós-fixas sobre       */
/* uma base de dados formada por polinômios em uma variável.              */

#ifndef _CalcExpr_DEFINED
#define _CalcExpr_DEFINED

#include "polinomios.h"

#define MAX_EXPR 100 /* Tamanho máximo de uma expressão */

void InicializaBasePolinomios();
/* Inicializa polinômios com NULL, indicando que não há polinônios       */
/* válidos na base.                                                      */ 

Polinomio RecuperaPolinomio(char x);
/* Retorna o polinômio de nome x.                                        */

void ArmazenaPolinomio(char x, Polinomio p);
/* Armazena o polinômio p sob o nome x na base.                          */


Polinomio CalcExpr(char* expr);
/* Retorna o polinômio referente à expressão dada.                       */
/* O polinômio devolvido é sempre uma nova cópia, mesmo que a            */
/* expressão seja uma variável simples.                                  */

#endif

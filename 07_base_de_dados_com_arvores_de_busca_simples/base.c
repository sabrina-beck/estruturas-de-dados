/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 07 
  Segundo semestre de 2012

*/

/*
 * Arquivo base.c: implementação das funções de manipulação da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

typedef struct AuxNoArv {
  Aluno info;                   /* registros de informação */
  struct AuxNoArv *esq,*dir;   /* subárvores */
  } NoArv, * ImplBase;
  

Base CriaBase() {
/* Devolve apontador para uma base vazia */

  return NULL;
  
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se não existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */
   
  /****** COMPLETAR ***********/
  return false; /* PROVISÓRIO */

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
   
  /****** COMPLETAR ***********/
  return false; /* PROVISÓRIO */
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. */

  /****** COMPLETAR ***********/
  return false; /* PROVISÓRIO */

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVISÓRIO */

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVISÓRIO */

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */

    /****** COMPLETAR ***********/

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

  /****** COMPLETAR ***********/

} /* LiberaBase */

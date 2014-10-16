/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 07 
  Segundo semestre de 2012

*/

/*
 * Arquivo base.c: implementa��o das fun��es de manipula��o da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

typedef struct AuxNoArv {
  Aluno info;                   /* registros de informa��o */
  struct AuxNoArv *esq,*dir;   /* sub�rvores */
  } NoArv, * ImplBase;
  

Base CriaBase() {
/* Devolve apontador para uma base vazia */

  return NULL;
  
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */
   
  /****** COMPLETAR ***********/
  return false; /* PROVIS�RIO */

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
   
  /****** COMPLETAR ***********/
  return false; /* PROVIS�RIO */
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */

  /****** COMPLETAR ***********/
  return false; /* PROVIS�RIO */

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVIS�RIO */

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o n�mero de n�s da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVIS�RIO */

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */

    /****** COMPLETAR ***********/

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

  /****** COMPLETAR ***********/

} /* LiberaBase */

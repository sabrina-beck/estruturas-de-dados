/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 07 
  Primeiro semestre de 2013

*/

/*
 * Arquivo base.c: implementa��o das fun��es de manipula��o da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

#include "imprimearvore.h"

typedef struct AuxNoArv {
  Aluno info;                  /* registros de informa��o */
  struct AuxNoArv *esq,*dir;   /* sub�rvores */
  short int bal;               /* fator de balanceamento */
  } NoArv, * ImplBase;

/* ============================================================ */

/* Fun��o ImprimeBase para produzir a representa��o gr�fica */
/* Pode ajudar na depura��o */

char cadeiainfo[7] = "0000000"; /* conter� os d�gitos do RA */
char *vazia = "�rvore vazia\n";

ImplBase esq(ImplBase a, int d) {
  /* Sup�e a!=NULL */
  return a->esq;
}

ImplBase dir(ImplBase a, int d) {
  /* Sup�e a!=NULL */
  return a->dir;
}

char *info(ImplBase a, int d) {
  /* Sup�e a!=NULL */
  sprintf(cadeiainfo,"%6d", (a->info).ra);
  /* cadeiainfo[0] = (a->info)->ra;*/
  return cadeiainfo;
}

void ImprimeBase(Base *p) {
  /* Imprime a base sob a forma de uma �rvore 'deitada'. */
  ImplBase q = (ImplBase)(*p);
  printf("\n");
  ImprimeArvore(q,(subarvfunc*)esq,(subarvfunc*)dir,(infofunc*)info,NULL,1,vazia);
  printf("\n");
}

/* ============================================================ */

/* 
   Complete o resto do arquivo de maneira coerente com o arquivo
   'base.h'; se n�o implementar a fun��o de remo��o, coloque apenas um
   esqueleto vazio devolvendo qualquer valor booleano para evitar
   erros de compila��o.
*/

Base CriaBase() {
/* Devolve apontador para uma base vazia */
  /* FIXME: COMPLETAR! */
  return NULL;
}

Base SubEsq(Base *p) {
/* Devolve a sub�rvore esquerda da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */
  /* FIXME: COMPLETAR! */   
  return NULL;
}

Base SubDir(Base *p) {
/* Devolve a sub�rvore direita da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */
  /* FIXME: COMPLETAR! */   
  return NULL;   
}

int FatorBal(Base *p) {
/* Devolve o fator de balanceamento da raiz da base: altura da
   sub�rvore direita menos a altura da sub�rvore esquerda; devolve
   zero se a �rvore � vazia. */
  /* FIXME: COMPLETAR! */   
  return 0;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */  
  /* FIXME: COMPLETAR! */   
  return false;
}

Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
  /* FIXME: COMPLETAR! */   
  return false;
}
   
int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
  /* FIXME: COMPLETAR! */   
  return 0;
}

int NumeroNosBase(Base *p) {
/* Devolve o n�mero de n�s da base 'p'. */
  /* FIXME: COMPLETAR! */   
  return 0;
}

void PercorreBase(Base *p, TipoVisita Visita) {
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */
  /* FIXME: COMPLETAR! */   
}

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
  /* FIXME: COMPLETAR! */   
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. 

   A IMPLEMENTA��O DESTA FUN��O � OPCIONAL. 

*/
  /* FIXME: COMPLETAR! */   
  return false;
}

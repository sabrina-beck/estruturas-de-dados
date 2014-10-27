/*
  Autor:         COMPLETAR!
  RA:            COMPLETAR!
  Disciplina:    MC202
  Turma:         COMPLETAR!
  
  Tarefa 07 
  Primeiro semestre de 2013

*/

/*
 * Arquivo base.c: implementação das funções de manipulação da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

#include "imprimearvore.h"

typedef struct AuxNoArv {
  Aluno info;                  /* registros de informação */
  struct AuxNoArv *esq,*dir;   /* subárvores */
  short int bal;               /* fator de balanceamento */
  } NoArv, * ImplBase;

/* ============================================================ */

/* Função ImprimeBase para produzir a representação gráfica */
/* Pode ajudar na depuração */

char cadeiainfo[7] = "0000000"; /* conterá os dígitos do RA */
char *vazia = "Árvore vazia\n";

ImplBase esq(ImplBase a, int d) {
  /* Supõe a!=NULL */
  return a->esq;
}

ImplBase dir(ImplBase a, int d) {
  /* Supõe a!=NULL */
  return a->dir;
}

char *info(ImplBase a, int d) {
  /* Supõe a!=NULL */
  sprintf(cadeiainfo,"%6d", (a->info).ra);
  /* cadeiainfo[0] = (a->info)->ra;*/
  return cadeiainfo;
}

void ImprimeBase(Base *p) {
  /* Imprime a base sob a forma de uma árvore 'deitada'. */
  ImplBase q = (ImplBase)(*p);
  printf("\n");
  ImprimeArvore(q,(subarvfunc*)esq,(subarvfunc*)dir,(infofunc*)info,NULL,1,vazia);
  printf("\n");
}

/* ============================================================ */

/* 
   Complete o resto do arquivo de maneira coerente com o arquivo
   'base.h'; se não implementar a função de remoção, coloque apenas um
   esqueleto vazio devolvendo qualquer valor booleano para evitar
   erros de compilação.
*/

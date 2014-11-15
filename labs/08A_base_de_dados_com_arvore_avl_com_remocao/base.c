/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
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

Base CriaBase() {
/* Devolve apontador para uma base vazia */
  /* FIXME: COMPLETAR! */
  return NULL;
}

Base SubEsq(Base *p) {
/* Devolve a subárvore esquerda da base 'p' se não for vazia; caso
   contrário devolve NULL. */
  /* FIXME: COMPLETAR! */   
  return NULL;
}

Base SubDir(Base *p) {
/* Devolve a subárvore direita da base 'p' se não for vazia; caso
   contrário devolve NULL. */
  /* FIXME: COMPLETAR! */   
  return NULL;   
}

int FatorBal(Base *p) {
/* Devolve o fator de balanceamento da raiz da base: altura da
   subárvore direita menos a altura da subárvore esquerda; devolve
   zero se a árvore é vazia. */
  /* FIXME: COMPLETAR! */   
  return 0;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se não existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */  
  /* FIXME: COMPLETAR! */   
  return false;
}

Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
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
/* Devolve o número de nós da base 'p'. */
  /* FIXME: COMPLETAR! */   
  return 0;
}

void PercorreBase(Base *p, TipoVisita Visita) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */
  /* FIXME: COMPLETAR! */   
}

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
  /* FIXME: COMPLETAR! */   
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. 

   A IMPLEMENTAÇÃO DESTA FUNÇÃO É OPCIONAL. 

*/
  /* FIXME: COMPLETAR! */   
  return false;
}

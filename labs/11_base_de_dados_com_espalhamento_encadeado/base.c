/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 11
  Segundo semestre de 2014

*/

#include <stdio.h>
#include "base.h"

/* DECLARA��ES DE TIPOS */
/* -------------------- */

typedef struct RegLista *Lista;
typedef struct RegLista {
  Aluno aluno;
  Lista prox;
} RegLista;

typedef struct RegBase *ImplBase;
typedef struct RegBase {
  int numregs;
  Lista tabela[MaxHash];
} RegBase;

/* FUN��O DE ESPALHAMENTO */
/* ---------------------- */

int Espalha(int k) {
  return (k % MaxHash);
} /* Espalha */

/* FUN��ES AUXILIARES */
/* ------------------ */

Boolean InsereLista(Lista *lista, Aluno *a) {
  Lista *atual = lista;
  Lista novo;
  if(*atual != NULL) {
    while((*atual)->prox != NULL &&
          (*atual)->prox->aluno.ra < a->ra)
      atual = &((*atual)->prox);
      
    if((*atual)->aluno.ra == a->ra)
      return false;
  }
  
  novo = MALLOC(sizeof(RegLista));
  novo->aluno = *a;
  novo->prox = *atual;
  *atual = novo;
  
  return true;
}


/* FUN��ES DA INTERFACE */
/* -------------------- */

/*
 * Devolve apontador para uma base vazia com tabela inicializada
 */
Base CriaBase() {
  ImplBase base = MALLOC(sizeof(RegBase));
  base->numregs = 0;
  return base;
}

/*
 * Insere o registro 'a' na base 'p' se n�o existe aluno
 * com o mesmo valor de 'ra', e devolve 'true';  caso
 * contr�rio devolve 'false'
 */
Boolean InsereBase(Base p, Aluno *a) {
  ImplBase base = p;
  int hashcode = Espalha(a->ra);
  (base->numregs)++;
  return InsereLista(&(base->tabela[hashcode]), a);
}
   
/*
 * Remove da base 'p' o aluno com 'ra' dado; devolve 'true'
 * se ele existiu e 'false' caso contr�rio.
 */
Boolean RemoveBase(Base p, int ra) {
  /*TODO*/
  return false;
}

/* Devolve 'true' se existe um registro com 'ra' dado na
 * base 'p';  caso contr�rio devolve 'false'.  'a' conter� 
 * os dados do aluno, se encontrado.
 */
Boolean ConsultaBase(Base p, int ra, Aluno *a) {
  /*TODO*/
  return false;
}
   
/*
 * Devolve o n�mero de registros (alunos) na base 'p'.
 */
int NumeroRegsBase(Base p) {
  /*TODO*/
  return 0;
}

/* Imprime, os registros contidos na base 'p', um por linha.  A ordem
 * de impress�o segue a ordem das entradas da tabela, e para cada
 * entrada, a ordem da lista ligada.  Cada linha come�a com o �ndice
 * correspondente na tabela de espalhamento. Deve ser usado o formato
 * "(%3d) %06d %s\n".
 */
void ImprimeBase(Base p) {
  /*TODO*/
}
   
/*
 * Libera toda a mem�ria utilizada pela base 'p', bem como
 * todas as cadeias que guardam os nomes.
 */
void LiberaBase(Base p) {
  /*TODO*/
}

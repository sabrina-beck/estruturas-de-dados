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

/* DECLARAÇÕES DE TIPOS */
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

/* FUNÇÃO DE ESPALHAMENTO */
/* ---------------------- */

int Espalha(int k) {
  return (k % MaxHash);
} /* Espalha */

/* FUNÇÕES AUXILIARES */
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

Boolean RemoveLista(Lista *lista, int ra) {
  Lista *atual = lista;
  while(*atual != NULL && (*atual)->aluno.ra < ra)
    atual = &((*atual)->prox);
    
  if((*atual)->aluno.ra != ra)
    return false;

  FREE(*atual);
  *atual = (*atual)->prox;
  return true;
}

Boolean ConsultaLista(Lista lista, int ra, Aluno *a) {
  Lista atual = lista;
  while(atual != NULL && atual->aluno.ra < ra)
    atual = atual->prox;
    
  if(atual == NULL)
    return false;
    
  *a = atual->aluno;
  return true;
}

void ImprimeLista(int indice, Lista lista) {
  Lista atual = lista;
  while(atual != NULL)
    printf("(%3d) %06d %s\n", indice, atual->aluno.ra, atual->aluno.nome);
}

void LiberaLista(Lista lista) {
  Lista atual = lista;
  while(atual != NULL) {
    Lista aux = atual->prox;
    FREE(atual->aluno.nome);
    FREE(atual);
    atual = aux;
  }
}

/* FUNÇÕES DA INTERFACE */
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

 * Insere o registro 'a' na base 'p' se não existe aluno
 * com o mesmo valor de 'ra', e devolve 'true';  caso
 * contrário devolve 'false'
 */
Boolean InsereBase(Base p, Aluno *a) {
  ImplBase base = p;
  int hashcode = Espalha(a->ra);
  (base->numregs)++;
  return InsereLista(&(base->tabela[hashcode]), a);
}
   
/*
 * Remove da base 'p' o aluno com 'ra' dado; devolve 'true'
 * se ele existiu e 'false' caso contrário.
 */
Boolean RemoveBase(Base p, int ra) {
  ImplBase base = p;
  int hashcode = Espalha(ra);
  if(RemoveLista(&(base->tabela[hashcode]), ra)) {
    (base->numregs)--;
    return true;
  }
  
  return false;
}

/*
 * Devolve 'true' se existe um registro com 'ra' dado na
 * base 'p';  caso contrário devolve 'false'.  'a' conterá 
 * os dados do aluno, se encontrado.
 */
Boolean ConsultaBase(Base p, int ra, Aluno *a) {
  ImplBase base = p;
  int hashcode = Espalha(ra);
  return ConsultaLista(base->tabela[hashcode], ra, a);
}
   
/*
 * Devolve o número de registros (alunos) na base 'p'.
 */
int NumeroRegsBase(Base p) {
  ImplBase base = p;
  return base->numregs;
}

/*
 * Imprime, os registros contidos na base 'p', um por linha.  A ordem
 * de impressão segue a ordem das entradas da tabela, e para cada
 * entrada, a ordem da lista ligada.  Cada linha começa com o índice
 * correspondente na tabela de espalhamento. Deve ser usado o formato
 * "(%3d) %06d %s\n".
 */
void ImprimeBase(Base p) {
  ImplBase base = p;
  int i;
  for(i = 0; i < MaxHash; i++)
    ImprimeLista(i, base->tabela[i]);
}
   
/*
 * Libera toda a memória utilizada pela base 'p', bem como
 * todas as cadeias que guardam os nomes.
 */
void LiberaBase(Base p) {
  ImplBase base = p;
  int i;
  for(i = 0; i < MaxHash; i++)
    LiberaLista(base->tabela[i]);
  FREE(base);
}


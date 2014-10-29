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
   ImplBase *atual = (ImplBase*) p;
   
   while(*atual != NULL) {
     if((*atual)->info.ra == a.ra)
       return false;
     if((*atual)->info.ra > a.ra)
       atual = &((*atual)->esq);
     else
       atual = &((*atual)->dir);
   }
   
   *atual = MALLOC(sizeof(NoArv));
   (*atual)->info = a;
   (*atual)->esq = NULL;
   (*atual)->dir = NULL;
  return true;

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
  ImplBase atual = (ImplBase) *p;
  while(atual != NULL) {
    if(ra == atual->info.ra) {
      *a = atual->info;
      return true;
    }
    if(ra > atual->info.ra)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
     
  return false;
  
} /* ConsultaBase */

void removerNo(Base *p) {
    ImplBase *atual = (ImplBase*) p;
    if((*atual)->esq == NULL) {
      ImplBase removido = *p;
      *atual = removido->dir;
      FREE(removido->info.nome);
      FREE(removido);
    } else if((*atual)->dir == NULL) {
      ImplBase removido = *p;
      *atual = removido->dir;
      FREE(removido);
      FREE(removido->info.nome);
    } else {
      ImplBase removido = (*atual)->dir;
      while(removido != NULL && removido->esq != NULL)
        removido = removido->esq;
      (*atual)->info = removido->info;
      removerNo((Base*) &removido);
    }
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. */
  ImplBase *atual = (ImplBase*) p;

  /* Acha o nó a ser removido */
  while(*atual != NULL) {
    if((*atual)->info.ra == ra)
      break;
    if((*atual)->info.ra > ra)
      atual = &((*atual)->esq);
    else
      atual = &((*atual)->dir);
  }
  
  if(*atual != NULL) {
    removerNo((Base*) atual);
    return true;
  }
  
  return false;

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
  int alturaDir, alturaEsq;
  ImplBase atual = (ImplBase) *p;
  if(atual == NULL) 
   return 0;

  alturaEsq = AlturaBase((Base*) &(atual->esq));
  alturaDir = AlturaBase((Base*) &(atual->dir));
  
  if(alturaEsq >= alturaDir)
    return 1 + alturaEsq;
    
  return 1 + alturaDir;

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */
  ImplBase arv = (ImplBase) *p;
  if(arv == NULL)
    return 0;
  return 1 + NumeroNosBase((Base*) &(arv->esq)) + NumeroNosBase((Base*) &(arv->dir));
} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */
  ImplBase arv = (ImplBase) *p;
  if(arv != NULL) {
    PercorreBase((Base*) &(arv->esq), Visita);
    Visita(&arv->info);
    PercorreBase((Base*) &(arv->dir), Visita);
  }

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
  ImplBase arv = (ImplBase) *p;
  if(arv != NULL) {
    LiberaBase((Base*) &(arv->esq));
    LiberaBase((Base*) &(arv->dir));
    FREE(arv->info.nome);
    FREE(arv);
  }
} /* LiberaBase */

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

Boolean InsereAVL(Base *p, Aluno a, Boolean *alt);
void rotacaoSimplesLL(Base* p);
void rotacaoSimplesRR(Base* p);
void rotacaoDuplaLR(Base* p);
void rotacaoDuplaRL(Base* p);


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
  return NULL;
}

Base SubEsq(Base *p) {
/* Devolve a subárvore esquerda da base 'p' se não for vazia; caso
   contrário devolve NULL. */
   ImplBase *raiz = (ImplBase*)p;
   if(*raiz == NULL)
    return NULL;
   return (*raiz)->esq;
}

Base SubDir(Base *p) {
/* Devolve a subárvore direita da base 'p' se não for vazia; caso
   contrário devolve NULL. */
   ImplBase *raiz = (ImplBase*)p;
   if(*raiz == NULL)
    return NULL;
   return (*raiz)->dir;
}

int FatorBal(Base *p) {
/* Devolve o fator de balanceamento da raiz da base: altura da
   subárvore direita menos a altura da subárvore esquerda; devolve
   zero se a árvore é vazia. */
   ImplBase raiz = (ImplBase) *p;
   if(raiz == NULL)
      return 0;
   return AlturaBase((Base*) &(raiz->dir)) - AlturaBase((Base*) &(raiz->esq));
   
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se não existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */
   Boolean alt = false;
   return InsereAVL(p, a, &alt);
}
  
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
   ImplBase* raiz = (ImplBase*) p;
   if(*raiz == NULL)
      return false;

   if((*raiz)->info.ra == ra) {
      *a = (*raiz)->info;
      return true;
   }
   
   if((*raiz)->info.ra > ra) {
      return ConsultaBase((Base*) &((*raiz)->esq), ra, a);
   }
   
   return ConsultaBase((Base*) &((*raiz)->dir), ra, a);
}
   
int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
  ImplBase raiz = (ImplBase) *p;
  int altDir, altEsq;
  if(raiz == NULL)
      return 0;
  
  altEsq = AlturaBase((Base*) (&raiz->esq));
  altDir = AlturaBase((Base*) (&raiz->dir));
  if(altEsq > altDir)
    return altEsq + 1;
  return altDir + 1;
}

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */
  ImplBase raiz = (ImplBase) *p;
  if(raiz == NULL)
    return 0;
  return NumeroNosBase((Base*) (&raiz->esq)) + NumeroNosBase((Base*) (&raiz->dir)) + 1;
}

void PercorreBase(Base *p, TipoVisita Visita) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */
  ImplBase *raiz = (ImplBase*) p;
  if(*raiz != NULL) {
    PercorreBase((Base*) &((*raiz)->esq), Visita);
    Visita(&((*raiz)->info));
    PercorreBase((Base*) &((*raiz)->dir), Visita);
  }
}

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
  ImplBase* raiz = (ImplBase*) p;
  if(*raiz != NULL) {
    LiberaBase((Base*) &((*raiz)->esq));
    LiberaBase((Base*) &((*raiz)->dir));
    FREE((*raiz)->info.nome);
    FREE(*raiz);
  }
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. 

   A IMPLEMENTAÇÃO DESTA FUNÇÃO É OPCIONAL. 

*/
  /* TODO */
  return false;
}

/* FUNÇÕES AUXILIARES */
Boolean InsereAVL(Base *p, Aluno a, Boolean *alt) {
   ImplBase* raiz = (ImplBase*) p;
   if(*raiz == NULL) {
      *raiz = MALLOC(sizeof(NoArv));
      (*raiz)->esq = (*raiz)->dir = NULL;
      (*raiz)->info = a;
      (*raiz)->bal = 0;
      *alt = true;
      return true;
   }
   
   Aluno info = (*raiz)->info;
   if(a.ra == info.ra)
      return false;
   
   if(a.ra < info.ra) {
      Boolean inseriu = InsereAVL((Base*) &((*raiz)->esq), a, alt);
      if(!inseriu)
        return false;
      
      if(*alt) {
          short int bal = (*raiz)->bal;
          if(bal > 0) {
              (*raiz)->bal = 0;
              *alt = false;
          } else if(bal == 0) {
              (*raiz)->bal = -1;
              /* Alt continua true */
          } else {
              ImplBase aux = (*raiz)->esq;
              if(aux->bal > 0) {
                  /* Rotação dupla esquerda-direita */
                  rotacaoDuplaLR((Base*) raiz);
              } else {
                  /* Rotação simples esquerda-esquerda */
                  rotacaoSimplesLL((Base*) raiz);
              }
              aux->bal = 0;
              *alt = false;
          }
      }
      
   } else {
      Boolean inseriu = InsereAVL((Base*) &((*raiz)->dir), a, alt);
      if(!inseriu)
        return false;
      
      if(*alt) {
        short int bal = (*raiz)->bal;
        if(bal < 0) {
            (*raiz)->bal = 0;
            *alt = false;
        } else if(bal == 0) {
            (*raiz)->bal = 1;
            /* Alt continua true */
        } else {
            ImplBase aux = (*raiz)->dir;
            if(aux->bal < 0) {
                /* Rotação Dupla Direita-Esquerda */
                rotacaoDuplaRL((Base*) raiz);
            } else {
                /* Rotação Simples Direita-Direita */
                rotacaoSimplesRR((Base*) raiz);
            }
            aux->bal = 0;
            *alt = false;
        }
      }
   }
   return true;
}


void rotacaoSimplesLL(Base* p) {
  ImplBase* base = (ImplBase*) p;
  ImplBase novaRaiz = (*base)->esq;
  (*base)->esq = novaRaiz->dir;
  novaRaiz->dir = *base;
  (*base)->bal = 0;
  novaRaiz->bal = 0;
  *p = novaRaiz;
}

void rotacaoSimplesRR(Base* p) {
  ImplBase base = (ImplBase) *p;
  ImplBase novaRaiz = base->dir;
  base->dir = novaRaiz->esq;
  novaRaiz->esq = base;
  base->bal = 0;
  novaRaiz->bal = 0;
  *p = novaRaiz;
}

void rotacaoDuplaLR(Base* p) {
  ImplBase base = (ImplBase) *p;
  ImplBase itermediario = base->esq;
  ImplBase novaRaiz = itermediario->dir;
  base->esq = novaRaiz->dir;
  itermediario->dir = novaRaiz->esq;
  novaRaiz->esq = itermediario;
  novaRaiz->dir = base;
  switch(novaRaiz->bal) {
  case -1:
    itermediario->bal = 0;
    base->bal = 1;
    break;
  case 0:
    itermediario->bal = 0;
    base->bal = 0;
    break;
  case +1:
    itermediario->bal = -1;
    base->bal = 0;
    break;
  }
  novaRaiz->bal = 0;
  *p = novaRaiz;
}

void rotacaoDuplaRL(Base* p) {
  ImplBase base = *p;
  ImplBase intermediario = base->dir;
  ImplBase novaRaiz = intermediario->esq;
  intermediario->esq = novaRaiz->dir;
  base->dir = novaRaiz->esq;
  novaRaiz->esq = base;
  novaRaiz->dir = intermediario;
  switch(novaRaiz->bal) {
  case -1:
    base->bal = 0;
    intermediario->bal = 1;
    break;
  case 0:
    base->bal = 0;
    intermediario->bal = 0;
    break;
  case +1:
    base->bal = -1;
    intermediario->bal = 0;
    break;
  }
  novaRaiz->bal = 0;
  *p = novaRaiz;
}

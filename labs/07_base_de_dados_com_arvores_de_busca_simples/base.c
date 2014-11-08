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
   ImplBase *atual = (ImplBase*) p;

   /* Procura a posi��o de inser��o */   
   while(*atual != NULL) {
     /* N�o insere dados repetidos */
     if((*atual)->info.ra == a.ra)
       return false;
     /*
      * Por ser �rvore de busca, valores menores que a raiz s�o
      * inseridos na sub�rvore esquerda
      */
     if((*atual)->info.ra > a.ra)
       atual = &((*atual)->esq);
     else
       /* E valores maiores que a raiz s�o inseridos na sub�rvore direita */
       atual = &((*atual)->dir);
   }
   
   /* No fim, temos a posi��o de inser��o */
   *atual = MALLOC(sizeof(NoArv));
   (*atual)->info = a;
   (*atual)->esq = NULL;
   (*atual)->dir = NULL;
  return true;

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
  ImplBase atual = (ImplBase) *p;
  
  /* Percorre a �rvore */
  while(atual != NULL) {
    if(ra == atual->info.ra) {
      /* Achou o dado procurado */
      *a = atual->info;
      return true;
    }
    if(ra > atual->info.ra)
      /* Valores maiores que a raiz est�o na sub�rvore direita */
      atual = atual->dir;
    else
      /* Valores menores que a raiz est�o na sub�rvore esquerda */
      atual = atual->esq;
  }

  return false;
  
} /* ConsultaBase */

void removerNo(Base *p) {
/* Remove recursivamente o n� contido na mem�ria apontada por p */
    ImplBase analisado = *p;
    /*
     * Se o n� tem apenas um filho, esquerdo ou direito, ent�o
     * a remo��o consiste em apenas fazer esse filho ocupar a
     * posi��o do pai na �rvore
     */
    if(analisado->esq == NULL) {
      *p = analisado->dir;
      FREE(analisado->info.nome);
      FREE(analisado);
    } else if(analisado->dir == NULL) {
      *p = analisado->esq;
      FREE(analisado->info.nome);
      FREE(analisado);
    } else {
      /*
       * Caso o n� a ser removido tenha dois filhos, a remo��o � diferente
       */
      ImplBase *aRemover = &(analisado->dir);
      char* aux;
      /*
       * Procura o menor n� da sub�rvore direita
       */
      while((*aRemover)->esq != NULL)
        aRemover = &((*aRemover)->esq);
      /*
       * Coloca o conte�do do menor n� da sub�rvore direita no n� que
       * originalmente seria removido, e remove a estrutura do n� que
       * antes continha o menor n� da sub�rvore direita
       */
      ((ImplBase) *p)->info.ra = (*aRemover)->info.ra;
      aux = ((ImplBase) *p)->info.nome;
      ((ImplBase) *p)->info.nome = (*aRemover)->info.nome;
      /*
       * O n� a ser removido precisa desalocar a mem�ria ocupada
       * pelo nome do aluno removido
       */
      (*aRemover)->info.nome = aux;
      removerNo((Base*) aRemover);
    }
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */
  ImplBase *atual = (ImplBase*) p;

  /* Procura n� a ser removido */
  while(*atual != NULL) {
    if((*atual)->info.ra == ra)
    /* Achou o n� a ser removido */
      break;
    if((*atual)->info.ra > ra)
    /* Valores menores que a raiz est�o na sub�rvore esquerda */
      atual = &((*atual)->esq);
    else
    /* Valores maiores que a raiz est�o na sub�rvore direita */
      atual = &((*atual)->dir);
  }
  
  if(*atual != NULL) {
    /* Remove */
    removerNo((Base*) atual);
    return true;
  }
  
  return false;

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
  int alturaDir, alturaEsq;
  ImplBase atual = (ImplBase) *p;
  /* �rvores vazias tem altura 0 */
  if(atual == NULL) 
   return 0;
   
  /* Calcula a altura das sub�rvores esquerda e direita  */
  alturaEsq = AlturaBase((Base*) &(atual->esq));
  alturaDir = AlturaBase((Base*) &(atual->dir));
  
  /*
   * A altura da �rvore ser� a maior altura encontrada para as sub�rvores
   * +1 que representa a raiz
   */
  if(alturaEsq >= alturaDir)
    return 1 + alturaEsq;
    
  return 1 + alturaDir;

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o n�mero de n�s da base 'p'. */
  ImplBase arv = (ImplBase) *p;
  /* Se a �rvore � vazia, ent�o n�o tem n�s */
  if(arv == NULL)
    return 0;
  /*
   * A quantidade de n�s de uma �rvore � 1 (a raiz) mais a
   * quantidade de n�s nas sub�rvores esquerda e direita
   */
  return 1 + NumeroNosBase((Base*) &(arv->esq)) + NumeroNosBase((Base*) &(arv->dir));
} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */
  ImplBase arv = (ImplBase) *p;
  /* �rvores vazias n�o representam nada no percurso inordem */
  if(arv != NULL) {
    /*
     * No percurso inordem, a raiz � visitada depois de percorrer
     * a sub�rvore esquerda, depois de visitar a ra�z, a sub�rvore
     * direita � percorrida
     */
    PercorreBase((Base*) &(arv->esq), Visita);
    Visita(&arv->info);
    PercorreBase((Base*) &(arv->dir), Visita);
  }

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
  ImplBase arv = (ImplBase) *p;
  
  /*
   * Para Liberar a mem�ria ocupada por uma �rvore, � necess�rio
   * fazer a libera��o pelo percurso posordem, uma vez que a raiz �
   * desalocada por �ltimo, caso contr�rio, as sub�rvores n�o seriam
   * desalocadas
   */
  if(arv != NULL) {
    LiberaBase((Base*) &(arv->esq));
    LiberaBase((Base*) &(arv->dir));
    FREE(arv->info.nome);
    FREE(arv);
  }
} /* LiberaBase */

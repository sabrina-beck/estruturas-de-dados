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

   /* Procura a posição de inserção */   
   while(*atual != NULL) {
     /* Não insere dados repetidos */
     if((*atual)->info.ra == a.ra)
       return false;
     /*
      * Por ser árvore de busca, valores menores que a raiz são
      * inseridos na subárvore esquerda
      */
     if((*atual)->info.ra > a.ra)
       atual = &((*atual)->esq);
     else
       /* E valores maiores que a raiz são inseridos na subárvore direita */
       atual = &((*atual)->dir);
   }
   
   /* No fim, temos a posição de inserção */
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
  
  /* Percorre a árvore */
  while(atual != NULL) {
    if(ra == atual->info.ra) {
      /* Achou o dado procurado */
      *a = atual->info;
      return true;
    }
    if(ra > atual->info.ra)
      /* Valores maiores que a raiz estão na subárvore direita */
      atual = atual->dir;
    else
      /* Valores menores que a raiz estão na subárvore esquerda */
      atual = atual->esq;
  }

  return false;
  
} /* ConsultaBase */

void removerNo(Base *p) {
/* Remove recursivamente o nó contido na memória apontada por p */
    ImplBase analisado = *p;
    /*
     * Se o nó tem apenas um filho, esquerdo ou direito, então
     * a remoção consiste em apenas fazer esse filho ocupar a
     * posição do pai na árvore
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
       * Caso o nó a ser removido tenha dois filhos, a remoção é diferente
       */
      ImplBase *aRemover = &(analisado->dir);
      char* aux;
      /*
       * Procura o menor nó da subárvore direita
       */
      while((*aRemover)->esq != NULL)
        aRemover = &((*aRemover)->esq);
      /*
       * Coloca o conteúdo do menor nó da subárvore direita no nó que
       * originalmente seria removido, e remove a estrutura do nó que
       * antes continha o menor nó da subárvore direita
       */
      ((ImplBase) *p)->info.ra = (*aRemover)->info.ra;
      aux = ((ImplBase) *p)->info.nome;
      ((ImplBase) *p)->info.nome = (*aRemover)->info.nome;
      /*
       * O nó a ser removido precisa desalocar a memória ocupada
       * pelo nome do aluno removido
       */
      (*aRemover)->info.nome = aux;
      removerNo((Base*) aRemover);
    }
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. */
  ImplBase *atual = (ImplBase*) p;

  /* Procura nó a ser removido */
  while(*atual != NULL) {
    if((*atual)->info.ra == ra)
    /* Achou o nó a ser removido */
      break;
    if((*atual)->info.ra > ra)
    /* Valores menores que a raiz estão na subárvore esquerda */
      atual = &((*atual)->esq);
    else
    /* Valores maiores que a raiz estão na subárvore direita */
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
  /* Árvores vazias tem altura 0 */
  if(atual == NULL) 
   return 0;
   
  /* Calcula a altura das subárvores esquerda e direita  */
  alturaEsq = AlturaBase((Base*) &(atual->esq));
  alturaDir = AlturaBase((Base*) &(atual->dir));
  
  /*
   * A altura da árvore será a maior altura encontrada para as subárvores
   * +1 que representa a raiz
   */
  if(alturaEsq >= alturaDir)
    return 1 + alturaEsq;
    
  return 1 + alturaDir;

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */
  ImplBase arv = (ImplBase) *p;
  /* Se a árvore é vazia, então não tem nós */
  if(arv == NULL)
    return 0;
  /*
   * A quantidade de nós de uma árvore é 1 (a raiz) mais a
   * quantidade de nós nas subárvores esquerda e direita
   */
  return 1 + NumeroNosBase((Base*) &(arv->esq)) + NumeroNosBase((Base*) &(arv->dir));
} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */
  ImplBase arv = (ImplBase) *p;
  /* Árvores vazias não representam nada no percurso inordem */
  if(arv != NULL) {
    /*
     * No percurso inordem, a raiz é visitada depois de percorrer
     * a subárvore esquerda, depois de visitar a raíz, a subárvore
     * direita é percorrida
     */
    PercorreBase((Base*) &(arv->esq), Visita);
    Visita(&arv->info);
    PercorreBase((Base*) &(arv->dir), Visita);
  }

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
  ImplBase arv = (ImplBase) *p;
  
  /*
   * Para Liberar a memória ocupada por uma árvore, é necessário
   * fazer a liberação pelo percurso posordem, uma vez que a raiz é
   * desalocada por último, caso contrário, as subárvores não seriam
   * desalocadas
   */
  if(arv != NULL) {
    LiberaBase((Base*) &(arv->esq));
    LiberaBase((Base*) &(arv->dir));
    FREE(arv->info.nome);
    FREE(arv);
  }
} /* LiberaBase */

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

/*
 * Cria uma árvore vazia, no caso NULL já basta para essa implementação
 */
Base CriaBase() {
/* Devolve apontador para uma base vazia */
  return NULL;
}

Base SubEsq(Base *p) {
/* Devolve a subárvore esquerda da base 'p' se não for vazia; caso
   contrário devolve NULL. */
   ImplBase *raiz = (ImplBase*)p;
   /*
    * Árvores vazias não tem subarvores, sem essa verificação daria erro na
    * pois tentaria acessar o atributo esq de um ponteiro nulo
    */
   if(*raiz == NULL)
    return NULL;
   return (*raiz)->esq;
}

Base SubDir(Base *p) {
/* Devolve a subárvore direita da base 'p' se não for vazia; caso
   contrário devolve NULL. */
   ImplBase *raiz = (ImplBase*)p;
   /*
    * Árvores vazias não tem subarvores, sem essa verificação daria erro na
    * pois tentaria acessar o atributo esq de um ponteiro nulo
    */
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
   /* A inserção em AVL é recursiva, para isso uma função auxiliar */
   return InsereAVL(p, a, &alt);
}
  
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
   ImplBase* raiz = (ImplBase*) p;
   /*
    * Como é uma arvore de busca, se chegar em uma subárvore nula,
    * então o elemento não está na árvore 
    */
   if(*raiz == NULL)
      return false;

   /*
    * Se a raiz (Nó atual) contem o aluno desejado, basta retorna-lo
    */
   if((*raiz)->info.ra == ra) {
      *a = (*raiz)->info;
      return true;
   }
   
   /*
    * Seguindo árvores de busca, se o valor procurado é menor que a
    * raiz, então ele está na subárvore esquerda, senão na subárvore direita
    */
   if((*raiz)->info.ra > ra) {
      return ConsultaBase((Base*) &((*raiz)->esq), ra, a);
   }
   
   return ConsultaBase((Base*) &((*raiz)->dir), ra, a);
}
   
int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
  ImplBase raiz = (ImplBase) *p;
  int altDir, altEsq;
  /* Árvores vazias tem altura 0 */
  if(raiz == NULL)
      return 0;
  
  /*
   * A altura de uma árvores não vazia é a maior altura dentre as alturas
   * das subarvores esquerda e direita mais 1 para contar o nível da raiz
   */
  altEsq = AlturaBase((Base*) (&raiz->esq));
  altDir = AlturaBase((Base*) (&raiz->dir));
  if(altEsq > altDir)
    return altEsq + 1;
  return altDir + 1;
}

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */
  ImplBase raiz = (ImplBase) *p;
  /* Árvores vazias não tem nenhum nó */
  if(raiz == NULL)
    return 0;
  /*
   * A quantidade de nós em uma árvore é 1 (contando a raiz) mais a
   * quantidade de nós de suas subárvores esquerda e direita
   */
  return NumeroNosBase((Base*) (&raiz->esq)) + NumeroNosBase((Base*) (&raiz->dir)) + 1;
}

void PercorreBase(Base *p, TipoVisita Visita) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */
  ImplBase *raiz = (ImplBase*) p;
  /*
   * O percurso inordem não faz nada para árvores vazias,
   * mas para árvores não vazias primeiro percorre a subárvore
   * esquerda, depois visita a raiz e por último percorre a subárvore
   * direita
   */
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
  /*
   * Para liberar a memória ocupada por uma arvore binária,
   * deve-se primeiro liberar suas subárvores esquerda e direita,
   * depois liberar a raiz, para que não se perca a referencia das
   * subárvores 
   */
  if(*raiz != NULL) {
    LiberaBase((Base*) &((*raiz)->esq));
    LiberaBase((Base*) &((*raiz)->dir));
    /* É preciso liberar o nome do aluno também */
    FREE((*raiz)->info.nome);
    FREE(*raiz);
  }
}

void AcertaBalanceamentoAlteracaoEsquerda(ImplBase* raiz, Boolean *alt) {
  if(*alt) {
      short int bal = (*raiz)->bal;
      /*
       * Com a subárvore direita maior que a esquerda, como a inserção
       * foi na subárvore esquerda, então a altura da subárvore esquerda
       * aumentou e o balanceamento da raiz passa a ser 0
       */
      if(bal > 0) {
          (*raiz)->bal = 0;
          *alt = false; /* Nesse caso a altura da raíz não muda */
          
      /*
       * Com as subarvores com tamanhos iguais antes da inserção,
       * como a inserção foi na subárvore esquerda, então esta passa
       * a ter mais nós que a direita, logo o fator de balanceamento é -1
       */
      } else if(bal == 0) {
          (*raiz)->bal = -1;
          /*
           * Nesse caso a altura da raiz aumentou, logo a variável alt 
           * continua com seu valor true
           */
       
       /*
        * Se a subárvore esquerda antes da inserção era a maior,
        * depois da inserção na própria esquerda acontece o
        * desbalanceamento, logo são necessárias as rotações
        */
      } else {
          ImplBase aux = (*raiz)->esq;
          /*
           * Se a subárvore esquerda não tem desbalanceamento, ou
           * possui a subárvore direita maior que a esquerda, 
           * a rotação é dupla
           */
          if(aux->bal >= 0) {
              /* Rotação dupla esquerda-direita */
              rotacaoDuplaLR((Base*) raiz);
          /*
           * Caso a subárvore esquerda possua a própria subárvore
           * esquerda maior, então a rotação é simples
           */
          } else {
              /* Rotação simples esquerda-esquerda */
              rotacaoSimplesLL((Base*) raiz);
          }
          /*
           * Depois das rotações a altura não muda
           */
          *alt = false;
    }
}

void AcertaBalanceamentoAlteracaoDireita(ImplBase* raiz, Boolean *alt) {
  if(*alt) {
    short int bal = (*raiz)->bal;
    
    /*
     * Com a subárvore esquerda maior que a direita, como a inserção
     * foi na subárvore direita, então a altura da subárvore direita
     * aumentou e o balanceamento da raiz passa a ser 0
     */
    if(bal < 0) {
        (*raiz)->bal = 0;
        *alt = false; /* Nesse caso a altura da raíz não muda */
          
    /*
     * Com as subarvores com tamanhos iguais antes da inserção,
     * como a inserção foi na subárvore direita, então esta passa
     * a ter mais nós que a esquerda, logo o fator de balanceamento é 1
     */
    } else if(bal == 0) {
        (*raiz)->bal = 1;
        /*
         * Nesse caso a altura da raiz aumentou, logo a variável alt 
         * continua com seu valor true
         */
       
       /*
        * Se a subárvore direita antes da inserção era a maior,
        * depois da inserção na própria direita acontece o
        * desbalanceamento, logo são necessárias as rotações
        */
    } else {
        ImplBase aux = (*raiz)->dir;
        /*
         * Se a subárvore direita não tem desbalanceamento, ou
         * possui a subárvore esquerda maior que a direita, 
         * a rotação é dupla
         */
        if(aux->bal <= 0) {
            /* Rotação Dupla Direita-Esquerda */
            rotacaoDuplaRL((Base*) raiz);
        /*
         * Caso a subárvore esquerda possua a própria subárvore
         * esquerda maior, então a rotação é simples
         */
        } else {
            /* Rotação Simples Direita-Direita */
            rotacaoSimplesRR((Base*) raiz);
        }
        /*
         * Depois do balanceamento a altura não muda
         */
        *alt = false;
    }
  }
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. 

   A IMPLEMENTAÇÃO DESTA FUNÇÃO É OPCIONAL. 

*/

  ImplBase* raiz = (ImplBase*) p;
  if(*raiz == NULL) {
    *alt = false;
    return false
  }
  
  
  if((*raiz)->info.ra > ra) {
    Boolean res = RemoveAVL(&((*raiz)->esq), ra, alt);
    if(res)
      AcertaBalanceamentoAlteracaoEsquerda(raiz, alt);
    return res;
  }
  
  if((*raiz)->info.ra < ra) {
    Boolean res = RemoveAVL(&((*raiz)->dir), ra, alt);
    if(res)
      AcertaBalanceamentoAlteracaoDireita(raiz, alt);
    return res;
  }
  
  /* Se a raiz é contem o dado a ser removido */
  if((*raiz)->dir ==NULL) {
    ImplBase aux = *raiz;
    if((*raiz)->esq != NULL)
      (*raiz)->
  }
  
}

/* FUNÇÕES AUXILIARES */
Boolean InsereAVL(Base *p, Aluno a, Boolean *alt) {
/*
 * Realiza a inserção do aluno a na árvore AVL p corrigindo sempre os
 * fatores de balanceamento
 */
   ImplBase* raiz = (ImplBase*) p;
   /*
    * Se a árvore está vazia, cria-se o novo nó, insere ele na árvore,
    * e informamos a chamada que a altura da árvore mudou através do
    * parâmetro alt
    */
   if(*raiz == NULL) {
      *raiz = MALLOC(sizeof(NoArv));
      (*raiz)->esq = (*raiz)->dir = NULL;
      (*raiz)->info = a;
      (*raiz)->bal = 0;
      *alt = true;
      return true;
   }
   
   /*
    * Não se insere alunos com ra repetido, ou seja, não se insere o
    * mesmo aluno duas vezes
    */
   Aluno info = (*raiz)->info;
   if(a.ra == info.ra)
      return false;
   
   /*
    * No caso do ra da raíz se maior que o inserido, o mesmo deve ser
    * inserido na subárvore esquerda
    */
   if(a.ra < info.ra) {
      /* Insere o novo dado na subárvore esquerda */
      Boolean inseriu = InsereAVL((Base*) &((*raiz)->esq), a, alt);
      /* Se não inseriu, não há motivos para continuar as operações */
      if(!inseriu)
        return false;
      
      /* Se a altura mudou, então é preciso verificar o balanceamento da árvore */
      AcertaBalanceamentoAlteracaoEsquerda(raiz, alt);
      }
   /*
    * No caso do ra da raíz se menor que o inserido, o mesmo deve ser
    * inserido na subárvore direita
    */
   } else {
      /* Insere o novo dado na subárvore direita */
      Boolean inseriu = InsereAVL((Base*) &((*raiz)->dir), a, alt);
      /* Se não inseriu, não há motivos para continuar as operações */
      if(!inseriu)
        return false;
      
      /* Se a altura mudou, então é preciso verificar o balanceamento da árvore */
      AcertaBalanceamentoAlteracaoDireita(raiz, alt);
   }

   return true;
}


void rotacaoSimplesLL(Base* p) {
/*
 * Realiza a rotação simples LL na árvore de raiza *p
 */
  ImplBase* base = (ImplBase*) p;
  ImplBase novaRaiz = (*base)->esq;
  /* 
   * A raiz passa a ter como subárvore esquerda a subárvore direita
   * de seu filho esquerdo, seguindo a regra de árvore de busca
   */
  (*base)->esq = novaRaiz->dir;
  /*
   * Seguindo as regras de árvores de busca, o filho esquerdo da raiz passa
   * a ter como filho direito a própria raiz
   */
  novaRaiz->dir = *base;
  
  /*
   * Essa rotação deixa a raiz e seu filho esquerdo balanceados
   */
  (*base)->bal = 0;
  novaRaiz->bal = 0;
  /*
   * O filho esquerdo da raiz passa a ser a nova raiz
   */
  *p = novaRaiz;
}

void rotacaoSimplesRR(Base* p) {
/*
 * Realiza a rotação simples RR na árvore de raiza *p
 */
  ImplBase base = (ImplBase) *p;
  ImplBase novaRaiz = base->dir;
  /* 
   * A raiz passa a ter como subárvore direita a subárvore esquerda
   * de seu filho direito, seguindo a regra de árvore de busca
   */
  base->dir = novaRaiz->esq;
  /*
   * Seguindo as regras de árvores de busca, o filho direito da raiz passa
   * a ter como filho esquerdo a própria raiz
   */
  novaRaiz->esq = base;
  
  /*
   * Essa rotação deixa a raiz e seu filho direito balanceados
   */
  base->bal = 0;
  novaRaiz->bal = 0;
  /*
   * O filho direito da raiz passa a ser a nova raiz
   */
  *p = novaRaiz;
}

void rotacaoDuplaLR(Base* p) {
/*
 * Realiza a rotação dupla LR na árvore de raiza *p
 */
  ImplBase base = (ImplBase) *p;
  
  /* Considere intermediário o nó do meio */
  ImplBase itermediario = base->esq;
  
  /* O nó direito do intermediário será a nova raiz */
  ImplBase novaRaiz = itermediario->dir;
  
  /*
   * A raiz passa a ter como subárvore esquerda a
   * subárvore esquerda da nova raiz, seguindo as regras de arvores de busca
   */
  base->esq = novaRaiz->dir;
  
  /*
   * O intermediario passa a ter como subárvore direita a subárvore
   * esquerda da nova raiz, seguindo as regras de arvores de busca
   */
  itermediario->dir = novaRaiz->esq;
  
  /*
   * Seguindo as regras de arvores de busca a nova raiz passa a ter como
   * filho esquerdo o intermediario e como filho direito a raiz
   */
  novaRaiz->esq = itermediario;
  novaRaiz->dir = base;
  
  /*
   * O fator de balanceamento é acertado de acordo
   * com o fator de balanceamento da nova Raiz
   */
  if(novaRaiz->bal < 0) {
    itermediario->bal = 0;
    base->bal = 1;
  } else if (novaRaiz->bal == 0) {
    itermediario->bal = 0;
    base->bal = 0;
  } else {
    itermediario->bal = -1;
    base->bal = 0;
  }
  /*
   * Essa rotação deixa a nova raiz balanceada
   */
  novaRaiz->bal = 0;
  
  /* O nó direito do intermediário será a nova raiz */
  *p = novaRaiz;
}

void rotacaoDuplaRL(Base* p) {
/*
 * Realiza a rotação dupla LR na árvore de raiza *p
 */
  ImplBase base = *p;

  /* Considere intermediário o nó do meio */
  ImplBase intermediario = base->dir;

  /* O nó direito do intermediário será a nova raiz */
  ImplBase novaRaiz = intermediario->esq;

  /*
   * O intermediario passa a ter como subárvore esquerda a subárvore
   * direita da nova raiz, seguindo as regras de arvores de busca
   */
  intermediario->esq = novaRaiz->dir;

  /*
   * A raiz passa a ter como subárvore direita a
   * subárvore esquerda da nova raiz, seguindo as regras de arvores de busca
   */
  base->dir = novaRaiz->esq;
  
  /*
   * Seguindo as regras de arvores de busca a nova raiz passa a ter como
   * filho esquerdo a raiz e como filho direito o intermediario
   */
  novaRaiz->esq = base;
  novaRaiz->dir = intermediario;
  
  /*
   * O fator de balanceamento é acertado de acordo
   * com o fator de balanceamento da nova Raiz
   */
  if(novaRaiz->bal < 0) {
    base->bal = 0;
    intermediario->bal = 1;
  } else if(novaRaiz->bal == 0) {
    base->bal = 0;
    intermediario->bal = 0;
  } else {
    base->bal = -1;
    intermediario->bal = 0;
  }
  
  /*
   * Essa rotação deixa a nova raiz balanceada
   */
  novaRaiz->bal = 0;
  
  /* O nó esquerdo do intermediário será a nova raiz */
  *p = novaRaiz;
}

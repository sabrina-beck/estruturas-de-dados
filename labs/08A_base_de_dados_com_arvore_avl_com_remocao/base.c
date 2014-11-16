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

Boolean InsereAVL(Base *p, Aluno a, Boolean *alt);
void rotacaoSimplesLL(Base* p);
void rotacaoSimplesRR(Base* p);
void rotacaoDuplaLR(Base* p);
void rotacaoDuplaRL(Base* p);


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

/*
 * Cria uma �rvore vazia, no caso NULL j� basta para essa implementa��o
 */
Base CriaBase() {
/* Devolve apontador para uma base vazia */
  return NULL;
}

Base SubEsq(Base *p) {
/* Devolve a sub�rvore esquerda da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */
   ImplBase *raiz = (ImplBase*)p;
   /*
    * �rvores vazias n�o tem subarvores, sem essa verifica��o daria erro na
    * pois tentaria acessar o atributo esq de um ponteiro nulo
    */
   if(*raiz == NULL)
    return NULL;
   return (*raiz)->esq;
}

Base SubDir(Base *p) {
/* Devolve a sub�rvore direita da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */
   ImplBase *raiz = (ImplBase*)p;
   /*
    * �rvores vazias n�o tem subarvores, sem essa verifica��o daria erro na
    * pois tentaria acessar o atributo esq de um ponteiro nulo
    */
   if(*raiz == NULL)
    return NULL;
   return (*raiz)->dir;
}

int FatorBal(Base *p) {
/* Devolve o fator de balanceamento da raiz da base: altura da
   sub�rvore direita menos a altura da sub�rvore esquerda; devolve
   zero se a �rvore � vazia. */
   ImplBase raiz = (ImplBase) *p;
   if(raiz == NULL)
      return 0;
   return AlturaBase((Base*) &(raiz->dir)) - AlturaBase((Base*) &(raiz->esq));
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */
   Boolean alt = false;
   /* A inser��o em AVL � recursiva, para isso uma fun��o auxiliar */
   return InsereAVL(p, a, &alt);
}
  
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
   ImplBase* raiz = (ImplBase*) p;
   /*
    * Como � uma arvore de busca, se chegar em uma sub�rvore nula,
    * ent�o o elemento n�o est� na �rvore 
    */
   if(*raiz == NULL)
      return false;

   /*
    * Se a raiz (N� atual) contem o aluno desejado, basta retorna-lo
    */
   if((*raiz)->info.ra == ra) {
      *a = (*raiz)->info;
      return true;
   }
   
   /*
    * Seguindo �rvores de busca, se o valor procurado � menor que a
    * raiz, ent�o ele est� na sub�rvore esquerda, sen�o na sub�rvore direita
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
  /* �rvores vazias tem altura 0 */
  if(raiz == NULL)
      return 0;
  
  /*
   * A altura de uma �rvores n�o vazia � a maior altura dentre as alturas
   * das subarvores esquerda e direita mais 1 para contar o n�vel da raiz
   */
  altEsq = AlturaBase((Base*) (&raiz->esq));
  altDir = AlturaBase((Base*) (&raiz->dir));
  if(altEsq > altDir)
    return altEsq + 1;
  return altDir + 1;
}

int NumeroNosBase(Base *p) {
/* Devolve o n�mero de n�s da base 'p'. */
  ImplBase raiz = (ImplBase) *p;
  /* �rvores vazias n�o tem nenhum n� */
  if(raiz == NULL)
    return 0;
  /*
   * A quantidade de n�s em uma �rvore � 1 (contando a raiz) mais a
   * quantidade de n�s de suas sub�rvores esquerda e direita
   */
  return NumeroNosBase((Base*) (&raiz->esq)) + NumeroNosBase((Base*) (&raiz->dir)) + 1;
}

void PercorreBase(Base *p, TipoVisita Visita) {
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */
  ImplBase *raiz = (ImplBase*) p;
  /*
   * O percurso inordem n�o faz nada para �rvores vazias,
   * mas para �rvores n�o vazias primeiro percorre a sub�rvore
   * esquerda, depois visita a raiz e por �ltimo percorre a sub�rvore
   * direita
   */
  if(*raiz != NULL) {
    PercorreBase((Base*) &((*raiz)->esq), Visita);
    Visita(&((*raiz)->info));
    PercorreBase((Base*) &((*raiz)->dir), Visita);
  }
}

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
  ImplBase* raiz = (ImplBase*) p;
  /*
   * Para liberar a mem�ria ocupada por uma arvore bin�ria,
   * deve-se primeiro liberar suas sub�rvores esquerda e direita,
   * depois liberar a raiz, para que n�o se perca a referencia das
   * sub�rvores 
   */
  if(*raiz != NULL) {
    LiberaBase((Base*) &((*raiz)->esq));
    LiberaBase((Base*) &((*raiz)->dir));
    /* � preciso liberar o nome do aluno tamb�m */
    FREE((*raiz)->info.nome);
    FREE(*raiz);
  }
}

void AcertaBalanceamentoAlteracaoEsquerda(ImplBase* raiz, Boolean *alt) {
  if(*alt) {
      short int bal = (*raiz)->bal;
      /*
       * Com a sub�rvore direita maior que a esquerda, como a inser��o
       * foi na sub�rvore esquerda, ent�o a altura da sub�rvore esquerda
       * aumentou e o balanceamento da raiz passa a ser 0
       */
      if(bal > 0) {
          (*raiz)->bal = 0;
          *alt = false; /* Nesse caso a altura da ra�z n�o muda */
          
      /*
       * Com as subarvores com tamanhos iguais antes da inser��o,
       * como a inser��o foi na sub�rvore esquerda, ent�o esta passa
       * a ter mais n�s que a direita, logo o fator de balanceamento � -1
       */
      } else if(bal == 0) {
          (*raiz)->bal = -1;
          /*
           * Nesse caso a altura da raiz aumentou, logo a vari�vel alt 
           * continua com seu valor true
           */
       
       /*
        * Se a sub�rvore esquerda antes da inser��o era a maior,
        * depois da inser��o na pr�pria esquerda acontece o
        * desbalanceamento, logo s�o necess�rias as rota��es
        */
      } else {
          ImplBase aux = (*raiz)->esq;
          /*
           * Se a sub�rvore esquerda n�o tem desbalanceamento, ou
           * possui a sub�rvore direita maior que a esquerda, 
           * a rota��o � dupla
           */
          if(aux->bal >= 0) {
              /* Rota��o dupla esquerda-direita */
              rotacaoDuplaLR((Base*) raiz);
          /*
           * Caso a sub�rvore esquerda possua a pr�pria sub�rvore
           * esquerda maior, ent�o a rota��o � simples
           */
          } else {
              /* Rota��o simples esquerda-esquerda */
              rotacaoSimplesLL((Base*) raiz);
          }
          /*
           * Depois das rota��es a altura n�o muda
           */
          *alt = false;
    }
}

void AcertaBalanceamentoAlteracaoDireita(ImplBase* raiz, Boolean *alt) {
  if(*alt) {
    short int bal = (*raiz)->bal;
    
    /*
     * Com a sub�rvore esquerda maior que a direita, como a inser��o
     * foi na sub�rvore direita, ent�o a altura da sub�rvore direita
     * aumentou e o balanceamento da raiz passa a ser 0
     */
    if(bal < 0) {
        (*raiz)->bal = 0;
        *alt = false; /* Nesse caso a altura da ra�z n�o muda */
          
    /*
     * Com as subarvores com tamanhos iguais antes da inser��o,
     * como a inser��o foi na sub�rvore direita, ent�o esta passa
     * a ter mais n�s que a esquerda, logo o fator de balanceamento � 1
     */
    } else if(bal == 0) {
        (*raiz)->bal = 1;
        /*
         * Nesse caso a altura da raiz aumentou, logo a vari�vel alt 
         * continua com seu valor true
         */
       
       /*
        * Se a sub�rvore direita antes da inser��o era a maior,
        * depois da inser��o na pr�pria direita acontece o
        * desbalanceamento, logo s�o necess�rias as rota��es
        */
    } else {
        ImplBase aux = (*raiz)->dir;
        /*
         * Se a sub�rvore direita n�o tem desbalanceamento, ou
         * possui a sub�rvore esquerda maior que a direita, 
         * a rota��o � dupla
         */
        if(aux->bal <= 0) {
            /* Rota��o Dupla Direita-Esquerda */
            rotacaoDuplaRL((Base*) raiz);
        /*
         * Caso a sub�rvore esquerda possua a pr�pria sub�rvore
         * esquerda maior, ent�o a rota��o � simples
         */
        } else {
            /* Rota��o Simples Direita-Direita */
            rotacaoSimplesRR((Base*) raiz);
        }
        /*
         * Depois do balanceamento a altura n�o muda
         */
        *alt = false;
    }
  }
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. 

   A IMPLEMENTA��O DESTA FUN��O � OPCIONAL. 

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
  
  /* Se a raiz � contem o dado a ser removido */
  if((*raiz)->dir ==NULL) {
    ImplBase aux = *raiz;
    if((*raiz)->esq != NULL)
      (*raiz)->
  }
  
}

/* FUN��ES AUXILIARES */
Boolean InsereAVL(Base *p, Aluno a, Boolean *alt) {
/*
 * Realiza a inser��o do aluno a na �rvore AVL p corrigindo sempre os
 * fatores de balanceamento
 */
   ImplBase* raiz = (ImplBase*) p;
   /*
    * Se a �rvore est� vazia, cria-se o novo n�, insere ele na �rvore,
    * e informamos a chamada que a altura da �rvore mudou atrav�s do
    * par�metro alt
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
    * N�o se insere alunos com ra repetido, ou seja, n�o se insere o
    * mesmo aluno duas vezes
    */
   Aluno info = (*raiz)->info;
   if(a.ra == info.ra)
      return false;
   
   /*
    * No caso do ra da ra�z se maior que o inserido, o mesmo deve ser
    * inserido na sub�rvore esquerda
    */
   if(a.ra < info.ra) {
      /* Insere o novo dado na sub�rvore esquerda */
      Boolean inseriu = InsereAVL((Base*) &((*raiz)->esq), a, alt);
      /* Se n�o inseriu, n�o h� motivos para continuar as opera��es */
      if(!inseriu)
        return false;
      
      /* Se a altura mudou, ent�o � preciso verificar o balanceamento da �rvore */
      AcertaBalanceamentoAlteracaoEsquerda(raiz, alt);
      }
   /*
    * No caso do ra da ra�z se menor que o inserido, o mesmo deve ser
    * inserido na sub�rvore direita
    */
   } else {
      /* Insere o novo dado na sub�rvore direita */
      Boolean inseriu = InsereAVL((Base*) &((*raiz)->dir), a, alt);
      /* Se n�o inseriu, n�o h� motivos para continuar as opera��es */
      if(!inseriu)
        return false;
      
      /* Se a altura mudou, ent�o � preciso verificar o balanceamento da �rvore */
      AcertaBalanceamentoAlteracaoDireita(raiz, alt);
   }

   return true;
}


void rotacaoSimplesLL(Base* p) {
/*
 * Realiza a rota��o simples LL na �rvore de raiza *p
 */
  ImplBase* base = (ImplBase*) p;
  ImplBase novaRaiz = (*base)->esq;
  /* 
   * A raiz passa a ter como sub�rvore esquerda a sub�rvore direita
   * de seu filho esquerdo, seguindo a regra de �rvore de busca
   */
  (*base)->esq = novaRaiz->dir;
  /*
   * Seguindo as regras de �rvores de busca, o filho esquerdo da raiz passa
   * a ter como filho direito a pr�pria raiz
   */
  novaRaiz->dir = *base;
  
  /*
   * Essa rota��o deixa a raiz e seu filho esquerdo balanceados
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
 * Realiza a rota��o simples RR na �rvore de raiza *p
 */
  ImplBase base = (ImplBase) *p;
  ImplBase novaRaiz = base->dir;
  /* 
   * A raiz passa a ter como sub�rvore direita a sub�rvore esquerda
   * de seu filho direito, seguindo a regra de �rvore de busca
   */
  base->dir = novaRaiz->esq;
  /*
   * Seguindo as regras de �rvores de busca, o filho direito da raiz passa
   * a ter como filho esquerdo a pr�pria raiz
   */
  novaRaiz->esq = base;
  
  /*
   * Essa rota��o deixa a raiz e seu filho direito balanceados
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
 * Realiza a rota��o dupla LR na �rvore de raiza *p
 */
  ImplBase base = (ImplBase) *p;
  
  /* Considere intermedi�rio o n� do meio */
  ImplBase itermediario = base->esq;
  
  /* O n� direito do intermedi�rio ser� a nova raiz */
  ImplBase novaRaiz = itermediario->dir;
  
  /*
   * A raiz passa a ter como sub�rvore esquerda a
   * sub�rvore esquerda da nova raiz, seguindo as regras de arvores de busca
   */
  base->esq = novaRaiz->dir;
  
  /*
   * O intermediario passa a ter como sub�rvore direita a sub�rvore
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
   * O fator de balanceamento � acertado de acordo
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
   * Essa rota��o deixa a nova raiz balanceada
   */
  novaRaiz->bal = 0;
  
  /* O n� direito do intermedi�rio ser� a nova raiz */
  *p = novaRaiz;
}

void rotacaoDuplaRL(Base* p) {
/*
 * Realiza a rota��o dupla LR na �rvore de raiza *p
 */
  ImplBase base = *p;

  /* Considere intermedi�rio o n� do meio */
  ImplBase intermediario = base->dir;

  /* O n� direito do intermedi�rio ser� a nova raiz */
  ImplBase novaRaiz = intermediario->esq;

  /*
   * O intermediario passa a ter como sub�rvore esquerda a sub�rvore
   * direita da nova raiz, seguindo as regras de arvores de busca
   */
  intermediario->esq = novaRaiz->dir;

  /*
   * A raiz passa a ter como sub�rvore direita a
   * sub�rvore esquerda da nova raiz, seguindo as regras de arvores de busca
   */
  base->dir = novaRaiz->esq;
  
  /*
   * Seguindo as regras de arvores de busca a nova raiz passa a ter como
   * filho esquerdo a raiz e como filho direito o intermediario
   */
  novaRaiz->esq = base;
  novaRaiz->dir = intermediario;
  
  /*
   * O fator de balanceamento � acertado de acordo
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
   * Essa rota��o deixa a nova raiz balanceada
   */
  novaRaiz->bal = 0;
  
  /* O n� esquerdo do intermedi�rio ser� a nova raiz */
  *p = novaRaiz;
}

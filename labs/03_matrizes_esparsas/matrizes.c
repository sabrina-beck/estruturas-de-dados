/* Laborat�rio 03 - matrizes esparsas ligadas - implementa��o. */
/* Adapta��o do exerc�cio originalmente preparado por Jorge Stolfi */
/* Sabrina Beck Angelini                                RA157240 */
/* Data: 20/09/2014                                     Turma: E */

/* Complete todos os trechos indicados. */

#include <stdio.h>
#include "matrizes.h"
#include "balloc.h"

void erro(char *msg)
  { 
    printf("\n*** %s\n", msg); 
    exit(1);
  }  

void prox_linha(void)
  { char c;
    do { scanf("%c", &c); } while ((c != '\n') && (c != EOF));
  }

void inicializa(matriz *a, int m, int n)
  {
    ap_elemento r, t;
    int i;
    if ((m < 1) || (m > LCMAX)) { erro("inicializa: n�mero de linhas inv�lido"); }
    if ((n < 1) || (n > LCMAX)) { erro("inicializa: n�mero de colunas inv�lido"); }
    a->nlins = m;
    a->ncols = n;
    a->nelems = 0;
    a->clin = (ap_elemento *)MALLOC((m+1)*sizeof(ap_elemento));
    a->ccol = (ap_elemento *)MALLOC((n+1)*sizeof(ap_elemento));
    /* Cria a cabe�a das cabe�as "r". */
    r = (ap_elemento)MALLOC(sizeof(elemento));
    if (r == NULL) { erro("inicializa: mem�ria esgotada"); }
    r->lin = m;
    r->col = n;
    r->val = 0;
    r->esq = r; r->dir = r;
    r->ac = r; r->ab = r;
    a->clin[m] = r;
    a->ccol[n] = r;
    /* Cria cabe�as das linhas: */
    for (i = 0; i < m; i++)
      { t = (ap_elemento)MALLOC(sizeof(elemento));
        if (t == NULL) { erro("inicializa: mem�ria esgotada"); }
        t->lin = i;
        t->col = n;
        t->val = 0;
        t->esq = t; t->dir = t;
        /* Insere logo acima da super-cabe�a: */
        t->ac = r->ac; t->ab = r;
        t->ab->ac = t;
        t->ac->ab = t;
        a->clin[i] = t;
      }
    /* Cria cabe�as das colunas: */
    for(i = 0; i < n; i++) {
      t = (ap_elemento) MALLOC(sizeof(elemento));
      if(t == NULL) {
        erro("inicializa: mem�ria esgotada");
      }
      t->lin = m;
      t->col = i;
      t->val = 0;
      t->ac = t;
      t->ab = t;
      t->esq = r->esq;
      t->dir = r;
      /* Insere depois do cabe�a n� */
      t->dir->esq = t;
      t->esq->dir = t;
      a->ccol[i] = t;
    }
  }

void libera(matriz *a) {
  /* Libera toda a mem�ria din�mica ocupada por uma matriz */
    /* Libera as linhas */
    int i;
    int nlins = a->nlins;
    for(i = 0; i < nlins; i++) {
      ap_elemento cabecaLinha = a->clin[i];
      ap_elemento atual = cabecaLinha->esq;
      ap_elemento prox;
      /* Libera o conte�do de cada linha */
      while(atual != cabecaLinha) {
        prox = atual->esq;
        FREE(atual);
        atual = prox;
      }
      /* Libera o cabe�a da linha */
      FREE(cabecaLinha);
    }
    
    for(i = 0; i <= a->ncols; i++) {
      /* Libera as cabe�as das colunas e o super cabe�a */
      FREE(a->ccol[i]);
    }
    
    /* Libera vetores de linha e de coluna */
    FREE(a->clin);
    FREE(a->ccol);
    
}

void encontra(matriz *a, int i, int j, ap_elemento *ppl, ap_elemento *ppc)
  /* Fun��o auxiliar: se o elemento "a[i,j]" existe,
    devolve seu endere�o em "*ppl" e "*ppc".  Caso contr�rio,
    devolve nessas vari�veis os endere�os dos seus sucessores
    imediatos na linha e coluna (possivelmente as respectivas
    cabe�as). */
  {
    ap_elemento pl, pc;
    if ((i < 0) || (i >= a->nlins)) { erro("encontra: linha inv�lida"); }
    if ((j < 0) || (j >= a->ncols)) { erro("encontra: coluna inv�lida"); }
    /* Procura elemento "pl" na linha "i": */
    pl = a->clin[i]; 
    pl = pl->dir; while (pl->col < j) { pl = pl->dir; }
    if (pl->col == j)
      { pc = pl; }
    else
      { /* Procura elemento "pc" na coluna "j": */
        pc = a->ccol[j];
        pc = pc->ab; while (pc->lin < i) { pc =  pc->ab; }
        /* Consist�ncia: */
        if (pc == pl) { erro("encontra: apontadores pirados"); }
      }
    if ((pl->lin != i) || (pl->col < j)) { erro("encontra: pl inconsistente"); }
    if ((pc->col != j) || (pc->lin < i)) { erro("encontra: pc inconsistente"); }
    (*ppl) = pl; (*ppc) = pc;
  } 

float valor(matriz *a, int i, int j)
  {
    ap_elemento pl, pc;
    encontra(a, i, j, &pl, &pc); 
    if (pl != pc)
      { return 0; }
    else
      { return pl->val; }
  }

void remove_elem(matriz *a, ap_elemento r)
  /* Fun��o auxiliar: elimina um elemento "r" da matriz "a". */
  {
    /* Acerta ponteiros para retirar o elemento da matriz */
    r->ab->ac = r->ac;
    r->ac->ab = r->ab;
    r->esq->dir = r->dir;
    r->dir->esq = r->esq;
    /* Libera a mem�ria */
    FREE(r);
    /* Decrementa o numero de elementos durante a remo��o */
    a->nelems--;
  }
 
void insere_elem(matriz *a, int i, int j, float v, ap_elemento pl, ap_elemento pc) 
  /* Fun��o auxiliar: insere um elemento de valor "v" e �ndices "[i,j]",
    dadas as posi��es dos sucessores do elemento "a[i,j]" na linha e 
    coluna, respectivamente (possivelmente cabe�as).  Sup�e que o 
    elemento n�o est� na matriz, e que "v != 0". */
  {
    ap_elemento r;
    if (v == 0) { erro("insere: elemento nulo"); }
    if (pl->col < j) { erro("insere: pl inconsistente"); }
    if (pc->lin < i) { erro("insere: pc inconsistente"); }
    r = (ap_elemento)MALLOC(sizeof(elemento));
    r->lin = i;
    r->col = j;
    r->val = v;
    /* Insere o elemento nas listas da linha e da coluna: */
    /* Acerta os ponteiros na coluna */
    r->ab = pc;
    r->ac = pc->ac;
    pc->ac = r;
    r->ac->ab = r;
    /* Acerta os ponteiros na linha */
    r->dir = pl;
    r->esq = pl->esq;
    pl->esq = r;
    r->esq->dir = r;
    /* Incrementa o numero de elementos na inclus�o */
    a->nelems++;
  }   

void atribui(matriz *a, int i, int j, float v)
  {
    ap_elemento pl, pc;
    encontra(a, i, j, &pl, &pc); 
    if (pl != pc)
      { /* Elemento n�o existe; se "v" n�o � nulo, precisa encaixar: */
        if (v != 0.0) { insere_elem(a, i, j, v, pl, pc); }
      }
    else
      { /* Elemento existe; se "v" � nulo, precisa remover, sen�o alterar: */
        if (v != 0.0) { pl->val = v; } else { remove_elem(a, pl); }
      }
  }

void le_matriz(matriz *a)
  { int m, n, d;
    int i, j; float v;
    int k;

    scanf("%d %d %d", &m, &n, &d); prox_linha();
    inicializa(a, m, n);
    for (k = 0; k < d; k++)
      { scanf("%d %d %f", &i, &j, &v); prox_linha();
        if (v != 0) { insere_elem(a, i, j, v, a->clin[i], a->ccol[j]); }
      }
  }

void imprime_matriz(matriz *a)
  { int i;
    printf("%d %d %d\n", a->nlins, a->ncols, a->nelems);
    for (i = 0; i < a->nlins; i++)
      { elemento *p = a->clin[i]->dir;
        while (p->col < a->ncols) 
          { printf("  %2d %2d %8.2f\n", p->lin, p->col, p->val);
            p = p->dir;
          }
      }
  }
 
void transpoe(matriz *a, matriz *t)
  { int i;
    inicializa(t, a->ncols, a->nlins);
    /* Percorre as linhas da matriz */
    for(i = 0; i < a->nlins; i++) {
      ap_elemento atual = a->clin[i]->dir;
      /* Percorre as colunas da matriz */
      while(atual->val != 0.0) {
        int linha = atual->col;
        int coluna = atual->lin;
        float valor = atual->val;
        /* Insere elementos na transposta trocando linha por coluna */
        insere_elem(t, linha, coluna, valor, t->clin[linha], t->ccol[coluna]);
        atual = atual->dir;
      }
    }
  }

void soma(matriz *a, matriz *b, matriz *s)
  {
    int i, j; float v;
    /* Verifica se possuem mesmas dimens�es: */
    if ((a->nlins != b->nlins) || (a->ncols != b->ncols))
      erro("soma: matrizes com tamanhos diferentes");
    /* Inicializa matriz "s" com mesmas dimensoes de "a" e "b": */
    inicializa(s, a->nlins, a->ncols);
    for(i = 0; i < a->nlins; i++)
      for(j = 0; j < a->ncols; j++) {
        v = valor(a, i, j) + valor(b, i, j);
        if(v != 0.0) {
          /* Insere a soma de cada elemento na matriz de resultados */
          insere_elem(s, i, j, v, s->clin[i], s->ccol[j]);
        }
      }
  }
  
void multiplica(matriz *a, matriz *b, matriz *p) 
  {
    int i, j;
    if ((a->ncols) != (b->nlins)) { erro("multiplica: tamanhos invalidos"); }
    inicializa(p, a->nlins, b->ncols);
    /* i percorre as linhas de a */
    for(i = 0; i < a->nlins; i++) {
      /* j percorre as colunas de b */
      for(j = 0; j < b->ncols; j++) {
          float mult = 0.0;
          ap_elemento atualLinhaA = a->clin[i]->dir;
          ap_elemento atualColunaB = b->ccol[j]->ab;
          /*
           * Percorre a linha i de a e a coluna j de b fazendo um
           * produto escalar entre esses vetores
           */
          while(atualLinhaA->val != 0 && atualColunaB->val != 0) {
            /* Se coluna e linha baterem multiplica os valores */
            if(atualLinhaA->col == atualColunaB->lin) {
              mult += atualLinhaA->val * atualColunaB->val;
              atualLinhaA = atualLinhaA->dir;
              atualColunaB = atualColunaB->ab;
            }
            /*
             * Se n�o baterem � porque o elemento correspondente na
             * multiplica��o da outra matriz � nulo, logo o resultado
             * da multiplica��o ser� nulo tamb�m
             */
            else if(atualLinhaA->col < atualColunaB->lin)
              atualLinhaA = atualLinhaA->dir;
            else
              atualColunaB = atualColunaB->ab;
        }
        /* Insere o valor na matriz resultante somente se ele n�o for nulo */
        if(mult != 0.0)
          insere_elem(p, i, j, mult, p->clin[i], p->ccol[j]);
      }
    }
  }


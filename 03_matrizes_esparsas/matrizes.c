/* Laboratório 03 - matrizes esparsas ligadas - implementação. */
/* Adaptação do exercício originalmente preparado por Jorge Stolfi */

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
    if ((m < 1) || (m > LCMAX)) { erro("inicializa: número de linhas inválido"); }
    if ((n < 1) || (n > LCMAX)) { erro("inicializa: número de colunas inválido"); }
    a->nlins = m;
    a->ncols = n;
    a->nelems = 0;
    a->clin = (ap_elemento *)MALLOC((m+1)*sizeof(ap_elemento));
    a->ccol = (ap_elemento *)MALLOC((n+1)*sizeof(ap_elemento));
    /* Cria a cabeça das cabeças "r". */
    r = (ap_elemento)MALLOC(sizeof(elemento));
    if (r == NULL) { erro("inicializa: memória esgotada"); }
    r->lin = m;
    r->col = n;
    r->val = 0;
    r->esq = r; r->dir = r;
    r->ac = r; r->ab = r;
    a->clin[m] = r;
    a->ccol[n] = r;
    /* Cria cabeças das linhas: */
    for (i = 0; i < m; i++)
      { t = (ap_elemento)MALLOC(sizeof(elemento));
        if (t == NULL) { erro("inicializa: memória esgotada"); }
        t->lin = i;
        t->col = n;
        t->val = 0;
        t->esq = t; t->dir = t;
        /* Insere logo acima da super-cabeça: */
        t->ac = r->ac; t->ab = r;
        t->ab->ac = t;
        t->ac->ab = t;
        a->clin[i] = t;
      }
    /* Cria cabeças das colunas: */
    for(i = 0; i < n; i++) {
      t = (ap_elemento) MALLOC(sizeof(elemento));
      if(t == NULL) {
        erro("inicializa: memória esgotada");
      }
      t->lin = m;
      t->col = i;
      t->val = 0;
      t->ac = t;
      t->ab = t;
      t->esq = r->esq;
      t->dir = r;
      /* Insere depois do cabeça nó */
      t->dir->esq = t;
      t->esq->dir = t;
      a->ccol[i] = t;
    }
  }

void libera(matriz *a) {
  /* Libera toda a memória dinâmica ocupada por uma matriz */
    /* Libera as linhas */
    int i;
    int nlins = a->nlins;
    for(i = 0; i < nlins; i++) {
      ap_elemento cabecaLinha = a->clin[i];
      ap_elemento atual = cabecaLinha->esq;
      ap_elemento prox;
      /* Libera o conteúdo de cada linha */
      while(atual != cabecaLinha) {
        prox = atual->esq;
        FREE(atual);
        atual = prox;
      }
      /* Libera o cabeça da linha */
      FREE(cabecaLinha);
    }
    
    for(i = 0; i <= a->ncols; i++) {
      /* Libera as cabeças das colunas e o super cabeça */
      FREE(a->ccol[i]);
    }
    
    /* Libera vetores de linha e de coluna */
    FREE(a->clin);
    FREE(a->ccol);
    
}

void encontra(matriz *a, int i, int j, ap_elemento *ppl, ap_elemento *ppc)
  /* Função auxiliar: se o elemento "a[i,j]" existe,
    devolve seu endereço em "*ppl" e "*ppc".  Caso contrário,
    devolve nessas variáveis os endereços dos seus sucessores
    imediatos na linha e coluna (possivelmente as respectivas
    cabeças). */
  {
    ap_elemento pl, pc;
    if ((i < 0) || (i >= a->nlins)) { erro("encontra: linha inválida"); }
    if ((j < 0) || (j >= a->ncols)) { erro("encontra: coluna inválida"); }
    /* Procura elemento "pl" na linha "i": */
    pl = a->clin[i]; 
    pl = pl->dir; while (pl->col < j) { pl = pl->dir; }
    if (pl->col == j)
      { pc = pl; }
    else
      { /* Procura elemento "pc" na coluna "j": */
        pc = a->ccol[j];
        pc = pc->ab; while (pc->lin < i) { pc =  pc->ab; }
        /* Consistência: */
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
  /* Função auxiliar: elimina um elemento "r" da matriz "a". */
  {
    /* Acerta ponteiros para retirar o elemento da matriz */
    r->ab->ac = r->ac;
    r->ac->ab = r->ab;
    r->esq->dir = r->dir;
    r->dir->esq = r->esq;
    /* Libera a memória */
    FREE(r);
    /* Decrementa o numero de elementos durante a remoção */
    a->nelems--;
  }
 
void insere_elem(matriz *a, int i, int j, float v, ap_elemento pl, ap_elemento pc) 
  /* Função auxiliar: insere um elemento de valor "v" e índices "[i,j]",
    dadas as posições dos sucessores do elemento "a[i,j]" na linha e 
    coluna, respectivamente (possivelmente cabeças).  Supõe que o 
    elemento não está na matriz, e que "v != 0". */
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
    /* Incrementa o numero de elementos na inclusão */
    a->nelems++;
  }   

void atribui(matriz *a, int i, int j, float v)
  {
    ap_elemento pl, pc;
    encontra(a, i, j, &pl, &pc); 
    if (pl != pc)
      { /* Elemento não existe; se "v" não é nulo, precisa encaixar: */
        if (v != 0.0) { insere_elem(a, i, j, v, pl, pc); }
      }
    else
      { /* Elemento existe; se "v" é nulo, precisa remover, senão alterar: */
        if (v != 0.0) { pl->val = v; } else { remove_elem(a, pl); }
      }
  }

void le_matriz(matriz *a)
  { int m, n, d;
    int i, j; float v;
    int ip, jp; /* Índices do elemento anterior. */
    int k;

    scanf("%d %d %d", &m, &n, &d); prox_linha();
    inicializa(a, m, n);
    ip = -1; jp = n-1;
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
    erro("!!!COMPLETAR");
  }

void soma(matriz *a, matriz *b, matriz *s)
  {
    int i, j; float v;
    /* Verifica se possuem mesmas dimensões: */
    if ((a->nlins != b->nlins) || (a->ncols != b->ncols))
      erro("soma: matrizes com tamanhos diferentes");
    /* Inicializa matriz "s" com mesmas dimensoes de "a" e "b": */
    inicializa(s, a->nlins, a->ncols);
    for(i = 0; i < a->nlins; i++)
      for(j = 0; j < a->ncols; j++) {
        float soma = valor(a, i, j) + valor(b, i, j);
        ap_elemento pl;
        ap_elemento pc;
        encontra(s, i, j, &pl, &pc);
        insere_elem(s, i, j, soma, pl, pc); 
      }
  }

void multiplica(matriz *a, matriz *b, matriz *p) 
  {
    int i, j;
    if ((a->ncols) != (b->nlins)) { erro("multiplica: tamanhos invalidos"); }
    inicializa(p, a->nlins, b->ncols);
    erro("!!!COMPLETAR");
  }

/* Laboratório 03 - matrizes esparsas ligadas - interface. */
/* Adaptação do exercício originalmente preparado por Jorge Stolfi */

#define LCMAX 10000  /* Número máximo de linhas e de colunas. */

    /* As linhas e colunas da matriz esparsa são numeradas "0 .. nlins-1" e
      "0 .. ncols-1", respectivamente.

      Os elementos não nulos de cada linha "i" formam uma lista
      circular com cabeça, duplamente ligada pelos campos "dir"
      e "esq". A cabeça da linha, "clin[i]", fica na
      extremidade direita da mesma, e tem "clin[i]->col = ncols".

      Analogamente, os elementos de cada coluna "j" formam uma lista
      circular com cabeça, duplamente ligada pelos campos "ab" e
      "ac". A cabeça da coluna, "ccol[j]", fica na extremidade
      inferior da mesma, com "ccol[j]->lin = nlins".

      As cabeças de todas as linhas são ligadas entre si pelos
      campos "ab" e "ac", e as cabeças das colunas são
      ligadas pelos campos "dir" e "esq". As duas listas de
      cabeças compartilham um único nó *super-cabeça* "clin[nlins] =
      ccol[ncols]", no canto inferior direito da matriz
      (com "lin = nlins" e "col = ncols"). */

/* Representação ligada de matrizes esparsas: */
typedef struct elemento *ap_elemento;

typedef struct elemento
  { int lin, col;          /* Índices na matriz original. */ 
    float val;             /* Valor do elemento. */
    ap_elemento dir;       /* Próx. elem. na mesma linha, ou cabeça da linha. */
    ap_elemento esq;       /* Elem. ant. na mesma linha, ou cabeça da linha. */
    ap_elemento ab;        /* Próx. elem. na mesma coluna, ou cabeça da coluna. */
    ap_elemento ac;        /* Elem. ant. na mesma coluna, ou cabeça da coluna. */
  } elemento;

typedef struct 
  { int nlins, ncols;      /* Dimensões da matriz original. */  
    int nelems;            /* Número de elementos não nulos. */
    ap_elemento *clin;     /* "clin[i]" = cabeça da linha "i". */
    ap_elemento *ccol;     /* "ccol[j]" = cabeça da coluna "j". */
  } matriz;


/* Os procedimentos abaixo devem interromper o programa com 
  uma mensagem de erro quando os argumentos fornecidos não
  satisfazem as condições especificadas. Veja o procedimento 
  "erro" mais abaixo. */

void inicializa(matriz *a, int m, int n);
  /* Inicializa "a" com uma matriz nula de "m" linhas e "n" colunas. */

void libera(matriz *a);
  /* Libera toda a memória dinâmica ocupada por uma matriz */

float valor(matriz *a, int i, int j);
  /* Retorna o valor do elemento da matriz "a" com índices "[i,j]"
    (que devem estar nos respectivos intervalos de validade).  */

void atribui(matriz *a, int i, int j, float v);
  /* Armazena o valor "v" na matriz "a", com índices "[i,j]"
    (que devem estar nos respectivos intervalos de validade). */

void soma(matriz *a, matriz *b, matriz *s);
  /* Coloca em "s" a soma das matrizes "a" e "b",
    que devem ter as mesmas dimensões (linhas e colunas).  */

void multiplica(matriz *a, matriz *b, matriz *p);
  /* Retorna na matriz "p" o produto das matrizes "a" e "b".
     O número de colunas de "a" deve ser igual ao número de linhas de "b". */

void transpoe(matriz *a, matriz *t);
  /* Coloca em "t" a transposta da matriz "a". */

void le_matriz(matriz *a);
  /* Lê uma matriz e coloca-a em "a". A próxima linha  do arquivo
    de entrada deve conter três inteiros "nlins", "ncols", "nelems" 
    (número de linhas, de colunas, e de elementos não nulos da matriz).
    Em seguida devem vir "nelems" linhas do arquivo, cada qual contendo
    os índices "lin" e "col" e o valor "val" de um elemento não nulo da
    matriz. */

void imprime_matriz(matriz *a);
  /* Imprime os elementos da matriz "a", no formato esperado
    por "le_matriz". */

void erro(char *msg);
  /* Função auxiliar: imprime "msg" e termina o programa. */

void prox_linha(void);
  /* Função auxiliar: pula caracteres até o próximo fim-de-linha. */


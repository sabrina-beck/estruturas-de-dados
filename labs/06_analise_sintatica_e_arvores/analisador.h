/* 
 * analisador.h: Interface para o módulo de transformação de
 * expressões em árvores binárias e seus percursos.
 */

/* Tamanho máximo de uma expressão */
#define TAM_MAX_EXPR 100

/* Códigos de erro */

typedef enum{
  EXPR_VALIDA,
  OPERANDO_ESPERADO,
  OPERADOR_ESPERADO,
  FECHA_PARENTESE_ESPERADO,
  CARACTERE_INVALIDO,
  CADEIA_DE_BRANCOS
} CodigosErro;

/* Estrutura para retorno de erro, indicando tipo do erro e posição */
/* na cadeia de entrada.                                            */
typedef struct erro {
  int posicao; 
  int codigoErro; 
} Erro; 

/* Estrutura de árvore para representar uma expressão. O campo 'info'
   contém uma variável ou um operador. */
typedef struct NoArvBin {
  char info;
  struct NoArvBin *esq, *dir;
} NoArvBin, *ArvBin;


Erro InArv(char* infixa, ArvBin *arv);
/* Transforma a notação infixa em árvore binária.  Em caso de erro,
   devolve o código e a posição na cadeia de entrada onde o erro foi
   encontrado.  */
   
void ArvPre(ArvBin arv, char *pre);
/* Produz a representação pré-fixa a partir da árvore. */

void ArvPos(ArvBin arv, char *pos);
/* Produz a representação pós-fixa a partir da árvore. */

void LiberaArv(ArvBin arv);
/* Libera o espaço ocupado pela árvore. */

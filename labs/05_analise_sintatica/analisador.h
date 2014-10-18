/*
  Disciplina: MC202
  Tarefa 05 
  Segundo semestre de 2014
*/

/* 
 * analisador.h: Interface para o módulo de transformação de expressões na
 * notação infixa para pós-fixa.
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

/* Estrutura para retorno de erro, indicando o tipo do erro e a posição
   na cadeia de entrada.  */
typedef struct erro {
  int posicao; 
  int codigoErro; 
} Erro; 

Erro InPos(char* infixa, char* posfixa);
/* Transforma uma expressão da notação infixa para a pós-fixa. Em caso
   de erro, devolve o código e a posição na cadeia de entrada onde o
   erro foi encontrado.  */

/*
  Disciplina: MC202
  Tarefa 05 
  Segundo semestre de 2014
*/

/*
 * principal.c - Arquivo de teste para o módulo de transformação de
 * expressões na notação infixa para pós-fixa.
 */
#include <stdio.h>
#include <string.h>

#include "analisador.h"


/* Mensagens de erro para os códigos previstos em analisador.h */
char *msg_erro[] = {
  "Expressão válida.",
  "Operando esperado nesta posição.",
  "Operador esperado nesta posição.",  
  "Fecha parêntese esperado nesta posição.",
  "Caractere inválido nesta posição.",
  "Cadeia de brancos."
};


void mostraErro(Erro erro) {
/* Imprime uma mensagem de erro. Não encerra a execução do programa.    */
  printf("Erro:   %*s^\n",erro.posicao,""); /* Mostra posição do primeiro erro encontrado */
  printf("        %s\n\n", msg_erro[erro.codigoErro]);
} /* mostraErro */


int leExpr(char *in) {
/* Tenta ler uma expressão da entrada, desprezando linhas maiores do */
/* que TAM_MAX_EXPR, linhas vazias e linhas de comentário. Retorna o */
/* número de caracteres lidos.                                       */
  int m;
  char ch;
  
  for (;;) {
    if (fgets(in,TAM_MAX_EXPR+2,stdin)==NULL) /* fim de arquivo */
      return 0;
    m = strlen(in);
    if (in[0]=='#')  { /* comentário */
      printf("%s",in);
    } else if (in[m-1]!='\n') { /* '\n' não coube */
      printf("Infixa: %s",in);
      do {
	ch=getc(stdin);
        putc(ch,stdout);
      } while (ch!='\n');    /* resto da entrada */
      printf("Erro:   Cadeia de entrada muito longa.\n\n");
    } else if (m>1) {        /* cadeia não vazia */
      in[m-1] = '\0';             /* elimina '\n' */
      return m-1;
    }
  }
  
} /* LeExpr */


int main() {
  char in[TAM_MAX_EXPR+2], pos[TAM_MAX_EXPR+1];
  Erro erro;

  while (leExpr(in)>0) {
      erro = InPos(in, pos);
      printf("Infixa: %s\n", in);
      if (erro.codigoErro == EXPR_VALIDA) {
	printf("Posfixa: %s\n\n", pos);
      }
      else
	mostraErro(erro); 
  }
        
  printf("Processamento terminado\n");
  
  return 0;
  
} /* main */



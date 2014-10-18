/*
 * principal.c - Arquivo de teste para o módulo de transformação de
 * expressões em notação infixa para árvores binárias e representações
 * pré-fixa e pós-fixa.
 */
#include <stdio.h>
#include <string.h>
#include "balloc.h"
#include "analisador.h"

/* Função despejaArv para ser usada na depuração */
#include "imprimearvore.h"
char cadeiainfo[2] = "*"; /* conterá a cadeia de um caractere */
char *vazia = "Árvore vazia\n";

ArvBin esq(ArvBin a, int d) {
  /* Supõe a!=NULL */
  return a->esq;
}

ArvBin dir(ArvBin a, int d) {
  /* Supõe a!=NULL */
  return a->dir;
}

char *info(ArvBin a, int d) {
  /* Supõe a!=NULL */
  cadeiainfo[0] = a->info;
  return cadeiainfo;
}


void despejaArv(ArvBin a) {
/* Função para depuração: despeja a árvore "deitada" */
  printf("\nÁrvore despejada:\n");
  ImprimeArvore(a,(subarvfunc*)esq,(subarvfunc*)dir,(infofunc*)info,NULL,1,vazia);
  printf("\n");
}

/* Função auxiliar que imprime dados sobre bloco de memória não
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {

  printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
  
} /* bprint */


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
  int i;
  printf("Erro:   ");  /* Mostra posição do primeiro erro encontrado */
  for (i = 0; i < erro.posicao; i++)
    printf(" ");
  printf("^\n"); 
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
  char in[TAM_MAX_EXPR+2], res[TAM_MAX_EXPR+1];
  Erro erro;
  ArvBin arv;

  while (leExpr(in)>0) {
    erro = InArv(in,&arv);
    printf("Infixa: %s\n", in);
    if (erro.codigoErro == EXPR_VALIDA) {
      ArvPre(arv,res);
      /* para ser usado em depuração: basta descomentar */
      /* despejaArv(arv); */
      printf("Prefixa: %s\n",res);
      ArvPos(arv,res);
      printf("Posfixa: %s\n\n",res);
    }
    else
      mostraErro(erro); 
    printf("\n");
    LiberaArv(arv);
  }
        
 /* Verifica se foram liberados todos os blocos alocados */
  bapply(bprint);

        
  printf("Processamento terminado\n");
  
  return 0;
  
} /* main */



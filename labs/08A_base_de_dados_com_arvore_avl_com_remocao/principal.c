/* 
 * principal.c - Este programa testa o m�dulo 'base.c', operando
 * sobre uma �rvore AVL.
 *
 *  Comandos aceitos:
 *       i <ra> <nome> insere novo n� com ra e nome
 *       c <ra>        consulta ra
 *       d             imprime a �rvore sob forma gr�fica
 *       r <ra>        remove ra, caso exista
 *       n  imprime o n�mero de n�s na �rvore
 *       a  imprime a altura da �rvore
 *       p  imprime em inordem a base
 *       d             imprime a �rvore sob forma gr�fica
 *       l  libera base
 *       h  imprime resumo
 *       #  coment�rio
 *
 * A libera��o total da mem�ria din�mica alocada por 'MALLOC' � 
 *      testada no fim utilizando a fun��o 'bapply(bprint)'.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balloc.h"
#include "base.h" 


void ErroAVL() {
  /* Interrompe o programa, emitindo mensagem de erro. */ 
  fprintf(stderr,"Erro na implementa��o da �rvore AVL.\n");
  exit(0);
}

/* Fun��o auxiliar que imprime dados sobre bloco de mem�ria n�o
   liberado. */
void bprint(char *who, int where, void *ptr, size_t size) {
    printf("Arquivo: %s, linha: %d, tamanho: %d\n",who,where,(int)size);
} /* bprint */

void ImprimeComentario() {
  char c;
  int res;
    do { 
      res = scanf("%c", &c); 
      if (res!=EOF)
	printf("%c",c);
    } while ((res!=EOF) && (c!='\n'));
}

void ImprimeAluno(Aluno *aluno) {
  printf("%06d %s\n", aluno->ra, aluno->nome);
}

/* L� um nome da entrada, com no m�ximo 100 caracteres. */

#define COMPR_MAX_NOME 100
String leNome() {
  String nome;
  char buffer[COMPR_MAX_NOME+1];
  char c;
  int i, res;

  i = 0;
  while (i < COMPR_MAX_NOME && (res = scanf("%c", &c)) != EOF && c != '\n')
    buffer[i++] = c;
  buffer[i] = '\0';
  /* Despreza o restante da linha caso o nome seja maior que COMPR_MAX_NOME */
  if (i == COMPR_MAX_NOME && !(res == EOF || c == '\n'))
    while (scanf("%c", &c) != EOF && c != '\n') ;
  nome = MALLOC(strlen(buffer)+1);
  strcpy(nome, buffer);
  return nome;
}

Boolean AuxVerificaBase(Base p, int *alt) {
/* Verifica se a �rvore apontada por 'p' tem a estrutura de uma �rvore
   AVL e devolve a sua altura em 'alt'.*/
  int altEsq, altDir, bal, resEsq, resDir;
  if (p==NULL) {
    *alt = 0;
    return true;
  }
  resEsq = AuxVerificaBase(SubEsq(&p),&altEsq);
  resDir = AuxVerificaBase(SubDir(&p),&altDir);
  bal = FatorBal(&p);
  *alt = ((altEsq<altDir) ? altDir : altEsq) + 1;
  return ((bal>=-1) && (bal<=+1) && (bal==(altDir-altEsq)) && resEsq && resDir);
  
} /* AuxVerificaBase */

Boolean VerificaBase(Base p) {
/* Verifica se a �rvore apontada por 'p' tem a estrutura de uma �rvore
   AVL. */
  
    int alt;
    Boolean res = AuxVerificaBase(p,&alt);
    return (res && (alt==AlturaBase(&p)));
    
} /* VerificaBase */

int main() {
  Aluno aluno;
  Base base;
  Boolean fim = false;
  int ra;
  char acao;

  base = CriaBase(); 

  do { 
    if (scanf("%c", &acao) ==  EOF)
      fim = true; 
    else {
      printf("A��o: %c", acao);
      switch (acao) { 
          
      case '#':
	ImprimeComentario();
	break;
          
      case 'i':
      case 'I':
	scanf("%d ",&aluno.ra);
	aluno.nome = leNome();
	printf(" %06d %s\n", aluno.ra, aluno.nome);
	if (!InsereBase(&base, aluno)) {
	  printf("Ra %06d j� estava presente na base de dados.\n", aluno.ra);
	  FREE(aluno.nome);
	} else
	  if (!VerificaBase(base)) {
    ImprimeBase(&base);
	    ErroAVL();
	  }
	break;
	
      case 'c':
      case 'C':
	scanf("%d",&ra);
	printf(" %06d",ra);
	ImprimeComentario();
	if (ConsultaBase(&base, ra, &aluno))
	  printf("%06d %s \n", ra, aluno.nome);
	else
	  printf("Ra %06d n�o encontrado na base de dados.\n", ra);
	break;
        
      case 'd':
      case 'D':
	ImprimeComentario();
	ImprimeBase(&base);
	break;

      case 'r':
      case 'R':
	scanf("%d",&ra);
	printf(" %06d",ra);
	ImprimeComentario();
	if (RemoveBase(&base, ra)) {
	  printf("Ra %06d removido.\n", ra);
    ImprimeBase(&base);
	  if (!VerificaBase(base))
	    ErroAVL();
	}
	else
	  printf("Ra %06d n�o encontrado na base de dados.\n", ra);
	break;
            
      case 'n':
      case 'N':
	ImprimeComentario();
	printf("N�mero de n�s na base de dados: %d.\n", NumeroNosBase(&base));
	break;

      case 'a':
      case 'A':
	ImprimeComentario();
	printf("Altura da base de dados: %d.\n", AlturaBase(&base));
	break;
            
      case 'l':
      case 'L':
	ImprimeComentario();
	LiberaBase(&base);
	base = CriaBase(); /* Reinicializa nbase */
	break;

      case 'p':
      case 'P':
	ImprimeComentario();
	PercorreBase(&base,ImprimeAluno);
	break;
            
      case 'h':
      case 'H':
	ImprimeComentario();
	printf("\n");
	printf("#             : coment�rio.\n");
	printf("i <ra> <nome> : insere ra e nome na base.\n");
	printf("c <ra>        : consulta ra na base.\n");
	printf("r <ra>        : remove ra da base.\n");
	printf("l             : libera base.\n");
	printf("p             : executa um percurso inordem na base.\n");
	printf("n             : imprime o n�mero de n�s na base.\n");
	printf("a             : imprime a altura da base.\n");
	printf("h             : imprime resumo.\n");
	printf("x             : t�rmino.\n");
	printf("q             : t�rmino.\n");
	fim = true;
	break;
            
      case 'x':
      case 'X':
      case 'q':
      case 'Q':
	ImprimeComentario();
	fim = true;
	break;
      }  /* switch */
    }
  } while (!fim);
      
    
    
  bapply(bprint);
   
  printf("Processamento terminado\n");

  return 0;
  
}  /* main */

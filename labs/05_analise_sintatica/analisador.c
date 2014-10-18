/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 05 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: M�dulo de transforma��o de express�es na nota��o
 * infixa para p�s-fixa.
 */

#include "analisador.h"
#include <ctype.h>

/* Enum de boolean */
typedef enum {
  false, true
} boolean;

/* Vari�veis globais a este m�dulo */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

char *pos; /* Cadeia e �ndice para express�o p�sfixa (sa�da). */
int indPos;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */


/* Prot�tipos das fun��es mutuamente recursivas  */
Erro Expressao();
Erro Termo();
Erro Fator();
Erro Primario();
Erro Potencia();
void EliminaBrancos();
boolean ehCaracterValido(char c);

/* Fun��o auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma express�o da nota��o infixa para a p�s-fixa. Em caso
   de erro, devolve o c�digo e a posi��o na cadeia de entrada onde o
   erro foi encontrado.  */
  Erro erro;

  in = infixa;
  indIn = 0;
  pos = posfixa;
  indPos = 0;
  
  /* Verifica cadeia vazia */
  EliminaBrancos();
  if(!in[indIn])
    return montaErro(CADEIA_DE_BRANCOS, indPos);
  
  /*
   * Analisa a express�o infixa armazenada na vari�vel global 'in' e armazena sua vers�o posfixa
   * na vari�vel pos, caso a express�o esteja errada retorna erro
   */
  erro = Expressao();

  /* Verifica��o necess�ria para n�o acontencer o erro de OPERADOR_ESPERADO, quando ocorre outro erro */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  /*
   * Se restarem elementos a serem avaliados na express�o, o m�todo Express�o n�o achou outro
   * operador que no caso est� faltando
   */
  if(in[indIn])
      return montaErro(OPERADOR_ESPERADO, indIn);
  
  /* No fim a express�o posfixa � finalizada */
  posfixa[indPos] = '\0';
  return erro;
  
}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com c�digo de erro e posi��o */
  Erro erro;

  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;

} /* montaErro */


Erro Expressao() {
/* Processa uma express�o da cadeia de entrada 'in'.  */
  Erro erro;

  /* Se a express�o come�ar com um operador '+' ou '-', ele � un�rio */
  if(in[indIn] == '+' || in[indIn] == '-')
    erro = Primario();
  else
  /*
   * Caso n�o tenha um operador un�rio no in�cio da express�o, ent�o 
   * o primeiro termo � tratado
   */
    erro = Termo();

  /*
   * Essa verifica��o � necess�ria sempre que um m�todo retornar erro, pois neste caso, n�o � necess�rio
   * continuar a an�lise (nem poss�vel continuar) , uma vez errada a express�o a recurs�o/m�todo/an�lise deve
   * ser interrompida e o erro retornado para tratamento no programa principal.
   */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  /* Se a cadeia de entrada estiver vazia, nenhuma an�lise deve ser feita */
  if(in[indIn]) {
    /* 
     * At� que a express�o continue apresentando operadores '+' e '-' (os separadores dos termos da express�o) a
     * repeti��o deve continuar
     */
    do {
      char atual = in[indIn];
      
      /* Tratamento de caracteres inv�lidos */
      if(!ehCaracterValido(atual))
        return montaErro(CARACTERE_INVALIDO, indIn);
      
      if(atual == '+' || atual == '-') {
        /* Controle do �ndice atual na cadeia de entrada */
        indIn++;
        /* Para cada operador '+' e '-' existe um termo a ser avaliado */
        erro = Termo();
        
        /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
        if(erro.codigoErro != EXPR_VALIDA)
          return erro;
        
        /*
         * Depois de analisar o termo relacionado a esse operador ele � adicionado no fim da cadeia 'pos'
         * seguindo a regra de express�es p�s fixas
         */
        pos[indPos++] = atual;
      } else
        /* Se n�o achar mais operadores, ent�o a express�o acabou */
        break;
    } while(true);
  }
  
  return resCorreto;


} /* Expressao */

Erro Termo() {
/* Processa um termo da cadeia de entrada.  */
  Erro erro;

  /* Todo termo come�a com um fator a ser analisado */
  erro = Fator();
  
  /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  do {
    char atual = in[indIn];
    
    /* Tratamento de caracteres inv�lidos */
    if(!ehCaracterValido(atual))
      return montaErro(CARACTERE_INVALIDO, indIn);

    if(atual == '*' || atual == '/') {
        /* Controle do �ndice atual na cadeia de entrada */
        indIn++;
        
        /* Ao achar o operador de um termo outro fator deve ser analisado */
        erro = Fator();
        
        /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
        if(erro.codigoErro != EXPR_VALIDA)
          return erro;
        
        /*
         * Depois de analisar o fator relacionado a esse operador ele � adicionado no fim da cadeia 'pos'
         * seguindo a regra de express�es p�s fixas
         */
        pos[indPos++] = atual;
    } else
        /*
         * Caso nenhum operador tenha sido encontrado, ent�o o termo acabou, por consequ�ncia sua an�lise tamb�m
         */
          break;
  } while(true);
  
  /* No final tudo ocorreu bem */
  return resCorreto;

} /* Termo */

Erro Fator() {
/* Processa um fator da cadeia de entrada.  */
  char atual;
  Erro erro;
  
  /* Primeiro elimina espa�os em branco que n�o s�o avaliados */
  EliminaBrancos();
  
  atual = in[indIn];
  
  /* Tratamento de caracteres inv�lidos */
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /*
   * Se for um operando, avan�amos um no �ndice de an�lise da express�o, para analisar operadores no futuro
   * e o operando � adicionado na express�o de sa�da obedecendo as regras de express�es p�s-fixas
   */
  if(atual >= 'a' && atual <= 'z') {
    pos[indPos++] = atual;
    indIn++;
  } else if (atual == '(') {
    /* �ndice pula o parenteses, uma vez que ele n�o entra na express�o p�s-fixa */
    indIn++;
    /*
     * Se for encontrado um parenteses, uma nova express�o vir� dentro dele, que tamb�m ser� analisada
     */
    erro = Expressao();
    
    /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /*
     * No final da an�lise da express�o entre parenteses, devemos encontrar um fecha parenteses, e
     * pul�-lo na an�lise, pois ele n�o vai para a express�o p�s-fixa
     */
    if(in[indIn] == ')')
      indIn++;
    else
      /* Se o fecha parenteses n�o for encontrado, existe um erro de sintaxe */
      return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
  } else
    /* Se nenhum operando for encontrado, ent�o a express�o est� errada */
    return montaErro(OPERANDO_ESPERADO, indIn);
  
  /* Elimina espa�os em branco que n�o s�o avaliados */
  EliminaBrancos();
  
  /* Atualiza o atual, para tratamento de pot�ncia, que � um fator com operador de pot�ncia */
  atual = in[indIn];
  
  /* Trata caracteres inv�lidos */
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /* Se for encontrado um operador de pot�ncia, este tem preced�ncia aos operadores '*' e '/' */
  if (atual == '^') {
    indIn++;
    /* A pot�ncia � tratada */
    erro = Potencia();
    
    /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /* Adiciona o operador no final da express�o, seguindo a ideia de p�s-fixa */
    pos[indPos++] = atual;
  }
  
  return resCorreto;  

} /* Fator */

/*
 * Pulando o �ndice da cadeia de entrada, ignora os espa�os em branco da express�o
 */
void EliminaBrancos() {
  if(in[indIn] == ' ') {
    indIn++;
    EliminaBrancos();
  }
}

/*
 * Verifica caracter inv�lido, que � qualquer caracter n�o previsto na implementa��o
 */
boolean ehCaracterValido(char c) {
  return (c >= 'a' && c <= 'z') || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '\0' 
    || c == ')' || c == '(';
}

Erro Primario() {
/* Processa um fator prim�rio da cadeia de entrada.  */
  char atual;
  int posAnt;
  Erro erro;

  /* Guarda o operador un�rio */
  atual = in[indIn];
 
  /* Tratamento de caracter inv�lido */ 
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /* Avan�a a an�lise para o operando */
  indIn++;
  posAnt = indIn; /* armazena a posi��o do elemento anterior, caso o indice n�o mudar, ent�o est� faltando um operando */
  erro = Termo();

  /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  /* Se n�o foi analisado nenhum termo, � porque este n�o existe, logo est� faltando um operando */
  if(indIn == posAnt) {
    return montaErro(OPERANDO_ESPERADO, indIn);
  }

  /* Adiciona o operador un�rio na express�o p�s-fixa */
  pos[indPos++] = atual == '+' ? '&' : '~';
  
  return resCorreto;

} /* Primario */

Erro Potencia() {
/* Processa uma potencia da cadeia prim�ria */
  Erro erro;

  /*
   * Analise um fator da pot�ncia, na primeira vez � o expoente, pois a base j� foi
   * analisada na pr�pria fun��o Fator
   */
  erro = Fator();
  
  /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  char atual = in[indIn];
  
  /* Tratamento de caractere inv�lido */
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /*
   * Se achou novamento o operador de pot�ncia, continua a an�lise de pot�ncia, que � a opera��o
   * de maior prioridade da express�o
   */
  if(atual == '^') {
    indIn++;
    erro = Potencia();
    
    /* Verifica��o necess�ria para n�o continuar a an�lise em express�o errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /* Atualiza a express�o p�s-fixa com o operador de pot�ncia */
    pos[indPos++] = atual;
  } 

  return resCorreto;

} /* Potencia */

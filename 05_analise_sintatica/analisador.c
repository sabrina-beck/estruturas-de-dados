/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 05 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: Módulo de transformação de expressões na notação
 * infixa para pós-fixa.
 */

#include "analisador.h"
#include <ctype.h>

/* Enum de boolean */
typedef enum {
  false, true
} boolean;

/* Variáveis globais a este módulo */

char *in;  /* Cadeia e índice para expressão infixa (entrada). */
int indIn;

char *pos; /* Cadeia e índice para expressão pósfixa (saída). */
int indPos;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */


/* Protótipos das funções mutuamente recursivas  */
Erro Expressao();
Erro Termo();
Erro Fator();
Erro Primario();
Erro Potencia();
void EliminaBrancos();
boolean ehCaracterValido(char c);

/* Função auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma expressão da notação infixa para a pós-fixa. Em caso
   de erro, devolve o código e a posição na cadeia de entrada onde o
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
   * Analisa a expressão infixa armazenada na variável global 'in' e armazena sua versão posfixa
   * na variável pos, caso a expressão esteja errada retorna erro
   */
  erro = Expressao();

  /* Verificação necessária para não acontencer o erro de OPERADOR_ESPERADO, quando ocorre outro erro */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  /*
   * Se restarem elementos a serem avaliados na expressão, o método Expressão não achou outro
   * operador que no caso está faltando
   */
  if(in[indIn])
      return montaErro(OPERADOR_ESPERADO, indIn);
  
  /* No fim a expressão posfixa é finalizada */
  posfixa[indPos] = '\0';
  return erro;
  
}

/*************************************************************/
/*           Funções de implementação do analisador          */
/*************************************************************/

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com código de erro e posição */
  Erro erro;

  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;

} /* montaErro */


Erro Expressao() {
/* Processa uma expressão da cadeia de entrada 'in'.  */
  Erro erro;

  /* Se a expressão começar com um operador '+' ou '-', ele é unário */
  if(in[indIn] == '+' || in[indIn] == '-')
    erro = Primario();
  else
  /*
   * Caso não tenha um operador unário no início da expressão, então 
   * o primeiro termo é tratado
   */
    erro = Termo();

  /*
   * Essa verificação é necessária sempre que um método retornar erro, pois neste caso, não é necessário
   * continuar a análise (nem possível continuar) , uma vez errada a expressão a recursão/método/análise deve
   * ser interrompida e o erro retornado para tratamento no programa principal.
   */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  /* Se a cadeia de entrada estiver vazia, nenhuma análise deve ser feita */
  if(in[indIn]) {
    /* 
     * Até que a expressão continue apresentando operadores '+' e '-' (os separadores dos termos da expressão) a
     * repetição deve continuar
     */
    do {
      char atual = in[indIn];
      
      /* Tratamento de caracteres inválidos */
      if(!ehCaracterValido(atual))
        return montaErro(CARACTERE_INVALIDO, indIn);
      
      if(atual == '+' || atual == '-') {
        /* Controle do índice atual na cadeia de entrada */
        indIn++;
        /* Para cada operador '+' e '-' existe um termo a ser avaliado */
        erro = Termo();
        
        /* Verificação necessária para não continuar a análise em expressão errada */
        if(erro.codigoErro != EXPR_VALIDA)
          return erro;
        
        /*
         * Depois de analisar o termo relacionado a esse operador ele é adicionado no fim da cadeia 'pos'
         * seguindo a regra de expressões pós fixas
         */
        pos[indPos++] = atual;
      } else
        /* Se não achar mais operadores, então a expressão acabou */
        break;
    } while(true);
  }
  
  return resCorreto;


} /* Expressao */

Erro Termo() {
/* Processa um termo da cadeia de entrada.  */
  Erro erro;

  /* Todo termo começa com um fator a ser analisado */
  erro = Fator();
  
  /* Verificação necessária para não continuar a análise em expressão errada */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  do {
    char atual = in[indIn];
    
    /* Tratamento de caracteres inválidos */
    if(!ehCaracterValido(atual))
      return montaErro(CARACTERE_INVALIDO, indIn);

    if(atual == '*' || atual == '/') {
        /* Controle do índice atual na cadeia de entrada */
        indIn++;
        
        /* Ao achar o operador de um termo outro fator deve ser analisado */
        erro = Fator();
        
        /* Verificação necessária para não continuar a análise em expressão errada */
        if(erro.codigoErro != EXPR_VALIDA)
          return erro;
        
        /*
         * Depois de analisar o fator relacionado a esse operador ele é adicionado no fim da cadeia 'pos'
         * seguindo a regra de expressões pós fixas
         */
        pos[indPos++] = atual;
    } else
        /*
         * Caso nenhum operador tenha sido encontrado, então o termo acabou, por consequência sua análise também
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
  
  /* Primeiro elimina espaços em branco que não são avaliados */
  EliminaBrancos();
  
  atual = in[indIn];
  
  /* Tratamento de caracteres inválidos */
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /*
   * Se for um operando, avançamos um no índice de análise da expressão, para analisar operadores no futuro
   * e o operando é adicionado na expressão de saída obedecendo as regras de expressões pós-fixas
   */
  if(atual >= 'a' && atual <= 'z') {
    pos[indPos++] = atual;
    indIn++;
  } else if (atual == '(') {
    /* Índice pula o parenteses, uma vez que ele não entra na expressão pós-fixa */
    indIn++;
    /*
     * Se for encontrado um parenteses, uma nova expressão virá dentro dele, que também será analisada
     */
    erro = Expressao();
    
    /* Verificação necessária para não continuar a análise em expressão errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /*
     * No final da análise da expressão entre parenteses, devemos encontrar um fecha parenteses, e
     * pulá-lo na análise, pois ele não vai para a expressão pós-fixa
     */
    if(in[indIn] == ')')
      indIn++;
    else
      /* Se o fecha parenteses não for encontrado, existe um erro de sintaxe */
      return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
  } else
    /* Se nenhum operando for encontrado, então a expressão está errada */
    return montaErro(OPERANDO_ESPERADO, indIn);
  
  /* Elimina espaços em branco que não são avaliados */
  EliminaBrancos();
  
  /* Atualiza o atual, para tratamento de potência, que é um fator com operador de potência */
  atual = in[indIn];
  
  /* Trata caracteres inválidos */
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /* Se for encontrado um operador de potência, este tem precedência aos operadores '*' e '/' */
  if (atual == '^') {
    indIn++;
    /* A potência é tratada */
    erro = Potencia();
    
    /* Verificação necessária para não continuar a análise em expressão errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /* Adiciona o operador no final da expressão, seguindo a ideia de pós-fixa */
    pos[indPos++] = atual;
  }
  
  return resCorreto;  

} /* Fator */

/*
 * Pulando o índice da cadeia de entrada, ignora os espaços em branco da expressão
 */
void EliminaBrancos() {
  if(in[indIn] == ' ') {
    indIn++;
    EliminaBrancos();
  }
}

/*
 * Verifica caracter inválido, que é qualquer caracter não previsto na implementação
 */
boolean ehCaracterValido(char c) {
  return (c >= 'a' && c <= 'z') || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '\0' 
    || c == ')' || c == '(';
}

Erro Primario() {
/* Processa um fator primário da cadeia de entrada.  */
  char atual;
  int posAnt;
  Erro erro;

  /* Guarda o operador unário */
  atual = in[indIn];
 
  /* Tratamento de caracter inválido */ 
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /* Avança a análise para o operando */
  indIn++;
  posAnt = indIn; /* armazena a posição do elemento anterior, caso o indice não mudar, então está faltando um operando */
  erro = Termo();

  /* Verificação necessária para não continuar a análise em expressão errada */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  /* Se não foi analisado nenhum termo, é porque este não existe, logo está faltando um operando */
  if(indIn == posAnt) {
    return montaErro(OPERANDO_ESPERADO, indIn);
  }

  /* Adiciona o operador unário na expressão pós-fixa */
  pos[indPos++] = atual == '+' ? '&' : '~';
  
  return resCorreto;

} /* Primario */

Erro Potencia() {
/* Processa uma potencia da cadeia primária */
  Erro erro;

  /*
   * Analise um fator da potência, na primeira vez é o expoente, pois a base já foi
   * analisada na própria função Fator
   */
  erro = Fator();
  
  /* Verificação necessária para não continuar a análise em expressão errada */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  char atual = in[indIn];
  
  /* Tratamento de caractere inválido */
  if(!ehCaracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  /*
   * Se achou novamento o operador de potência, continua a análise de potência, que é a operação
   * de maior prioridade da expressão
   */
  if(atual == '^') {
    indIn++;
    erro = Potencia();
    
    /* Verificação necessária para não continuar a análise em expressão errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /* Atualiza a expressão pós-fixa com o operador de potência */
    pos[indPos++] = atual;
  } 

  return resCorreto;

} /* Potencia */

/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 06 
  Segundo semestre de 2014

*/

/* 
 * analisador.c: Módulo de transformação de expressões em árvores
 * binárias e seus percursos.
 */

#include "analisador.h"
#include <stdlib.h>
#include <ctype.h>
#include "balloc.h"
#include <string.h>

/* Variáveis globais a este módulo */

char *in;  /* Cadeia e índice para expressão infixa (entrada). */
int indIn;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

/* Macro para desprezar espaços em branco na cadeia de entrada. */
/* Para evitar chamadas desnecessárias a esta macro, adotou-se  */
/* seguinte conveção. A macro é invocada uma vez imediatamente  */
/* antes da primeira chamada à função Expressao e imediatamente */
/* após todo o incremento de indIn.                             */
#define DESPREZA_ESPACOS() while (in[indIn] == ' ') indIn++

typedef enum bool { false, true } bool;

/* Protótipos das funções mutuamente recursivas. */
/* O resultado é devolvido através da variável 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);
Erro Unario(ArvBin *arv);
void ignoraBrancos();

/* Função auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);
bool fimDaCadeia(char c);

/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a notação infixa em árvore binária.  Em caso de erro,
   devolve o código e a posição na cadeia de entrada onde o erro foi
   encontrado.  */
  Erro erro;

  /* Inicializa string infixa usada na conversão */
  in = infixa;
  indIn = 0;
  
  /* Inicializa árvore */
  *arv = NULL;
  
  /* Verifica se não é uma cadeia de caractere brancos */
  ignoraBrancos();
  if(!in[indIn])
    return montaErro(CADEIA_DE_BRANCOS, 0);
  
  /* Transforma a expressão infixa em uma árvore binária de expressão */
  erro = Expressao(arv);

  /* Verifica se houve algum erro na transformação */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  /*
   * Se ainda tiver dados na cadeia infixa para serem interpretados,
   * significa que falta algum operador, uma vez que o algoritmo encerra
   * quando não acha o operador esperado
   */
  if(!fimDaCadeia(in[indIn]))
    erro = montaErro(OPERADOR_ESPERADO, indIn);
  
  return erro;

}

/*************************************************************/
/*           Funções de implementação do analisador          */
/*************************************************************/

/*
 * Verifica se o caracter representa o fim de cadeia de caracteres
 */
bool fimDaCadeia(char c) {
  return c == '\0' || c == '\n';
}

/*
 * Verifica se o caracter é um caracter previsto pela implementação
 */
bool caracterValido(char c) {
  return fimDaCadeia(c) || (c >= 'a' && c <= 'z') || c == '(' || c == ')' ||
         c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/*
 * Ignora caractere em branco, uma vez que não significam erro
 * na cadeia de entrada e nem um dado de entrada
 */
void ignoraBrancos() {
  char atual = in[indIn];
  if(atual == ' ') {
    indIn++;
    ignoraBrancos();
  }
}

/*
 * Faz o tratamento da entrada ignorando caracteres em branco e
 * verificando caracteres inválidos
 */
Erro trataEntrada() {
  char atual;

  ignoraBrancos();

  atual = in[indIn];

  /* Verifica se o caracter atual é previsto pela implementação, se é válido */    
  if(!caracterValido(atual))
    return montaErro(CARACTERE_INVALIDO, indIn);
  
  return resCorreto;
}

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com código de erro e posição */
  Erro erro;
  erro.posicao = posicao;
  erro.codigoErro = codigo;
  
  return erro;
} /* montaErro */

/*
 * Cria um Nó de árvore, com filhos nulos,
 * concentra código de alocação dinâmica
 */
void criaNoArv(ArvBin *arv) {
  *arv = MALLOC(sizeof(NoArvBin));
  (*arv)->esq = NULL;
  (*arv)->dir = NULL;
}

Erro Expressao(ArvBin *arv) {
/* Processa uma expressão da cadeia de entrada.  */

  char atual;
  Erro erro;
  /* noAtual terá a árvore resultante no fim do algoritimo */
  ArvBin *noAtual = arv, filhoEsq;
  
  /* Se a expressão começar com um operador '+' ou '-', ele é unário */
  if(in[indIn] == '+' || in[indIn] == '-')
    erro = Unario(noAtual);
  else
  /*
   * Caso não tenha um operador unário no início da expressão, então 
   * o primeiro termo é tratado
   */
    erro = Termo(noAtual);
  
  /*
   * Essa verificação é necessária sempre que um método retornar erro, pois neste caso, não é necessário
   * continuar a análise (nem possível continuar) , uma vez errada a expressão a recursão/método/análise deve
   * ser interrompida e o erro retornado para tratamento no programa principal.
   */
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
  
  do {
    /*
     * Caso haja um operador de expressão ('+' ou '-') então o primeiro termo analisado é filho esquerdo
     * do operador na arvore binária de expressão resultante
     */
    filhoEsq = *noAtual;
    
    /* Tratamento de caracteres inválidos e espaços em branco */
    erro = trataEntrada();
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    atual = in[indIn];
    if(atual == '+' || atual == '-') {
      /*
       * Cria árvore equivalente à operação atual, ou seja,
       * a raiz será o operador encontrado ('+' ou '-') seu 
       * filho esquerdo será a última operação (parte da expressão ou um termo)
       * analisada e seu filho direito será o próximo termo analisado
       */
      criaNoArv(noAtual);
      (*noAtual)->info = atual;
      (*noAtual)->esq = filhoEsq;

      /* Controle do índice atual na cadeia de entrada */
      indIn++;
      
      /*
       * Para cada operador '+' e '-' existe um termo a ser avaliado,
       * sendo este o filho direito do operador atual
       */
      erro = Termo(&((*noAtual)->dir));
      
      /*
       * Verificação necessária para não continuar a análise em expressão errada
       * Também desaloca a memória necessária
       */
      if(erro.codigoErro != EXPR_VALIDA) {
        LiberaArv(*noAtual);
        return erro;
      }
    } else
      /* Se não achar mais operadores, então a expressão acabou */
      break;
  } while (true);
  
  /* No fim, noAtual terá a árvore resultante */
  *arv = *noAtual;
  
  return erro;    
} /* Expressao */


Erro Termo(ArvBin *arv) {
/* Processa um termo da cadeia de entrada.  */
  /* noAtual terá a árvore resultante no fim do algoritimo */
  ArvBin *noAtual = arv, filhoEsq;
  Erro erro;
  
  /* Todo termo começa com um fator a ser analisado */
  erro = Fator(noAtual);
  
  /* Verificação necessária para não continuar a análise em expressão errada */
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  do {
    char atual;
    
    /*
     * Se existir algum operador de termo '*' ou '/' o primeiro fator
     * analisado será filho esquerdo deste operador
     */
    filhoEsq = *noAtual;
    
    /* Tratamento de caracteres inválidos e espaços em branco */
    erro = trataEntrada();
    
    /* Verificação necessária para não continuar a análise em expressão errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    atual = in[indIn];
    if(atual == '*' || atual == '/') {
      /*
       * Cria árvore equivalente à operação atual, ou seja,
       * a raiz será o operador encontrado ('*' ou '/') seu 
       * filho esquerdo será a última operação (parte do termo ou um fator)
       * analisada e seu filho direito será o próximo fator analisado
       */
      criaNoArv(noAtual);
      (*noAtual)->info = atual;
      (*noAtual)->esq = filhoEsq;
      
      /* Controle do índice atual na cadeia de entrada */
      indIn++;
      
      /*
       * Para cada operador '*' e '/' existe um fator a ser avaliado,
       * sendo este o filho direito do operador atual
       */
      erro = Fator(&((*noAtual)->dir));
      
      /*
       * Verificação necessária para não continuar a análise em expressão errada
       * Também desaloca a memória necessária
       */
      if(erro.codigoErro != EXPR_VALIDA) {
          LiberaArv(*noAtual);
          return erro;
      }
    } else
      /* Se não achar mais operadores, então o termo acabou */
      break;
  } while (true);
  
  /* No fim, noAtual terá a árvore resultante */
  *arv = *noAtual;
  
  return erro;
} /* Termo */


Erro Fator(ArvBin *arv) {
/* Processa um fator da cadeia de entrada.  */
  char atual;
  Erro erro;

  /* Um fator começa com um primário */
  erro = Primario(arv);
  
  /* Verificação necessária para não continuar a análise em expressão errada */
  if(erro.codigoErro != EXPR_VALIDA)
      return erro;
  
  /* Tratamento de caracteres inválidos e espaços em branco */
  erro = trataEntrada();
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;
                
  atual = in[indIn];
  /* Um fator é uma sequência de potências */
  if(atual == '^') {
    /*
     * A árvore resultante terá como raiz o operador de potencia '^',
     * seu filho esquerdo será o primário lido nessa chamada e seu
     * filho esquerdo será composta pelo fator analisado posteriormente
     */
    ArvBin aux = *arv;
    criaNoArv(arv);
    (*arv)->esq = aux;
    (*arv)->info = atual;
    
    /* Controle do índice atual na cadeia de entrada */
    indIn++;
    
    /*
     * Para cada operador '^' existe um fator a ser avaliado,
     * sendo este o filho direito do operador atual
     */
    erro = Fator(&((*arv)->dir));
    
    /* Verificação necessária para não continuar a análise em expressão errada */
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
  }
  
  return erro;  
} /* Fator */


Erro Primario(ArvBin *arv) {
/* Processa um  primário da cadeia de entrada.  */
  char atual;
  Erro erro = resCorreto;
  
  erro = trataEntrada();
  if(erro.codigoErro != EXPR_VALIDA)
    return erro;

  atual = in[indIn];
  if(atual >= 'a' && atual <= 'z') {
    indIn++;
    criaNoArv(arv);
    (*arv)->info = atual;
  } else if(atual == '(') {
    indIn++;
    erro = Expressao(arv);
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
    
    atual = in[indIn];
    if(atual == ')')
      indIn++;
    else
      return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
  } else
    return montaErro(OPERANDO_ESPERADO, indIn);
  
  return erro;
} /* Primario */

Erro Unario(ArvBin *arv) {
 char atual = in[indIn];
 Erro erro = resCorreto;
 criaNoArv(arv);

 /* Os únicos operadores unários existentes são '+' e '-' */
 if (atual == '+') {
    int anterior = indIn++; /* controle para ver se há realmente um operando
                               para esse operador */

    /*
     * Na árvore de expressão a raíz será o operador unário e seu filho
     * direito será o termo correspondente
     */
    (*arv)->info = '&';
    erro = Termo(&((*arv)->dir));
    
    /* Verificação necessária para não continuar a análise em expressão errada */
    if(erro.codigoErro != EXPR_VALIDA)
        return erro;
    
    /* Verifica se há realmente um operando para esse operador */
    if(anterior == indIn)
      return montaErro(OPERANDO_ESPERADO, indIn);
    
  } else if (atual == '-') {
    int anterior = indIn++; /* controle para ver se há realmente um operando
                               para esse operador */
                               
    /*
     * Na árvore de expressão a raíz será o operador unário e seu filho
     * direito será o termo correspondente
     */                            
    (*arv)->info = '~';
    erro = Termo(&((*arv)->dir));
    
    /* Verificação necessária para não continuar a análise em expressão errada */
    if(erro.codigoErro != EXPR_VALIDA)
      return erro;
    
    /* Verifica se há realmente um operando para esse operador */
    if(anterior == indIn)
      return montaErro(OPERANDO_ESPERADO, indIn);
    
  }
  
  return erro;
} /* Unario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representação pré-fixa a partir da árvore. */
 
  if(arv != NULL) {
    /*
     * Como o resultado deve estar na cadeia pre,
     * o dado analisado atualmente é o primeiro da cadeia,
     * depois ela é usada para armazenar o percurso na subárvore esquerda
     * e posteriormente é concatenada com o percurso da subárvore direito
     */
    char preDir[TAM_MAX_EXPR + 1];
    *pre = arv->info;
    ArvPre(arv->esq, pre + 1);
    ArvPre(arv->dir, preDir);
    strcat(pre, preDir);
  } else
    /* Por último deve ser informado o fim da cadeia */
    *pre = '\0';

}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representação pós-fixa a partir da árvore. */  

  if(arv != NULL) {
    /*
     * Como o resultado deve estar na cadeia pos,
     * primeiro ela é usada para armazenar o percurso na subárvore esquerda
     * depois ela é concatenada com o percurso da subárvore direita
     * e por ultimo, o dado atualmente lido é concatenado a cadeia
     */
    char posDir[TAM_MAX_EXPR + 1], atual[2];
    atual[0] = arv->info;
    atual[1] = '\0'; /* Garante que a string final tenha o delimitador '\0' */
    ArvPos(arv->esq, pos);
    ArvPos(arv->dir, posDir);
    strcat(pos, posDir);
    strcat(pos, atual);
  } else
    /* Por último deve ser informado o fim da cadeia */
    *pos = '\0';

}


void LiberaArv(ArvBin arv) {
/* Libera o espaço ocupado pela árvore. */
  /*
   * Para liberar o espaço alocado da árvore devemos
   * desalocar a raiz por ultimo (para não perder a referencia
   * para seus filhos, para isso, usamos o percurso pos-ordem
   */
  if(arv != NULL) {
    LiberaArv(arv->esq);
    LiberaArv(arv->dir);
    FREE(arv);
  }
}


/*
  Autor:         Sabrina Beck Angelini
  RA:            157240
  Disciplina:    MC202
  Turma:         E
  
  Tarefa 11
  Segundo semestre de 2014

*/

#include <stdio.h>
#include "base.h"

/* DECLARA��ES DE TIPOS */
/* -------------------- */

typedef struct RegLista *Lista;
typedef struct RegLista {
  Aluno aluno;
  Lista prox;
} RegLista;

typedef struct RegBase *ImplBase;
typedef struct RegBase {
  int numregs;
  Lista tabela[MaxHash];
} RegBase;

/* FUN��O DE ESPALHAMENTO */
/* ---------------------- */

int Espalha(int k) {
  return (k % MaxHash);
} /* Espalha */

/* FUN��ES AUXILIARES */
/* ------------------ */

/*
 * Insere um aluno '*a' na *lista com ordem crescente de ra
 */
Boolean InsereLista(Lista *lista, Aluno *a) {
  Lista *atual = lista;
  Lista novo;
  
  /* 
   * Encontra a posi��o de inser��o, ou seja, atual ser� o apontador
   * para a posi��o em que deve estar o novo aluno, logo avan�a-se com
   * o atual at� encontrar lista vazia ou um ra maior ou igual ao que
   * est� sendo inserido
   */
  while(*atual != NULL && (*atual)->aluno.ra < a->ra)
    atual = &((*atual)->prox);
  
  /*
   * Se o ra a ser inserido for encontrado, ent�o n�o h� inser��o
   */
  if(*atual != NULL && (*atual)->aluno.ra == a->ra)
    return false;
  
  /*
   * Aloca-se a mem�rio do n� do novo aluno e o insere na posi��o correta
   */
  novo = MALLOC(sizeof(RegLista));
  novo->aluno = *a;
  novo->prox = *atual;
  *atual = novo;
  
  return true;
}

/*
 * Remove o aluno que possui 'ra' da lista
 */
Boolean RemoveLista(Lista *lista, int ra) {
  Lista *atual = lista;
  Lista removido;
  
  /*
   * Procura o aluno a ser removido, considerando que a lista est� ordenada,
   * deve-se procurar pelo primeiro aluno cujo ra � maior ou igual ao
   * desejado
   */
  while(*atual != NULL && (*atual)->aluno.ra < ra)
    atual = &((*atual)->prox);
  
  /* Se o ra n�o est� na lista, n�o h� remo��o */
  if(*atual == NULL || (*atual)->aluno.ra != ra)
    return false;

  /*
   * Remove o aluno da lista, liberando a mem�ria necess�ria
   */
  removido = *atual;
  *atual = removido->prox;
  FREE(removido->aluno.nome);
  FREE(removido);
  return true;
}

/*
 * Procura o aluno de 'ra' na lista, armazena o aluno encontrado em 'a' e
 * retorna 'true' se achou, caso contr�rio retorna 'false' 
 */
Boolean ConsultaLista(Lista lista, int ra, Aluno *a) {
  Lista atual = lista;
  
  /*
   * Procura o ra na lista, ou seja, percorre a lista at� achar um ra maior
   * ou igual ao desejado uma vez que a lista est� ordenada
   */
  while(atual != NULL && atual->aluno.ra < ra)
    atual = atual->prox;
    
  /*
   * Se o aluno encontrado n�o possui o ra desejado, ele n�o est� na base
   */
  if(atual == NULL || atual->aluno.ra != ra)
    return false;

  *a = atual->aluno;
  return true;
}

/*
 * Imprime os dados da lista na ordem, cada aluno em uma linha indicado
 * pelo seu �ndice na tabela de hash
 */
void ImprimeLista(int indice, Lista lista) {
  Lista atual = lista;
  /*
   * Percorre a lista at� achar um ponteiro nulo == fim da lista
   */
  while(atual != NULL) {
    /* Imprime o aluno atual */
    printf("(%3d) %06d %s\n", indice, atual->aluno.ra, atual->aluno.nome);
    /* Avan�a com o ponteiro */
    atual = atual->prox;
  }
}

/*
 * Libera a mem�ria ocupada pela lista e pelos nomes dos alunos nela armazenados
 */
void LiberaLista(Lista lista) {
  Lista atual = lista;
  /* Percorre a lista at� achar um ponteiro nulo == fim da lista */
  while(atual != NULL) {
    Lista aux = atual->prox;
    /* Libera a mem�ria */
    FREE(atual->aluno.nome);
    FREE(atual);
    atual = aux;
  }
}

/* FUN��ES DA INTERFACE */
/* -------------------- */

/*
 * Devolve apontador para uma base vazia com tabela inicializada
 */
Base CriaBase() {
  ImplBase base = MALLOC(sizeof(RegBase));
  int i;
  
  /* A base come�a com nenhum registro */
  base->numregs = 0;
  
  /* Coloca listas vazias em todas as posi��es da tabela */
  for(i = 0; i < MaxHash; i++)
    base->tabela[i] = NULL;
  return base;
}
/*

 * Insere o registro 'a' na base 'p' se n�o existe aluno
 * com o mesmo valor de 'ra', e devolve 'true';  caso
 * contr�rio devolve 'false'
 */
Boolean InsereBase(Base p, Aluno *a) {
  ImplBase base = p;
  /* Calcula posi��o do aluno na tabela pela fun��o de espalhamento */
  int hashcode = Espalha(a->ra);
  /* Insere o aluno na lista presente na posi��o encontrada da tabela */
  if(InsereLista(&(base->tabela[hashcode]), a)) {
    (base->numregs)++;
    return true;
  }
  return false;
}
   
/*
 * Remove da base 'p' o aluno com 'ra' dado; devolve 'true'
 * se ele existiu e 'false' caso contr�rio.
 */
Boolean RemoveBase(Base p, int ra) {
  ImplBase base = p;
  /* Calcula posi��o do aluno na tabela pela fun��o de espalhamento */
  int hashcode = Espalha(ra);
  /* Remove o aluno na lista presente na posi��o encontrada da tabela */
  if(RemoveLista(&(base->tabela[hashcode]), ra)) {
    (base->numregs)--;
    return true;
  }
  
  return false;
}

/*
 * Devolve 'true' se existe um registro com 'ra' dado na
 * base 'p';  caso contr�rio devolve 'false'.  'a' conter� 
 * os dados do aluno, se encontrado.
 */
Boolean ConsultaBase(Base p, int ra, Aluno *a) {
  ImplBase base = p;
  /* Calcula posi��o do aluno na tabela pela fun��o de espalhamento */
  int hashcode = Espalha(ra);
  /*
   * Procura o aluno desejado na lista presente na posi��o
   * encontrada da tabela
   */
  return ConsultaLista(base->tabela[hashcode], ra, a);
}
   
/*
 * Devolve o n�mero de registros (alunos) na base 'p'.
 */
int NumeroRegsBase(Base p) {
  ImplBase base = p;
  return base->numregs;
}

/*
 * Imprime, os registros contidos na base 'p', um por linha.  A ordem
 * de impress�o segue a ordem das entradas da tabela, e para cada
 * entrada, a ordem da lista ligada.  Cada linha come�a com o �ndice
 * correspondente na tabela de espalhamento. Deve ser usado o formato
 * "(%3d) %06d %s\n".
 */
void ImprimeBase(Base p) {
  ImplBase base = p;
  int i;
  /*
   * Para cada �ndice da tabela, imprime a lista correspondente
   */
  for(i = 0; i < MaxHash; i++)
    ImprimeLista(i, base->tabela[i]);
}
   
/*
 * Libera toda a mem�ria utilizada pela base 'p', bem como
 * todas as cadeias que guardam os nomes.
 */
void LiberaBase(Base p) {
  ImplBase base = p;
  int i;
  /*
   * Libera a mem�ria das listas de cada posi��o da tabela
   */
  for(i = 0; i < MaxHash; i++)
    LiberaLista(base->tabela[i]);
  /* Libera a mem�ria da tabela */
  FREE(base);
}


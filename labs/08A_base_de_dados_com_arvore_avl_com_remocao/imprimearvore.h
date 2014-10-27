
/* Last update: "imprimearvore.h: 2012-09-06 (Thu)  11:32:02 BRT (tk)" */

/*! @file imprimearvore.h
 *
 * @brief Função de impressão de árvores binárias.
 *
 * Uso livre para qualquer aplicação
 *
 * <p>Autor: Tomasz Kowaltowski</p>
 *
 * <b>Histórico</b>
 * <p>2011-09-30 versão inicial</p>
 * <p>2012-09-06 revisão</p>
 */

#ifndef __IMPRIMEARVORE_DEFINED
#define __IMPRIMEARVORE_DEFINED


typedef void * subarvfunc(void *,int);
typedef char * infofunc(void *,int);
typedef void libfunc(void *);


void ImprimeArvore(void *arv, subarvfunc *esq, subarvfunc *dir, infofunc *info, libfunc *libera, int desl, char *vazia);
/* Imprime uma árvore binária num formato legível. 
   
   Argumentos:
   
     arv:    apontador para a raiz da árvore
     esq:    função que devolve apontador para o filho esquerdo
     dir:    função que devolve apontador para o filho direito
     info:   função que processa a informação do nó da árvore e devolve
             a cadeia a ser impressa
     libera: função que libera o bloco de memória devolvido por 'info'
             (pode ser NULL se desnecessário)
     desl:   deslocamento entre os níveis
     vazia:  cadeia a ser impressa se a árvore é vazia

     Em todas as funções que são argumentos, o argumento inteiro
     corresponde ao nível do nó; na chamada inicial este nível terá
     valor 1.

 */


#endif

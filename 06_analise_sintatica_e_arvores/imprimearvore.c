
/*  Last update: "imprimearvore.c: 2012-09-06 (Thu)  11:30:22 BRT (tk)"  */

/*! @file imprimearvore.c
 *
 * @brief Impressão de árvores binárias
 *
 * <b>Histórico:</b> V. imprimearvore.h
 */

#include <stdio.h>
#include "imprimearvore.h" 

void ImprimeArvoreAux(void *arv, subarvfunc *esq, subarvfunc *dir, infofunc *info, libfunc *libera, int desl, int nivel, char apont) {
  /* Função auxiliar para 'ImprimeArvore': recebe os mesmos argumentos
     além do valor de nível do nó na árvore e o caractere a
     representar o apontador (normalmente '\' ou '/').
  */
  
  void *p = arv;
  
  if (p!=NULL) {
    
    char *inf;
    
    ImprimeArvoreAux(dir(p,nivel+1), esq, dir, info, libera, desl, nivel+1, '/');
    printf("%*s",(nivel-1)*desl," ");
    if (nivel>1)
      printf("  %c",apont);
    inf = info(p,nivel);
    printf("%-s\n",inf);
    if (libera!=NULL)
      libera(inf);
    ImprimeArvoreAux(esq(p,nivel+1), esq, dir, info, libera, desl, nivel+1, '\\');
  }
  
}  /* ImprimeArvoreAux */

void ImprimeArvore(void *arv, subarvfunc *esq, subarvfunc *dir, infofunc *info, libfunc *libera, int desl, char *vazia) {
/* Imprime uma árvore binária num formato legível. 
   
   Argumentos:
   
     arv:    apontador para a raiz da árvore
     esq:    função que devolve apontador para o filho esquerdo
     dir:    função que devolve apontador para o filho direito
     info:   função que processa a informação do nó da árvore e devolve
             a cadeia a ser impressa
     libera: função que libera o bloco de memória devolvido por 'info'
             (pode ser NULL se desnecessário)

     Em todas as funções que são argumentos, o argumento inteiro
     corresponde ao nível do nó; na chamada inicial este nível terá
     valor 1.

 */
  
  if (arv==NULL) 
    printf("%s",vazia);
  else
    ImprimeArvoreAux(arv, esq, dir, info, libera, desl, 1,' ');

} /* ImprimeArvore */

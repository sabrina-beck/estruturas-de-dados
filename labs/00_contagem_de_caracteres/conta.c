/* Programa: conta.c                                   */
/* Autor: Sabrina Beck Angelini           RA157240     */
/* Disciplina: MC102                      Turma E      */
/* Data: 06/set/2014                                   */

#include <stdio.h>

int main() {

  int cars=0, linhas=0;
  int c;
  
  while ((c=getchar())!=EOF)
    if (c=='\n')
      linhas++;
    else
      cars++;

  printf("Caracteres: %d\n",cars);
  printf("Linhas:     %d\n",linhas);
  
  return 0;
  
}

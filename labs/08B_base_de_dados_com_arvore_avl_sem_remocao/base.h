/* 
 *  Arquivo base.h: definição de tipos e cabeçalhos das funções de
 *  manipulação da base.
 *
 * A base de dados é sempre passada por referência a fim de
 * uniformizar o tratamento; em alguns casos isto não seria
 * necessário.
 */

typedef enum {false, true} Boolean;

typedef char * String;

typedef void * Base;  /* tipo efetivo escondido */


typedef struct {
  int ra;
  String nome;
  } Aluno;
  
/* Tipo da função a ser passado para a função de percurso: o argumento
   aponta para o campo de informação (aluno). */
typedef void TipoVisita(Aluno *aluno);


Base CriaBase();
/* Devolve apontador para uma base vazia */

Base SubEsq(Base *p);
/* Devolve a subárvore esquerda da base 'p' se não for vazia; caso
   contrário devolve NULL. */

Base SubDir(Base *p);
/* Devolve a subárvore direita da base 'p' se não for vazia; caso
   contrário devolve NULL. */

int FatorBal(Base *p);
/* Devolve o fator de balanceamento da raiz da base: altura da
   subárvore direita menos a altura da subárvore esquerda; devolve
   zero se a árvore é vazia. */

Boolean InsereBase(Base *p, Aluno a);
/* Insere o registro 'a' na base 'p' se não existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a);
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
   
int AlturaBase(Base *p);
/* Devolve a altura da base 'p'. */

int NumeroNosBase(Base *p);
/* Devolve o número de nós da base 'p'. */

void PercorreBase(Base *p, TipoVisita Visita);
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */

void LiberaBase(Base *p);
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

Boolean RemoveBase(Base *p, int ra);
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. 

   A IMPLEMENTAÇÃO DESTA FUNÇÃO É OPCIONAL. 

*/

void ImprimeBase(Base *p);
  /* Imprime a base sob a forma de uma árvore 'deitada'. */

/* 
 *  Arquivo base.h: definição de tipos e cabeçalhos das funções de
 *  manipulação da base.
 */

/* #include "balloc.h" */

typedef char * String;
typedef enum {false, true} Boolean;
typedef void * Base;  /* tipo efetivo escondido */

typedef struct {
  int ra;
  String nome;
  } Aluno;
  
Base CriaBase();
/* Devolve apontador para uma base vazia */

Boolean InsereBase(Base *p, Aluno a);
/* Insere o registro 'a' na base 'p' se não existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a);
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */

Boolean RemoveBase(Base *p, int ra);
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. */
   
int AlturaBase(Base *p); 
/* Devolve a altura da base 'p'. */

int NumeroNosBase(Base *p);
/* Devolve o número de nós da base 'p'. */

void PercorreBase(Base *p, void (*Visita)(Aluno*));
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */

void LiberaBase(Base *p);
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

/*    Last update: "trie.h: 2014-11-05 (Wed)  17:06:50 BRST (tk)" */

/* Arquivo trie.h:

   Define a implementação de árvores digitais (ADs) através de um tipo
   abstrato de dados usando apontadores "void *".
   
   Supõe que as cadeias inseridas consistem apenas das letras
   minúsculas 'a' a 'z', sem símbolos diacríticos.
   
*/

/* Limites */
/* ------- */

#define TAM_ALFABETO 26
#define TAM_MAX_CADEIA 50

/* Tipos */
/* ----- */

typedef enum {false, true} Boolean;
typedef void * Trie;
typedef void funcVisita(char *s);  /* usada pela função percorreAD */


/* Funções */
/*-------- */

Trie CriaAD();
/* Devolve uma AD vazia. Supõe uma implementação que não modifica mais
   o apontador para a raiz da AD. */


Boolean consultaAD(Trie t, char *s);
/* Verifica se a cadeia de caracteres 's' foi inserida na AD 't'. */


Boolean insereAD(Trie t, char *s);
/* Insere na AD 't' a cadeia de caracteres 's'.  Devolve o valor
   verdadeiro se houve inserção; devolve o valor falso se a cadeia já
   ocorre em 't'.  A cadeia 's' pode ser vazia (de comprimento zero).
*/


Boolean removeAD(Trie t, char *s);
/* Remove da AD 't' a cadeia de caracteres 's'. Devolve o valor
   verdadeiro se houve remoção; devolve o valor falso se a cadeia não
   ocorre em '*t'.
*/


int numCadeiasAD(Trie t);
/* Devolve o número de cadeias contidas na AD. */


void percorreAD(Trie t, funcVisita *v);
/* Visita, em ordem alfabética, as cadeias contidas na AD 't' e
   aplica, a cada cadeia, a função 'v', sob a forma "v(s)", supondo
   que 's' é um apontador para a cadeia que deve terminar com o
   caractere nulo '\0'.
*/


void liberaAD(Trie t);
/* Libera a memória dinâmica alocada na construção da AD 't'. */

/* ------------------------------------------------------------
 Funções seguintes são usadas somente para verificação;
 conceitualmente não fazem parte da implementação.
*/

   
int numNosAD(Trie t);
/* Devolve o número de nós da AD. */


int alturaAD(Trie t);
/* Devolve a altura da AD. */

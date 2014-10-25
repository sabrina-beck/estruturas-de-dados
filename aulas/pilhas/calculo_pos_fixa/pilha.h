#define TAM_MAX 171

typedef
  enum bool {
    false, true
  } bool;

typedef
  struct Pilha {
    int topo;
    int elementos[TAM_MAX];
  } Pilha;

Pilha criarPilha(); 
bool estaVazia(Pilha pilha);
void empilhar(Pilha *pilha, int info);
int desempilhar(Pilha *pilha);

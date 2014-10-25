
typedef
  enum bool {
    false, true
  } bool;

typedef
  struct No {
    char info;
    struct No *prox;
  } No, *Pilha;

bool estaVazia(Pilha topo);

void empilhar(Pilha *topo, char info);

char desempilhar(Pilha *topo);

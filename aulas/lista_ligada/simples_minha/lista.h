#include "base.h"

typedef 
  struct No {
    void* info;
    struct No *prox;
  } No, *NoLista;
  
typedef
  struct Lista {
    NoLista primeiro;
    int qtd;
  } Lista;

Lista novaLista();

Lista insereNoInicio(void* info, Lista lista);

Lista insereNoFim(void* info, Lista lista);

Lista insereEm(int pos, void* info, Lista lista);

bool remover(void* info, Lista lista);

bool removerDe(int pos, Lista lista);

void* encontrar(int pos, Lista lista);

int posicaoDe(void* info, Lista lista);

bool estaVazia(Lista lista);

int quantidadeDeElementos(Lista lista);

void liberar(Lista lista);

void imprime(Lista lista);

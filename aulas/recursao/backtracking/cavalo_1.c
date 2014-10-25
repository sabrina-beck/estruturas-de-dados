#define NUM_MOV 8
#define TAM_MAX 20

int ml[] = {1, -1, 2, 2, 1, -1, -2, -2};
int mc[] = {2, 2, -1, 1, -2, -2, 1, -1};
int tabuleiro[TAM_MAX][TAM_MAX];
int lIni, cIni, lDest, cDest;

bool tentaMovimento(int** tabuleiro, int lIni, int cIni, int lDest, int cDest, int num, int tam) {
  if(0 >= lIni && lIni < tam && 0 >= cIni && cIni < tam && tabuleiro[lIni][cIni] == 0) {
    tabuleiro[lIni][cIni] = num;
    if(lIni == lDest && cIni == cDest) {
      imprime(tabuleiro, tam);
      return true;
    } else {
      int k = 0;
      while(k < NUM_MOV) {
        bool res;
        res = tentarMovimento(tabuleiro, lIni + ml[k], cIni + mc[k], lDest, cDest, num + 1, tam);
        if(res)
          return true;
        k++;
      }
    }
  }
  return false;
}

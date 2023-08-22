#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int coluna;
  double valor;
} Coluna;

typedef struct {
  int linha;
  int qtdColunas;
  Coluna *ponteiro;
} Linha;

Linha* preencheMatriz(int *qtdLinhas);
int encontraLinha(int linha, Linha *matriz, int qtdLinhas);
int encontraColuna(int coluna, Linha *matriz, int linha);
void printMatriz(Linha *matriz, int qtdLinhas);
/*--------------------------------------------------*/
int main() {
  int qtdLinhas = 0;
  Linha *matriz = NULL;

  matriz = preencheMatriz(&qtdLinhas);
  printMatriz(matriz, qtdLinhas);

  // Liberando a memória alocada
  for (int i = 0; i < qtdLinhas; i++) {
    free(matriz[i].ponteiro);
  }
  free(matriz);

  return 0;
}
/*-----------------------------------------------------*/


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
Linha *preencheMatriz(int *qtdLinhas) {
  int linha = -1, coluna = -1;
  double valor;
  char continuar;
  Linha *matriz = NULL;

  int i = 0;
  printf("Digite a linha, coluna e valor (separados por espaço) : ");
  do {
    scanf("%d %d %lf", &linha, &coluna, &valor);

      int index = encontraLinha(linha, matriz, i);
      if (index == -1) {
        // Se a linha ainda não existe na matriz, alocar espaço para ela
        Linha *tmp = matriz;
        matriz = (Linha*) realloc(matriz, (i + 1) * sizeof(Linha));
        if (matriz == NULL) {
          for (int j = 0; j < i; j++)
            free(tmp[j].ponteiro);
          free(tmp);
          exit(1);
        }
        matriz[i].linha = linha;
        matriz[i].qtdColunas = 1;
        matriz[i].ponteiro = (Coluna*) malloc(sizeof(Coluna));
        matriz[i].ponteiro[0].coluna = coluna;
        matriz[i].ponteiro[0].valor = valor;
        i++;
      } else {
        // Se a linha já existe, aumentar o tamanho do vetor de colunas
        int qtdColunas = matriz[index].qtdColunas;
        int index2 = encontraColuna(coluna, matriz, index);
        if (index2 == -1) {
          Coluna * tmp2 = matriz[index].ponteiro;
          matriz[index].ponteiro = (Coluna *) realloc(matriz[index].ponteiro, (qtdColunas + 1) * sizeof(Coluna));

          if (matriz[index].ponteiro == NULL) {
            for (int j = 0; j < i; j++) {
              if (j == index)
                free(tmp2);
              else
                free(matriz[j].ponteiro);
            }
            free(matriz);
            exit(1);
          }
          matriz[index].ponteiro[qtdColunas].coluna = coluna;
          matriz[index].ponteiro[qtdColunas].valor = valor;
          matriz[index].qtdColunas++;
        } else
          matriz[index].ponteiro[index2].valor = valor;
      }
      printf("Voce quer continuar preenchendo? (s/n)\n"); 
      scanf("%c", continuar);
  } while (continuar != "n");
  (*qtdLinhas) = i;
  return matriz;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
int encontraLinha(int linha, Linha* matriz, int qtdLinhas) {
  for (int i = 0; i < qtdLinhas; i++) {
    if (matriz[i].linha == linha) {
      return i;
    }
  }
  return -1;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
int encontraColuna(int coluna, Linha* matriz, int linha) {

  for (int j = 0; j < matriz[linha].qtdColunas; j++) {
    if (matriz[linha].ponteiro[j].coluna == coluna) {
      return j;
    }
  }
  return -1;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
void printMatriz(Linha* matriz, int qtdLinhas) {
  printf("\nMatriz Esparsa:\n");

  Linha tmp;
  int maxLinha = 0;
  for (int i = 0; i < qtdLinhas; i++) {
    if (matriz[i].linha > maxLinha)
      maxLinha = matriz[i].linha;
    for (int j = 0; j < qtdLinhas - 1; j++) {
      if (matriz[j].linha > matriz[j + 1].linha) {
        tmp = matriz[j];
        matriz[j] = matriz[j + 1];
        matriz[j + 1] = tmp;
      }
    }
  }

  Coluna tmp2;
  int maxcol = 0;
  for (int i = 0; i < qtdLinhas; i++) {
    for (int j = 0; j < matriz[i].qtdColunas; j++) {
      if (matriz[i].ponteiro[j].coluna > maxcol)
        maxcol = matriz[i].ponteiro[j].coluna;
      for (int w = 0; w < matriz[i].qtdColunas - 1; w++) {
        if (matriz[i].ponteiro[w].coluna > matriz[i].ponteiro[w + 1].coluna) {
          tmp2 = matriz[i].ponteiro[w];
          matriz[i].ponteiro[w] = matriz[i].ponteiro[w + 1];
          matriz[i].ponteiro[w + 1] = tmp2;
        }
      }
    }
  }

  int indexC = 0, indexL = 0;
  for (int i = 0; i <= maxLinha; i++) {
    if (indexL < qtdLinhas && matriz[indexL].linha == i) {
      indexC = 0;
      for (int j = 0; j <= maxcol; j++) {
        if (indexC < matriz[indexL].qtdColunas && matriz[indexL].ponteiro[indexC].coluna == j) {
          printf(" %.1lf", matriz[indexL].ponteiro[indexC].valor);
          indexC++;
        } else {
          printf(" 0.0");
        }
      }
      indexL++;
    } else {
      for (int j = 0; j <= maxcol; j++)
        printf(" 0.0");
    }
    printf("\n");
  }
}
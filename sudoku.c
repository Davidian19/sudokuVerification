#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define max_linhas 1000
#define max_colunas 1000
int matriz[max_linhas][max_colunas];
int nIguais = 0;
int nIguaisSubgrade = 0;
int nMaiorMenor = 0;

struct Sudoku {
  int tamanhoLinha;
  int tamanhoColuna;
};

struct Sudoku tamanhoSudoku;
struct Sudoku tamanhoSubgrade;

void *checarLinhas(void *lines) {
  int linhas = *((int*) lines);
  int i, j;

  for (i = 0; i < tamanhoSudoku.tamanhoLinha; i++) {
    for (j = i+1; j < tamanhoSudoku.tamanhoLinha; j++) {
      if (matriz[linhas][i] == matriz[linhas][j]) {
        nIguais++;
        pthread_exit(NULL);
        break;
      }
    }
  }
  pthread_exit(NULL);
}

void *checarColunas(void *coluns) {
  int colunas = *((int*) coluns);
  int i, j;

  for (i = 0; i < tamanhoSudoku.tamanhoColuna; i++) {
    for (j = i+1; j < tamanhoSudoku.tamanhoColuna; j++) {
      if (matriz[i][colunas] == matriz[j][colunas]) {
        nIguais++;
        pthread_exit(NULL);
        break;
      }
    }
  }
  pthread_exit(NULL);
}


void *checarLinhaSubgrade(void *lines) {
  int linhas = *((int*) lines);
  int i, j;

  for (i = 0; i < tamanhoSubgrade.tamanhoLinha - 1; i++) {
    for (j = i+1; j < tamanhoSubgrade.tamanhoLinha - 1; j++) {
      if (matriz[linhas][i] == matriz[linhas+1][j] ||
        matriz[linhas][i] == matriz[linhas-1][j] ||
        matriz[linhas][i] == matriz[linhas-1][j-2] ||
        matriz[linhas][i] == matriz[linhas+1][j-2]) {
        nIguaisSubgrade++;
        pthread_exit(NULL);
        break;
      }
    }
  }
  pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
  FILE *arquivo;
  char gradeN1[10], subgradeN1[10];
  char *gradeColuna, *subgradeColuna;
  pthread_t threadsLinhas[4], threadsColunas[4], threadsSubLinhas[4];

  char sudoku[1000];

  int nLinhas = 0, nColunas = 0, ret;

  arquivo = fopen(argv[1], "r");

  if(arquivo == NULL) {
    printf("Error to read file\n");
    return 1;
  }
  if(argc != 2) {
    printf("Invalid number of parameters\n");
    return 1;
  }
 

  int size = fread(sudoku, 1, sizeof(sudoku), arquivo);

  if (size == 0 && feof(arquivo)) {
    printf("File out of format\n");
    return 1;
  }
  
  rewind(arquivo);

  //separando as linhas
  fgets(gradeN1, 80, arquivo);
  
  char *isTemX =  strchr(gradeN1, 'x');
  if(isTemX == NULL){
    printf("File out of format\n");
    return 1;
  }

  char *gradeLinha = strtok(gradeN1, "x");
  if(gradeLinha == NULL){
    printf("File out of format\n");
    return 1;
  }
  gradeColuna = strtok(NULL, "\n");
  if(gradeColuna == NULL){
    printf("File out of format\n");
    return 1;
  }


  int n1 =  atoi(gradeLinha);
  int n2 =  atoi(gradeColuna);
  tamanhoSudoku.tamanhoLinha = n1;
  tamanhoSudoku.tamanhoColuna = n2;

  fgets(subgradeN1, 80, arquivo);

  char *subgradeLinha = strtok(subgradeN1, "x");
  if(subgradeLinha == NULL){
    printf("File out of format\n");
    return 1;
  }

  subgradeColuna = strtok(NULL, "\n");
  if(subgradeColuna == NULL){
    printf("File out of format\n");
    return 1;
  }


  int sn1 = atoi(subgradeLinha);
  int sn2 = atoi(subgradeColuna);
  tamanhoSubgrade.tamanhoLinha = sn1;
  tamanhoSubgrade.tamanhoColuna = sn2;

  while (!feof(arquivo) && nLinhas < max_linhas) { 
    nColunas = 0;
    for (;nColunas<n2; nColunas++) { 
      fscanf(arquivo, "%d", &matriz[nLinhas][nColunas]);
    }
    nLinhas++;
  }
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n1; j++) {
      if (matriz[i][j] > n1 ||
        matriz[i][j] <= 0){
        printf("File out of format\n");
        return 1;
      }
    }
  }
  //-------------Threads------------------//
  // Linhas - criar threads
  for (int i = 0; i < 4; i++) {
    int *arg = malloc(sizeof(int));
    *arg = i;
    ret = pthread_create(&threadsLinhas[i], NULL, checarLinhas, arg);
    if (ret != 0) {
      printf("Error creating thread.\n");
      return 1;
    }
  }

  // coluna - cria as threads
  for (int i = 0; i < 4; i++) {
    int *arg = malloc(sizeof(int));
    *arg = i;
    ret = pthread_create(&threadsColunas[i], NULL, checarColunas, arg);
    if (ret != 0) {
      printf("Error creating thread.\n");
      return 1;
    }
  }


  //---subgrade------//
  // Linhas - criar threads
  for (int i = 0; i < 4; i++) {
    int *arg = malloc(sizeof(int));
    *arg = i;
    ret = pthread_create(&threadsSubLinhas[i], NULL, checarLinhaSubgrade, arg);
    if (ret != 0) {
      printf("Error creating thread.\n");
      return 1;
    }
  }
  //-----------Finalização--------------
  
  // coluna - esperar finalizar finalizar
  for (int i = 0; i < 4; i++) {
    pthread_join(threadsColunas[i], NULL);
  }
  
  // Linhas - esperar finalizar 
  for (int i = 0; i < 4; i++) {
    pthread_join(threadsLinhas[i], NULL);
  }
  // Linhas da subgrade - esperar finalizar 
  for (int i = 0; i < 4; i++) {
    pthread_join(threadsSubLinhas[i], NULL);
  }

  //--------------------------------------------------//
  
  if((n1*n2) != (nLinhas*nColunas) || n1 < 9 || n2< 9){
    printf("File out of format\n");
    return 1;
  }
  if(strcmp(gradeLinha, gradeColuna) != 0){
    printf("File out of format\n");
    return 1;
  }
  if((sn1*sn2) != n1){
    printf("File out of format\n");
    return 1;
  }

  FILE *result;
  result = fopen("sudoku_dipp.out", "w");
  if(result == NULL){
    printf("Error to read file\n");
    return 1;
  }

  if(nIguais > 0 || nIguaisSubgrade > 0){
    fprintf(result, "FAIL");
    return 1;
  } else{
    fprintf(result, "SUCCESS");
  }

  fclose(result);
  fclose(arquivo);
  return 0;
}
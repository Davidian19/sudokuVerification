<b><h1>Documentação do Verificador de Sudoku</h1><br><br>
Este programa é um verificador de Sudoku desenvolvido em C que utiliza arquivos de texto para verificar se um tabuleiro de Sudoku está resolvido corretamente ou não. Ele utiliza a biblioteca `pthread.h` para criar threads que verificam as linhas, colunas e subgrades em paralelo.<br><br>
  <h3>Estruturas de Dados<br><br></h3>
O programa utiliza duas estruturas principais:<br>
`struct Sudoku` : armazena os tamanhos das linhas e colunas do tabuleiro.<br>
`int matriz[max_linhas][max_colunas]` : matriz que armazena os números do tabuleiro.<br><br>
<h3>Funções<br><br></h3>
O programa possui as seguintes funções:<br>
void *checarLinhas(void *lines) : função executada pelas threads para verificar se há números iguais na mesma linha.<br>
void *checarColunas(void *coluns) : função executada pelas threads para verificar se há números iguais na mesma coluna.<br>
void *checarLinhaSubgrade(void *lines) : função executada pelas threads para verificar se há números iguais na mesma subgrade.<br><br>
<h3>Fluxo do Programa<br><br></h3>
O programa lê o arquivo de entrada e extrai as dimensões do tabuleiro e das subgrades.<br>
A matriz é preenchida com os números do tabuleiro lido do arquivo.<br>
São criadas threads para verificar as linhas, colunas e subgrades em paralelo.<br>
O programa aguarda a finalização das threads.<br>
Caso haja algum número repetido nas linhas, colunas ou subgrades, o programa imprime "FAIL" no arquivo de saída "sudoku_dipp.out". Caso contrário, imprime "SUCCESS".<br><br>
<h3>Observações Importantes<br><br></h3>
O programa foi projetado para trabalhar com tabuleiros de Sudoku de tamanho 9x9 e subgrades 3x3.<br>
O arquivo de entrada deve estar no formato correto, caso contrário, o programa retornará um erro e a mensagem "File out of format".<br>
O arquivo de entrada deve conter primeiro as dimensões do tabuleiro e das subgrades (ex: "9x9\n3x3\n"), seguido pelos números do tabuleiro separados por espaços e quebras de linha.<br>
O programa utiliza quatro threads para verificar as linhas, colunas e subgrades. Isso pode ser ajustado, se necessário, mas o número de threads deve ser igual para todas as verificações.<br><br>
<h3>Exemplo de Uso<br><br></h3>
Para compilar o programa, utilize o comando:<br>
```
make
```
Para executar o programa, use:<br>
```
./sudoku arquivo_de_entrada.txt
```
O resultado da verificação será salvo no arquivo "sudoku_dipp.out". Se o Sudoku estiver resolvido corretamente, o arquivo conterá "SUCCESS". Se houver algum erro na resolução, o arquivo conterá "FAIL".<br>


<b><h1>Sudoku Verifier Documentation</h1><br><br>
This program is a Sudoku verifier developed in C that uses text files to check if a Sudoku board is correctly solved or not. It uses the pthread.h library to create threads that verify the rows, columns, and subgrids in parallel.<br><br>

  <h3>Data Structures<br><br></h3>
The program uses two main data structures:<br>
`struct Sudoku` : stores the sizes of the rows and columns of the board.<br>
`int matrix[max_rows][max_columns]` : matrix that stores the numbers of the board.<br><br>
<h3>Functions<br><br></h3>
The program has the following functions:<br>
void *checkRows(void *lines) : function executed by the threads to check if there are equal numbers in the same row.<br>
void *checkColumns(void *coluns) : function executed by the threads to check if there are equal numbers in the same column.<br>
void *checkSubgrid(void *lines) : function executed by the threads to check if there are equal numbers in the same subgrid.<br><br>
<h3>Program Flow<br><br></h3>
The program reads the input file and extracts the dimensions of the board and the subgrids.<br>
The matrix is filled with the numbers of the board read from the file.<br>
Threads are created to verify the rows, columns, and subgrids in parallel.<br>
The program waits for the threads to finish.<br>
If there is any repeated number in the rows, columns, or subgrids, the program prints "FAIL" to the output file "sudoku_dipp.out". Otherwise, it prints "SUCCESS".<br><br>
<h3>Important Notes<br><br></h3>
The program was designed to work with Sudoku boards of size 9x9 and subgrids of size 3x3.<br>
The input file must be in the correct format, otherwise, the program will return an error and the message "File out of format".<br>
The input file must first contain the dimensions of the board and the subgrids (e.g., "9x9\n3x3\n"), followed by the numbers of the board separated by spaces and line breaks.<br>
The program uses four threads to check the rows, columns, and subgrids. This can be adjusted if necessary, but the number of threads must be the same for all verifications.<br><br>
<h3>Usage Example<br><br></h3>
To compile the program, use the command:<br>
```
make
```
To run the program, use:<br>
```
./sudoku input_file.txt
```
The verification result will be saved in the file "sudoku_dipp.out". If the Sudoku is correctly solved, the file will contain "SUCCESS". If there is any error in the solution, the file will contain "FAIL".<br>

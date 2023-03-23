Documentação do Verificador de Sudoku
Este programa é um verificador de Sudoku desenvolvido em C que utiliza arquivos de texto para verificar se um tabuleiro de Sudoku está resolvido corretamente ou não. Ele utiliza a biblioteca `pthread.h` para criar threads que verificam as linhas, colunas e subgrades em paralelo.
Estruturas de Dados
O programa utiliza duas estruturas principais:
`struct Sudoku`: armazena os tamanhos das linhas e colunas do tabuleiro.
`int matriz[max_linhas][max_colunas]`: matriz que armazena os números do tabuleiro.
Funções
O programa possui as seguintes funções:
`void *checarLinhas(void *lines)`: função executada pelas threads para verificar se há números iguais na mesma linha.
`void *checarColunas(void *coluns)`: função executada pelas threads para verificar se há números iguais na mesma coluna.
`void *checarLinhaSubgrade(void *lines)`: função executada pelas threads para verificar se há números iguais na mesma subgrade.
Fluxo do Programa
O programa lê o arquivo de entrada e extrai as dimensões do tabuleiro e das subgrades.
A matriz é preenchida com os números do tabuleiro lido do arquivo.
São criadas threads para verificar as linhas, colunas e subgrades em paralelo.
O programa aguarda a finalização das threads.
Caso haja algum número repetido nas linhas, colunas ou subgrades, o programa imprime "FAIL" no arquivo de saída "sudoku_dipp.out". Caso contrário, imprime "SUCCESS".
Observações Importantes
O programa foi projetado para trabalhar com tabuleiros de Sudoku de tamanho 9x9 e subgrades 3x3.
O arquivo de entrada deve estar no formato correto, caso contrário, o programa retornará um erro e a mensagem "File out of format".
O arquivo de entrada deve conter primeiro as dimensões do tabuleiro e das subgrades (ex: "9x9\n3x3\n"), seguido pelos números do tabuleiro separados por espaços e quebras de linha.
O programa utiliza quatro threads para verificar as linhas, colunas e subgrades. Isso pode ser ajustado, se necessário, mas o número de threads deve ser igual para todas as verificações.
Exemplo de Uso
Para compilar o programa, utilize o comando:
```
make
```
Para executar o programa, use:
```
./sudoku arquivo_de_entrada.txt
```
O resultado da verificação será salvo no arquivo "sudoku_dipp.out". Se o Sudoku estiver resolvido corretamente, o arquivo conterá "SUCCESS". Se houver algum erro na resolução, o arquivo conterá "FAIL".



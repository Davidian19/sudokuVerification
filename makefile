all: lerArquivo

lerArquivo: sudoku.c
		gcc -o sudoku sudoku.c -lpthread

clean:
		rm -f sudoku

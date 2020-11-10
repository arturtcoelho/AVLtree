CC = gcc
CFLAGS = -Wall
LIBS = avl_tree.o tree_operators.o

all: main $(LIBS)

# compilação dos arquivos de funções auxiliares
avl_tree.o: avl_tree.h avl_tree.c
tree_operators.o: tree_operators.h tree_operators.c

# compilação e montagem do arquivo binário principal
main.o: main.c avl_tree.o avl_tree.h tree_operators.o tree_operators.h 
main: avl_tree.o avl_tree.o tree_operators.o

# limpeza dos arquivos
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o
	-rm -f ~. main
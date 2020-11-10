# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal (main)

CC = gcc
CFLAGS = -Wall
LIBS = avl_tree.o tree_operators.o

# targets de compilação
all: main
debug: main
	$(eval CFLAGS := -D_DEBUG_)

# targets de bibliotecas
avl_tree.o: avl_tree.h avl_tree.c
tree_operators.o: tree_operators.h tree_operators.c

# targets de arquivo executavel
main.o: main.c avl_tree.o avl_tree.h tree_operators.o tree_operators.h 
main: avl_tree.o avl_tree.o tree_operators.o

# targets de limpeza
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o
	-rm -f ~. main
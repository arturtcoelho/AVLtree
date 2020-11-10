# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal (main)

CC = gcc
CFLAGS = -Wall

# targets de compilação
all: main

# flag de debug
# debug: purge
debug: CFLAGS += -DDEBUG
debug: main

# targets de bibliotecas
tree_operations.o: tree_operations.h tree_operations.c
	$(CC) $(CFLAGS) -c tree_operations.c
avl_tree.o: avl_tree.h avl_tree.c tree_operations.o
	$(CC) $(CFLAGS) -c avl_tree.c 
main.o: tree_operations.h tree_operations.o avl_tree.h avl_tree.o main.c
	$(CC) $(CFLAGS) -c main.c
main: tree_operations.o avl_tree.o main.o

# targets de limpeza
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o
	-rm -f ~. main

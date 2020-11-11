# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal (main)

CC = gcc
CFLAGS = -Wall

# regra principal
all: main

# regra para compilar com a opção de debug
# debug: purge
debug: CFLAGS += -DDEBUG
debug: main

# regras para as bibliotecas
tree_operations.o: tree_operations.h tree_operations.c
	$(CC) $(CFLAGS) -c tree_operations.c
avl_tree.o: avl_tree.h avl_tree.c tree_operations.o
	$(CC) $(CFLAGS) -c avl_tree.c 

# regra de compilação do arquivo principal
main.o: tree_operations.h tree_operations.o avl_tree.h avl_tree.o main.c
	$(CC) $(CFLAGS) -c main.c

# regra de montagem do arquivo principal
main: tree_operations.o avl_tree.o main.o

# regras de limpeza
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o
	-rm -f ~. main

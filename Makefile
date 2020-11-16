# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal (main)

CC = gcc
CFLAGS = -Wall -Wextra
LIBFLAGS = -fPIC $(CFLAGS)
SHAREFLAGS = -shared

LIBS = tree_operations.c tree_operations.h avl_tree.c avl_tree.h
OBJECTS = tree_operations.o avl_tree.o

# regra principal
all: myavl

# regra para compilar com a opção de debug
debug: purge
debug: CFLAGS += -DDEBUG
debug: all

# regras para as bibliotecas de árvore
tree_operations.o: tree_operations.h tree_operations.c
	$(CC) $(LIBFLAGS) -c tree_operations.c -o $@
avl_tree.o: avl_tree.h avl_tree.c tree_operations.o
	$(CC) $(LIBFLAGS) -c avl_tree.c -o $@
avl_module.o: avl_tree.o tree_operations.o avl_module.c
	$(CC) $(LIBFLAGS) -c avl_module.c -o $@


# regra de compilação do arquivo principal em C
main.o: tree_operations.h tree_operations.o avl_tree.h avl_tree.o main.c
	$(CC) $(CFLAGS) -c main.c

# regra de montagem do arquivo principal em C
main: tree_operations.o avl_tree.o main.o

#######################################################

# compilação da lib utilizada pelo ctype
avl_module.so: $(OBJECTS) avl_module.o
	$(CC) $(SHAREFLAGS) avl_module.o $(OBJECTS) -o $@

# regra de geração do executavel myavl com link simbólico
myavl: myavl.py avl_module.so
	chmod 755 myavl.py
	ln -sf myavl.py myavl

install: avl_module.so
	cp ./avl_module.so /usr/lib

# regras de limpeza
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o *.so main myavl

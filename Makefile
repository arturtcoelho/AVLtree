# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal (main)

CC = gcc
CFLAGS = -Wall -Wextra
LIBFLAGS = -shared -fPIC $(CFLAGS)

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

#######################################################

avl_module.so: avl_module.c # OUTRAS LIBS DEPOIS
	$(CC) $(LIBFLAGS) -o $@ avl_module.c
# $(CC) $(LIBFLAGS) -Wl,-soname,avl_module -o avl_module.so avl_module.c 

# regra de geração do executavel myavl
myavl: myavl.py avl_module.so
	chmod 755 myavl.py
	ln -sf myavl.py myavl

# regras de limpeza
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o
	-rm -f ~. *.so
	-rm -f ~. main
	-rm -f ~. myavl

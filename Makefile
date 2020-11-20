# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal

CC = gcc
CFLAGS = -Wall -Wextra
LIBFLAGS = -fPIC $(CFLAGS)
MATH = -lm
SHAREFLAGS = -shared

LIBS = tree_operations.c tree_operations.h
OBJECTS = tree_operations.o

# regra principal
all: myavl

# regras para as bibliotecas de árvore
tree_operations.o: tree_operations.h tree_operations.c
	$(CC) $(LIBFLAGS) $(MATH) -c tree_operations.c -o $@
avl_module.o: tree_operations.o avl_module.c avl_module.h
	$(CC) $(LIBFLAGS) -c avl_module.c -o $@

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
	-rm -f ~. *.o *.so myavl

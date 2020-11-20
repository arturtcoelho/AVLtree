# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal

CC = gcc
CFLAGS = -Wall -Wextra
LIBFLAGS = -fPIC $(CFLAGS)
MATH = -lm
SHAREFLAGS = -shared

OBJECTS = tree_operations.o avl_operations.o

# regra principal
all: myavl

# regras para as bibliotecas de árvore
avl_operations.o: avl_operations.c avl_operations.h
	$(CC) $(LIBFLAGS) -c avl_operations.c -o $@
tree_operations.o: avl_operations.o tree_operations.c tree_operations.h
	$(CC) $(LIBFLAGS) $(MATH) -c tree_operations.c -o $@
avl_module.o: $(LIBS)
	$(CC) $(LIBFLAGS) -c avl_module.c -o $@

# compilação da lib utilizada pelo ctype
avl_module.so: avl_module.o $(OBJECTS) 
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

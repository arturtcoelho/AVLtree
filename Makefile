# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal

CC = gcc
CFLAGS = -Wall -Wextra
LIBFLAGS = -fPIC $(CFLAGS)
MATH = -lm
SHAREFLAGS = -shared

OBJECTS = tree_operations.o avl_operations.o print_tree.o

# regra principal
all: myavl

# regras para as bibliotecas de árvore
print_tree.o: print_tree.c print_tree.h
	$(CC) $(LIBFLAGS) $(MATH) -c print_tree.c -o $@
avl_operations.o: avl_operations.c avl_operations.h
	$(CC) $(LIBFLAGS) -c avl_operations.c -o $@
tree_operations.o: avl_operations.o tree_operations.c tree_operations.h
	$(CC) $(LIBFLAGS) $(MATH) -c tree_operations.c -o $@
avl_module.o: avl_module.c avl_module.h tree_operations.c tree_operations.h avl_operations.c avl_operations.h print_tree.o
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

gtk:
	$(CC) $(CFLAGS) gtk_tree.c `pkg-config --libs --cflags gtk+-2.0`

# regras de limpeza
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o *.so myavl

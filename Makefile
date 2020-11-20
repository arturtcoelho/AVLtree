# Makefile geral do projeto, realiza a compilação das bibliotecas e código principal

CC = gcc
CFLAGS = -Wall -Wextra
LIBFLAGS = -fPIC $(CFLAGS)
MATH = -lm
SHAREFLAGS = -shared

LIBS = tree_operations.c tree_operations.h
OBJECTS = tree_operations.o

# regra principal
all: mytree

# regra para compilar com a opção de debug
debug: purge
debug: CFLAGS += -DDEBUG
debug: all

# regras para as bibliotecas de árvore
tree_operations.o: tree_operations.h tree_operations.c
	$(CC) $(LIBFLAGS) $(MATH) -c tree_operations.c -o $@
tree_module.o: tree_operations.o tree_module.c tree_module.h
	$(CC) $(LIBFLAGS) -c tree_module.c -o $@

#######################################################

# compilação da lib utilizada pelo ctype
tree_module.so: $(OBJECTS) tree_module.o
	$(CC) $(SHAREFLAGS) tree_module.o $(OBJECTS) -o $@

# regra de geração do executavel mytree com link simbólico
mytree: mytree.py tree_module.so
	chmod 755 mytree.py
	ln -sf mytree.py mytree

install: tree_module.so
	cp ./tree_module.so /usr/lib

# regras de limpeza
clean: all
	-rm -f ~. *.o

purge:
	-rm -f ~. *.o *.so mytree

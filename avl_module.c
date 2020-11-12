// por enquanto utilizada para testar integração

#include <stdio.h>

int avl_teste();
int avl_soma_teste(int a, int b);

int avl_teste() {
    printf("TESTE\n");
    return 1;
}

int avl_soma_teste(int a, int b) {
    printf("SOMA: %d + %d == %d\n", a, b, a+b);
    return a + b;
}
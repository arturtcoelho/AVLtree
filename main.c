#include <stdio.h>

#include "avl_tree.h"

int main(){

    avl_t tree;

    printf("inicializa: %d\n", initialize_avl(&tree));
    printf("add key: %d\n", add_key_avl(&tree, 10));

    return 0;
}

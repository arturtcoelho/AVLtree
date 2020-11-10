#include <stdio.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
// após realizarmos a interface para python esse será um arquivo python
int main(){

    avl_t tree;

    printf("inicializa: %d\n", initialize_avl(&tree));
    printf("insert key: %d\n", insert_key_avl(&tree, 10));
    printf("key %d\n", tree.root->key);
    
    return 0;
}

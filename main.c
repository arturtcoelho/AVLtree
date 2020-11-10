#include <stdio.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
// após realizarmos a interface par apython esse será um arquivo python
int main(){
    avl_t tree;

<<<<<<< HEAD
    initialize_avl(&tree);
    add_key_avl(&tree, 10);
    // printf("%d\n", tree.root->key);
=======
    printf("inicializa: %d\n", initialize_avl(&tree));
    printf("insert key: %d\n", insert_key_avl(&tree, 10));
    printf("key: %d\n", tree.root->key);
    printf("%d");
>>>>>>> 7b5b0c2b1bafb6438b5c7f5c8d1d4a2e260b9193

    return 0;
}

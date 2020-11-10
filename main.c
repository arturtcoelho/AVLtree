#include <stdio.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
// após realizarmos a interface par apython esse será um arquivo python
int main(){
    avl_t tree;

    initialize_avl(&tree);
    add_key_avl(&tree, 10);
    // printf("%d\n", tree.root->key);

    return 0;
}

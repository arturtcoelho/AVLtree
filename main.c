#include <stdio.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
// após realizarmos a interface para python esse será um arquivo python
int main(){

    avl_t tree;
    initialize_avl(&tree);

    for (int i = 10; i >= 0; i--) {
        insert_key_avl(&tree, i);
        // insert_key_avl(&tree, i * 2 * (-1 * i % 3) + i*i / 10);
    }

    print_tree_avl(&tree);

    return 0;
}

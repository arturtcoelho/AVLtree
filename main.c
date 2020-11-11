#include <stdio.h>

#include "avl_tree.h"

// por enquanto contém código em C para testes, 
// após realizarmos a interface para python esse será um arquivo python
int main(){

    avl_t tree;
    initialize_avl(&tree);

    print_tree_avl(&tree);
    insert_key_avl(&tree, 10);
    print_tree_avl(&tree);
    remove_key_avl(&tree, 10);
    print_tree_avl(&tree);

    return 0;
}
